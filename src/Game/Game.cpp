#include "Game.hpp"

#include <imgui-SFML.h>
#include <imgui.h>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include <iostream>

#include "../GridManager/GridManager.hpp"
#include "../Resources/ResourceManager.hpp"

#include "../Grid/DraggableGrid.hpp"
#include "../Grid/CombatGrid.hpp"
#include "../Grid/InventoryGrid.h"
#include "../Grid/Map.hpp"

#define DEBUG

Game::Game(const sf::VideoMode& videoMode)
	: m_window(videoMode, "Rogue Tic-Tac-Toe")
{}

Game::~Game()
{
	ImGui::SFML::Shutdown();
}

bool Game::init()
{
	auto map = Grid::Map::getMap();
	m_grids.emplace("map", map);

	std::cout << m_grids.size() << std::endl;

	m_gameState = EGameState::Exploring;

	for (auto &grid : m_grids)
	{
		m_visibleImGuiWindows.emplace(grid.first, false);
	}

	m_window.setFramerateLimit(60);
	if (!ImGui::SFML::Init(m_window))
	{
		std::cerr << "ERR:\n\tFailed to initialize the window!" << std::endl;
		return false;
	}

	ResourceManager::load_json_resources("res/resources.json");

	return true;
}

void Game::onMouseClick(sf::Event &event)
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(m_window);

    // search grid on mouse position
	{
		std::map<std::string, Grid::BaseGrid *> mouseGrids;

		for (auto &grid : m_grids)
		{
			sf::Vector2i gridLU = grid.second->position();
			sf::Vector2i gridRB = grid.second->position() + sf::Vector2i(grid.second->size());

			if (mousePos.x >= gridLU.x && mousePos.x <= gridRB.x &&
				mousePos.y >= gridLU.y && mousePos.y <= gridRB.y)
			{
			    mouseGrids.emplace(grid);
			}
		}

		if (mouseGrids.empty())
			return;

		GridPair currentGrid = std::make_pair("", nullptr);

		for (auto &grid : mouseGrids)
		{
			if (currentGrid.second == nullptr || grid.second->layer() > currentGrid.second->layer())
			{
				currentGrid = grid;
			}
		}

		switch(event.type)
		{
		case sf::Event::MouseButtonPressed:
			if (currentGrid.first == "combat" && m_gameState == EGameState::InCombat)
			{
				if (Grid::GridManager::mouseClicked(m_window, event, currentGrid.second))
				{
					m_grids.at("map")->destroyEntity(m_currentlyInteractedEntity);
					m_currentlyInteractedEntity = nullptr;
					m_grids.erase("combat");
					m_gameState = EGameState::Exploring;
				}
			}
			break;
		}
	}
}

void Game::onKeyPressed(sf::Event &event)
{
	// player moving
	if (m_gameState == EGameState::Exploring)
	switch (event.key.code)
	{
	case sf::Keyboard::W:
	case sf::Keyboard::A:
	case sf::Keyboard::S:
	case sf::Keyboard::D:
	case sf::Keyboard::Up:
	case sf::Keyboard::Left:
	case sf::Keyboard::Down:
	case sf::Keyboard::Right:
		auto moveResult = Grid::GridManager::moveEvent(m_window, event, m_grids.at("map"));
		if (moveResult)
		{
			if (moveResult->hasTag("enemy"))
			{
				m_currentlyInteractedEntity = dynamic_cast<Entity::Character *>(moveResult);
				m_gameState = EGameState::InCombat;
			}
			else if (moveResult->hasTag("item"))
			{
				m_currentlyInteractedEntity = dynamic_cast<Entity::Actor *>(moveResult);
				m_gameState = EGameState::Interacting;
			}
		}
		else
		{
			m_currentlyInteractedEntity = nullptr;
			m_visibleImGuiWindows.erase("combat");
			m_gameState = EGameState::Exploring;
		}
		break;
	}

	if (event.key.code == sf::Keyboard::Escape)
	{
		event.type = sf::Event::Closed;
		return;
	}

	std::cout << "STATE" << std::endl;

	switch (m_gameState)
	{
	case EGameState::Exploring:
		std::cout << "EXPLORING" << std::endl;
		break;

	case EGameState::InCombat:
		if (!m_grids.contains("combat"))
		{
			m_visibleImGuiWindows.emplace("combat", false);
			m_grids.emplace(
				"combat",
				new Grid::CombatGrid(
					Grid::BaseGrid(
						Grid::BaseGrid::EGridType::Combat,
						sf::Vector2i(m_window.getSize().x-160, m_window.getSize().y/2 + 60),
						sf::Vector2u(120, 120))
					)
				);
		}
		break;

	case EGameState::Interacting:
		std::cout << "INTERACTION" << std::endl;
		if (!m_grids.contains("inventory")) {
			m_visibleImGuiWindows.emplace("inventory", false);
			m_grids.emplace(
				"inventory",
				new Grid::InventoryGrid(
					Grid::BaseGrid(
						Grid::BaseGrid::EGridType::Interaction,
						sf::Vector2i(m_window.getSize().x - 160, m_window.getSize().y / 6),
						sf::Vector2u(120, 120))
				)
			);
		}
		Grid::InventoryGrid * Inventory = dynamic_cast<Grid::InventoryGrid *>(m_grids.at("inventory"));
		Inventory->AddItem(m_currentlyInteractedEntity);
		m_grids.at("map")->destroyEntity(m_currentlyInteractedEntity);
		m_gameState = EGameState::Exploring;
		break;
	}
}

void Game::update()
{
	ImGui::SFML::Update(m_window, m_deltaClock.restart());

	//m_window.setSize(sf::Vector2u(720, 480));
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		ImGui::SFML::ProcessEvent(m_window, event);

		switch(event.type)
		{
		case sf::Event::MouseButtonPressed:
			std::cout << std::endl << "EVENT" << std::endl;
			if (!ImGuiFlags.mouseHover)
			{
				onMouseClick(event);
			}
			break;

		case sf::Event::KeyPressed:
			std::cout << std::endl << "EVENT" << std::endl;
			onKeyPressed(event);
			break;

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

			//m_grids.at("map")->resize(sf::Vector2i(event.size.width-200, event.size.height));

            // move combat grid relative to window size
			auto combatGrid = m_grids.find("combat");
			if (combatGrid != m_grids.end())
			{
				combatGrid->second->move(sf::Vector2i(m_window.getSize().x-160, m_window.getSize().y/2 - 60));
			}
		}
	}

	for (auto &grid : m_grids)
	{
		grid.second->update();
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
				// m_grids.find("combat")->second->clear();
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
			for (auto &grid : m_grids)
			{
				if (ImGui::MenuItem(grid.first.c_str()))
				{
					m_visibleImGuiWindows.at(grid.first) =
						!m_visibleImGuiWindows.at(grid.first);
				}
			}
			ImGui::EndMenu();
		}

		if(ImGui::IsWindowHovered())
				ImGuiFlags.mouseHover = true;

		ImGui::EndMainMenuBar();
	}

	for (auto &grid : m_grids)
	{
		if (m_visibleImGuiWindows.at(grid.first))
		{
			ImGui::Begin(grid.first.c_str());

			ImGui::LabelText((std::to_string(grid.second->position().x) + ":" + std::to_string(grid.second->position().y)).c_str(), "Position");
			ImGui::LabelText((std::to_string(grid.second->size().x) + ":" + std::to_string(grid.second->size().y)).c_str(), "Size");
			ImGui::LabelText((std::to_string(grid.second->layer()).c_str()), "Layer");
			ImGui::LabelText("", "Cells");

			for (auto &cell : grid.second->m_entities)
			{
				ImGui::LabelText("", "");
				ImGui::LabelText((std::to_string(cell.second->index().x) + ":" + std::to_string(cell.second->index().y)).c_str(), "Index");
				ImGui::LabelText((std::to_string(cell.second->position().x) + ":" + std::to_string(cell.second->position().y)).c_str(), "Position");
				ImGui::LabelText((std::to_string(cell.second->size().x) + ":" + std::to_string(cell.second->size().y)).c_str(), "Size");
			}

			if (ImGui::IsWindowHovered())
				ImGuiFlags.mouseHover = true;

			ImGui::End();
		}
	}

	ImGui::SFML::Render(m_window);
}

void Game::render()
{
	m_window.clear();
	for (auto &grid : m_grids)
	{
		grid.second->render(m_window);
		grid.second->renderCells(m_window);
	}
	processImgui();
	m_window.display();
}
