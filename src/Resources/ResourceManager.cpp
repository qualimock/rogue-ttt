#include "ResourceManager.hpp"

#include <SFML/Graphics.hpp>

#include <rapidjson/document.h>
#include <rapidjson/error/en.h>

#include <sstream>
#include <fstream>
#include <iostream>

ResourceManager::TexturesMap ResourceManager::m_textures;
ResourceManager::SpritesMap ResourceManager::m_sprites;
std::string ResourceManager::m_path;
std::vector<std::vector<std::string>> ResourceManager::m_levels;

void ResourceManager::set_executable_path(const std::string &executablePath)
{
	size_t found = executablePath.find_last_of("/\\");
	m_path = executablePath.substr(0, found);
}

void ResourceManager::unload_all_resources()
{
	m_textures.clear();
	m_sprites.clear();
}

std::string ResourceManager::get_file_string(const std::string &relativeFilePath)
{
	std::ifstream file;
	file.open(m_path + "/" + relativeFilePath.c_str(), std::ios::in | std::ios::binary);

	if (!file.is_open()) {
		std::cerr << "ERROR::FILE::get_file_string:\n\tCannot open " << relativeFilePath << std::endl;
		return std::string();
	}

	std::stringstream buffer;
	buffer << file.rdbuf();
	return buffer.str();
}

std::shared_ptr<sf::Texture> ResourceManager::load_texture(const std::string &textureName, const std::string &texturePath)
{
	int channels = 0;
	int width = 0;
	int height = 0;

	sf::Texture texture;
	if (!texture.loadFromFile(std::string(m_path + "/" + texturePath)))
	{
		std::cout << "ERROR::RESOURCES::load_texture:\n\tCannot load image: " << texturePath << std::endl;
		return nullptr;
	}

	std::shared_ptr<sf::Texture> newTexture = m_textures.emplace(
		textureName,
		std::make_shared<sf::Texture>(texture)
		).first->second;

	return newTexture;
}

std::shared_ptr<sf::Texture> ResourceManager::get_texture(const std::string &textureName)
{
	TexturesMap::const_iterator it = m_textures.find(textureName);
	if (it != m_textures.end()) {
		return it->second;
	}

	std::cerr << "ERROR::RESOURCES::get_texture:\n\tCannot find texture: " << textureName << std::endl;
	return nullptr;
}

std::shared_ptr<sf::Sprite> ResourceManager::load_sprite(const std::string &spriteName,
														 const std::string &textureName,
														 const sf::IntRect &subTexture)
{
	auto texture = get_texture(textureName);
	if (!texture) {
		std::cerr << "ERROR::RESOURCES::load_sprite: Cannot find texture " << textureName
				  << " for the sprite: " << spriteName << std::endl;
	}

	std::shared_ptr<sf::Sprite> newSprite = m_sprites.emplace(
		spriteName,
		std::make_shared<sf::Sprite>(*texture, subTexture)
		).first->second;
	return newSprite;
}


std::shared_ptr<sf::Sprite> ResourceManager::get_sprite(const std::string &spriteName) {
	SpritesMap::const_iterator it = m_sprites.find(spriteName);
	if (it != m_sprites.end()) {
		return it->second;
	}

	std::cerr << "ERROR::RESOURCES::get_sprite:\n\tCannot find sprite: " << spriteName << std::endl;
	return nullptr;
}

bool ResourceManager::load_json_resources(const std::string &jsonPath)
{
	const std::string jsonString = get_file_string(jsonPath);
	if (jsonString.empty())
	{
		std::cerr << "ERROR::RESOURCES::load_json_resources:\n\tNo JSON resources file!" << std::endl;
		return false;
	}

	rapidjson::Document document;
	rapidjson::ParseResult parseResult = document.Parse(jsonString.c_str());
	if (!parseResult)
	{
		std::cerr << "ERROR::RESOURCES::LOAD_JSON_RESOURCES: Parse error:\n\t"
				  << rapidjson::GetParseError_En(parseResult.Code())
				  << "(" << parseResult.Offset() << ")\n\t"
				  << "In JSON file: " << jsonPath << std::endl;
		return false;
	}

	auto spritesIterator = document.FindMember("sprites");
	if (spritesIterator != document.MemberEnd())
	{
		for (const auto &currentSprite : spritesIterator->value.GetArray())
		{
			const std::string name = currentSprite["name"].GetString();
			const std::string texture = currentSprite["initialSubTexture"].GetString();

			auto sprite = load_sprite(name, texture, sf::IntRect(0, 0, 40, 40));
			if (!sprite) {
				continue;
			}
		}
	}

	auto levelsIterator = document.FindMember("levels");
	if (levelsIterator != document.MemberEnd())
	{
		for (const auto &currentLevel : levelsIterator->value.GetArray())
		{
			const auto name = currentLevel["name"].GetArray();
			const auto description = currentLevel["description"].GetArray();
			size_t maxLength = 0;

			std::vector<std::string> levelRows;
			levelRows.reserve(description.Size());

			for (const auto &currentRow : description)
			{
				levelRows.emplace_back(currentRow.GetString());
				if (maxLength < levelRows.back().length())
				{
					maxLength = levelRows.back().length();
				}
			}

			for (auto &currentRow : levelRows)
			{
				while (currentRow.length() < maxLength)
				{
					currentRow.append("D");
				}
			}

			m_levels.emplace_back(std::move(levelRows));
		}
	}

	return true;
}
