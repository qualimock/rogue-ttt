#include "Game.hpp"

#include <imgui-SFML.h>
#include <imgui.h>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include <iostream>

#include "../GridManager/GridManager.hpp"

#include "../Grid/DraggableGrid.hpp"
#include "../Grid/Map.hpp"

#define DEBUG

#include <iostream>

Game::Game(const sf::VideoMode& videoMode)
	: m_window(videoMode, "Rogue Tic-Tac-Toe")
{
	m_grids.emplace_back(std::move(Grid::Map::getMap(m_window)).get());

	// combat grid
	{
		sf::Vector2i combatP1(m_window.getSize().x, m_window.getSize().y/2 + 60);
		sf::Vector2i combatP2(combatP1 + sf::Vector2i(120, 120));
		m_grids.emplace_back(new Grid::BaseGrid(m_window, Grid::BaseGrid::EGridType::Combat, "combat", combatP1, combatP2));
	}
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

void Game::update()
{
	ImGui::SFML::Update(m_window, m_deltaClock.restart());

	sf::Event event;
	while (m_window.pollEvent(event))
	{
		ImGui::SFML::ProcessEvent(m_window, event);

		for (auto &grid : m_grids)
		{
			if (event.type != sf::Event::MouseButtonPressed)
			{
				if (!ImGuiFlags.mouseHover)
					Grid::GridManager::processEvent(event, grid);				
			}
			else
			{
				if (!ImGuiFlags.mouseHover)
				{
					Grid::GridManager::processEvent(event, grid);
				}
			}
		}

		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				event.type = sf::Event::Closed;
			}

			if (event.key.code == sf::Keyboard::S) {
				auto mousePos = sf::Mouse::getPosition(m_window);
				m_grids.emplace_back(new Grid::DraggableGrid(m_window, Grid::IGrid::EGridType::Interaction,
															 ("G(" + std::to_string(mousePos.x) + ":" + std::to_string(mousePos.y) + ")").c_str(),
															 mousePos, mousePos+sf::Vector2i(100, 100), 7, true));
			}
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
			{
				sf::Vector2i combatPosition(m_window.getSize().x-160, m_window.getSize().y/2 - 60);
				m_grids[1]->move(combatPosition);
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
				// placeholder
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
			for (auto grid = m_grids.begin(); grid < m_grids.end(); ++i, ++grid)
			{
				if (m_grids.at(i)->name() == "map")
					continue;
				
				if (ImGui::MenuItem(m_grids.at(i)->name().c_str()))
				{
					m_grids.erase(grid);
				}
			}

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
		grid->draw();
		grid->drawCells(m_window);
	}
	processImgui();
	m_window.display();
}
