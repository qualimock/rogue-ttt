#include "DialogueCell.hpp"
#include <imgui-SFML.h>
#include <imgui.h>
namespace Entity
{
	DialogueCell::DialogueCell(const sf::Vector2i &position,
					 const sf::Vector2u &size,
					 Type type)
		: Actor("dialogueCell", position, size, 0, EType::DialogueCell)
		, m_type(type)
	{
		setSprite();
		inDialogue = false;
	}

	void DialogueCell::update() {
		if (inDialogue) {
			ImGui::Begin("Dialogue 1");
			ImGui::Text("Test Dialogue");
			ImGui::End();
		}
	}

	bool DialogueCell::SelectDialogue() {
		switch (m_type)
		{
		case Type::Exit:
			return true;
			break;

		case Type::Trade:
			return false;
			break;

		case Type::Talk:
			inDialogue = true;
			return false;
			break;

		case Type::None:
			return false;
			break;
		}
	}

	void DialogueCell::setSprite()
	{
		sf::Texture texture;
		switch(m_type)
		{
		case Type::Exit:
			texture.loadFromFile("res/Sprites/Actors/X1.png");
			setTexture(texture);
			break;

		case Type::Trade:
			texture.loadFromFile("res/Sprites/Actors/Trade.png");
			setTexture(texture);
			break;

		case Type::Talk:
			texture.loadFromFile("res/Sprites/Actors/Talk.png");
			setTexture(texture);
			break;

		case Type::None:
			m_color = sf::Color::Transparent;
			break;
		}

		this->setColor(m_color);
	}
}
