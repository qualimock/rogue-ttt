#include "game.hpp"

#include <imgui-SFML.h>
#include <imgui.h>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include <iostream>

#include "../grid/grid.hpp"

// #define DEBUG

Game::Game(const sf::VideoMode& videoMode)
	: m_window(videoMode, "Rogue Tic-Tac-Toe")
	, m_grid(m_window)
{

}

Game::~Game() {
	ImGui::SFML::Shutdown();
}

bool Game::init() {
    m_window.setFramerateLimit(60);
	if (!ImGui::SFML::Init(m_window)) {
		std::cerr << "ERR:\n\tFailed to initialize the window!" << std::endl;
		return false;
	}

	return true;
}

void Game::update() {
	sf::Event event;
	while (m_window.pollEvent(event)) {
		ImGui::SFML::ProcessEvent(m_window, event);

		if (!ImGuiFlags.mouseHover) {
			m_grid.processEvents(event);
		}

		if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::Escape) {
				event.type = sf::Event::Closed;
			}
		}

		if (event.type == sf::Event::Closed) {
			m_window.close();
		}

		if (event.type == sf::Event::Resized)
		{
			sf::FloatRect view(0, 0, event.size.width, event.size.height);
			m_window.setView(sf::View(view));
		}
	}

	ImGui::SFML::Update(m_window, m_deltaClock.restart());

	m_grid.update();
}

void Game::processImgui() {
	ImGuiFlags.mouseHover = false;

	if (ImGui::BeginMainMenuBar()) {
		if (ImGui::BeginMenu("Game")) {
			if (ImGui::MenuItem("New")) {
				m_grid.clear();
			}

			if (ImGui::MenuItem("Exit", "Esc")) {
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

	if (m_grid.victory.first) {
		std::string winner;
		switch (m_grid.victory.second) {
		case Grid::Cell::Cross:
			winner = "Cross";
			break;
		case Grid::Cell::Nought:
			winner = "Nought";
			break;
		default:
			winner = "";
			break;
		}

		if (ImGui::Begin("VICTORY")) {
			ImGui::LabelText("WON", winner.c_str());

			if (ImGui::IsWindowHovered())
				ImGuiFlags.mouseHover = true;

			ImGui::End();
		}
	}

#ifdef DEBUG
	if (ImGui::Begin("Debug")) {
		ImGui::LabelText(std::to_string(m_grid.horizontal().size()).c_str(), "Horizontal");
		ImGui::LabelText(std::to_string(m_grid.vertical().size()).c_str(), "Vertical");
		ImGui::LabelText(std::to_string(m_grid.cells().size()).c_str(), "Cells");

		if (ImGui::IsWindowHovered())
			ImGuiFlags.mouseHover = true;

		ImGui::End();
	}
#endif

	ImGui::SFML::Render(m_window);
}

void Game::render() {
	m_window.clear();

	for (auto &cell : m_grid.cells()) {
		m_window.draw(cell.second);
	}
	for (auto &line : m_grid.grid().first) {
		m_window.draw(line);
	}
	for (auto &line : m_grid.grid().second) {
		m_window.draw(line);
	}

	processImgui();

	m_window.display();
}
