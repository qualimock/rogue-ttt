#pragma once

#include <SFML/Graphics.hpp>

#include <string>
#include <memory>
#include <map>
#include <vector>

typedef std::vector<std::vector<std::string>> ObjectArray;

class ResourceManager {
	typedef std::map<const std::string, std::shared_ptr<sf::Texture>> TexturesMap;
	static TexturesMap m_textures;

	typedef std::map<const std::string, std::shared_ptr<sf::Sprite>> SpritesMap;
	static SpritesMap m_sprites;

	static ObjectArray m_levels;
	static ObjectArray m_floors;
	static std::vector<sf::Vector2i> m_levelIndices;

	static std::string m_path;

	static std::string get_file_string(const std::string &relativeFilePath);

public:
	static void set_executable_path(const std::string &executablePath);
	static void unload_all_resources();

	~ResourceManager() = delete;
	ResourceManager() = delete;
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;
	ResourceManager& operator=(ResourceManager&&) = delete;
	ResourceManager(ResourceManager&&) = delete;

	static std::shared_ptr<sf::Texture> load_texture(const std::string &textureName,
													 const std::string &texturePath);
	static std::shared_ptr<sf::Texture> get_texture(const std::string &textureName);

	static std::shared_ptr<sf::Sprite> load_sprite(const std::string &spriteName,
												   const std::string &textureName,
												   const sf::IntRect &subTexture);
	static std::shared_ptr<sf::Sprite> get_sprite(const std::string &spriteName);

	static bool load_json_resources(const std::string &jsonPath);

	static const std::pair<unsigned, std::pair<std::vector<sf::Vector2i>, std::pair<ObjectArray, ObjectArray>>>
	get_levels()
	{
		return std::make_pair(m_levels.size(), std::make_pair(m_levelIndices, std::make_pair(m_levels, m_floors)));
	}
};
