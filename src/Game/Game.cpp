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

Game::Game(const sf::VideoMode& videoMode)
	: m_window(videoMode, "Rogue Tic-Tac-Toe")
{
	m_grids.emplace_back(std::move(Grid::Map::getMap(m_window)).get());
	m_grids.emplace_back(new Grid::DraggableGrid(m_window, Grid::IGrid::EGridType::Interaction, "grid",
												 sf::Vector2i(100, 100), sf::Vector2i(200, 200), 7, true));
	m_grids.emplace_back(new Grid::DraggableGrid(m_window, Grid::IGrid::EGridType::Interaction, "grid1",
												 sf::Vector2i(200, 100), sf::Vector2i(400, 400), 7, true));
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
			m_grids[0]->resize(sf::Vector2i(event.size.width, event.size.height));
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
	}
	processImgui();
	m_window.display();
}
