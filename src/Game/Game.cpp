#include "Game.hpp"

#include <imgui-SFML.h>
#include <imgui.h>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include <iostream>

#include "../GridManager/GridManager.hpp"

#include "../Grid/DraggableGrid.hpp"
#include "../Grid/CombatGrid.hpp"
#include "../Grid/Map.hpp"

#define DEBUG

#include <iostream>

Game::Game(const sf::VideoMode& videoMode)
	: m_window(videoMode, "Rogue Tic-Tac-Toe")
{
	m_grids.emplace_back(Grid::Map::getMapPointer());

	{
		sf::Vector2i combatLeftTop(m_window.getSize().x, m_window.getSize().y/2 + 60);
		sf::Vector2i combatRightBottom(combatLeftTop + sf::Vector2i(120, 120));
		m_grids.emplace_back(new Grid::CombatGrid("combat", combatLeftTop, combatRightBottom, 0, 40));
	}

	m_gameState = EGameState::Exploring;
}

Game::~Game()
{
	ImGui::SFML::Shutdown();
}

bool Game::init()
{
    m_window.setFramerateLimit(60);
	if (!ImGui::SFML::Init(m_window))
	{
		std::cerr << "ERR:\n\tFailed to initialize the window!" << std::endl;
		return false;
	}

	return true;
}

void Game::onMouseClick(sf::Event event)
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(m_window);
	
    // search grid on mouse position
	{
		std::vector<Grid::BaseGrid *> mouseGrids;

		for (auto &grid : m_grids)
		{
			sf::Vector2i gridLU = grid->position();
			sf::Vector2i gridRB = grid->position() + sf::Vector2i(grid->size());

			if (mousePos.x >= gridLU.x && mousePos.x <= gridRB.x &&
				mousePos.y >= gridLU.y && mousePos.y <= gridRB.y)
			{
			    mouseGrids.emplace_back(grid);
			}
		}


		if (mouseGrids.empty())
			return;

		if (mouseGrids.size() == 1)
		{
			Grid::GridManager::mouseClicked(m_window, event, mouseGrids[0]);
			return;
		}

		Grid::BaseGrid *currentGrid = mouseGrids.at(0);
		for (auto &grid : mouseGrids)
		{
			if (grid->layer() > currentGrid->layer())
			{
				currentGrid = grid;
			}
		}

		Grid::GridManager::mouseClicked(m_window, event, currentGrid);
	}
}

void Game::onKeyPressed(sf::Event event)
{
	if (event.key.code == sf::Keyboard::Escape)
	{
		event.type = sf::Event::Closed;
	}

	if (event.key.code == sf::Keyboard::S) {
		auto mousePos = sf::Mouse::getPosition(m_window);

		// m_grids.emplace_back
		// (
				// Grid::DraggableGrid
				// (
					// ("G(" + std::to_string(mousePos.x) + ":" + std::to_string(mousePos.y) + ")").c_str(),
					// Grid::IGrid::EGridType::Interaction,
					// mousePos, mousePos+sf::Vector2i(10, 100), 7, true
				// )
		// );
	}
}

void Game::update()
{
	ImGui::SFML::Update(m_window, m_deltaClock.restart());

	sf::Event event;
	while (m_window.pollEvent(event))
	{
		ImGui::SFML::ProcessEvent(m_window, event);

		switch(event.type)
		{
		case sf::Event::MouseButtonPressed:
			if (!ImGuiFlags.mouseHover)
			{
				onMouseClick(event);
			}
			break;

		case sf::Event::KeyPressed:
			onKeyPressed(event);

		default:
			break;
		}

		if (event.type == sf::Event::Closed)
		{
			m_window.close();
		}

		if (event.type == sf::Event::Resized)
		{
			sf::FloatRect view(0, 0, event.size.width, event.size.height);
			m_window.setView(sf::View(view));
			m_grids[0]->resize(sf::Vector2i(event.size.width-200, event.size.height));

// combat grid
			for (auto &grid : m_grids)
			{
				if (grid->type() == Grid::IGrid::EGridType::Combat)
				{
					sf::Vector2i combatPosition(m_window.getSize().x-160, m_window.getSize().y/2 - 60);
					grid->move(combatPosition);
				}
			}
		}
	}

	for (auto &grid : m_grids)
	{
		grid->update();
	}
}

void Game::processImgui()
{
	ImGuiFlags.mouseHover = false;

	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("Game"))
		{
			if (ImGui::MenuItem("New"))
			{
				for (auto &grid : m_grids)
				{
					if (grid->name() == "combat")
					{
						grid->clear();
						break;
					}
				}
			}

			if (ImGui::MenuItem("Exit", "Esc"))
			{
				m_window.close();
			}

			if(ImGui::IsWindowHovered())
				ImGuiFlags.mouseHover = true;

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Grids"))
		{
			int i = 0;

			// for (auto grid = m_grids.begin(); grid < m_grids.end(); ++i, ++grid)
			// {
				// if (grid.base() == "map")
					// continue;
				
				// if (ImGui::MenuItem(grid.base()->name().c_str()))
				// {
					// m_grids.erase(grid);
				// }
			// }

			ImGui::EndMenu();
		}

		if(ImGui::IsWindowHovered())
				ImGuiFlags.mouseHover = true;

		ImGui::EndMainMenuBar();
	}

#ifdef DEBUG
	ImGui::Begin("Debug");
		for (auto &grid : m_grids)
		{
			ImGui::LabelText(grid->name().c_str(), "Name");
			ImGui::LabelText((std::to_string(grid->position().x) + ":" + std::to_string(grid->position().y)).c_str(), "Position");
			ImGui::LabelText((std::to_string(grid->size().x) + ":" + std::to_string(grid->size().y)).c_str(), "Size");
			ImGui::LabelText((std::to_string(grid->layer()).c_str()), "Layer");
			ImGui::LabelText("", "Cells");
			for (auto &cell : grid->m_entities)
			{
				ImGui::LabelText(std::to_string(cell.second->getFillColor().toInteger()).c_str(), "Color");
				ImGui::LabelText((std::to_string(cell.second->getPosition().x) + ":" + std::to_string(cell.second->getPosition().y)).c_str(), "Position");
				ImGui::LabelText((std::to_string(cell.second->getSize().x) + ":" + std::to_string(cell.second->getSize().y)).c_str(), "Size");
			}
		}

		if (ImGui::IsWindowHovered())
			ImGuiFlags.mouseHover = true;

		ImGui::End();
#endif

	ImGui::SFML::Render(m_window);
}

void Game::render()
{
	m_window.clear();
	for (auto &grid : m_grids)
	{
		grid->render(m_window);
		grid->renderCells(m_window);
	}
	processImgui();
	m_window.display();
}
