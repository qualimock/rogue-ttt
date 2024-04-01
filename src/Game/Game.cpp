#include "Game.hpp"

#include <imgui-SFML.h>
#include <imgui.h>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include <iostream>

#include "../GridManager/GridManager.hpp"

#define DEBUG

Game::Game(const sf::VideoMode& videoMode)
	: m_window(videoMode, "Rogue Tic-Tac-Toe")
	, m_map(std::move(Grid::Map::getMap(m_window)))
{}

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

		if (event.type != sf::Event::MouseButtonPressed)
		{
			Grid::GridManager::processEvent(event, m_map.get());
		}
		else
		{
			if (!ImGuiFlags.mouseHover)
			{
				Grid::GridManager::processEvent(event, m_map.get());
			}
		}

		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				event.type = sf::Event::Closed;
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
			m_map->resize(sf::Vector2i(event.size.width, event.size.height));
		}
	}

	m_map->update();
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
	if (ImGui::Begin("Debug"))
	{
		ImGui::LabelText(m_map->name().c_str(), "Name");
		ImGui::LabelText((std::to_string(m_map->position().x) + ":" + std::to_string(m_map->position().y)).c_str(), "Position");
		ImGui::LabelText((std::to_string(m_map->size().x) + ":" + std::to_string(m_map->size().y)).c_str(), "Size");

		if (ImGui::IsWindowHovered())
			ImGuiFlags.mouseHover = true;

		ImGui::End();
	}
#endif

	ImGui::SFML::Render(m_window);
}

void Game::render()
{
	m_window.clear();
	m_map->draw();
	processImgui();
	m_window.display();
}
