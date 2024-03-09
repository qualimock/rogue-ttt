#include "game.hpp"

#include "../../include/imgui/imgui.h"
#include "../../include/imgui-sfml/imgui-SFML.h"
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include <iostream>

#include "../grid/grid.hpp"

Game::Game(const sf::VideoMode& videoMode)
	: m_window(sf::RenderWindow(sf::VideoMode(640, 480), "Rogue Tic-Tac-Toe"))
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

		if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::Escape) {
				event.type = sf::Event::Closed;
			}
		}

		if (event.type == sf::Event::Closed) {
			m_window.close();
		}
	}

	ImGui::SFML::Update(m_window, m_deltaClock.restart());
}

void Game::render() {
	ImGui::Begin("Window");
	ImGui::Button("Butt OMG", ImVec2(0, 0));
	ImGui::Text("HELLO!!!");
	ImGui::End();

	m_window.clear();
	for (auto line : Grid::Grid(m_window).grid()) {
		m_window.draw(line);
	}
	ImGui::SFML::Render(m_window);
	m_window.display();
}
