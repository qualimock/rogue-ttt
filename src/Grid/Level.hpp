#pragma once

#include "../Entity/Character/Character.hpp"
#include "../Entity/Actor/Actor.hpp"

namespace Entity {
	class Actor;
	class Character;
}

class Level{
	std::string m_tag; //вдруг пригодится

	std::map<std::string, Entity::Actor> 		m_actors;
	std::map<std::string, Entity::Character> 	m_characters;;

public:
	void addActor(std::string &name, Entity::Actor *actor){ m_actors.emplace(name, actor); }
	void addCharacter(std::string &name, Entity::Character *character){ m_characters.emplace(name, character); }

	Entity::Entity &getActor(std::string &name) { return m_actors.at(name); }
	Entity::Entity &getCharacter(std::string &name) { return m_characters.at(name); }

	std::map<std::string, Entity::Actor> &getActors() { return m_actors; }
	std::map<std::string, Entity::Character> &getCharacters() { return m_characters; }
};
