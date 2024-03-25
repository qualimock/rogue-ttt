#pragma once

#include <SFML/Graphics.hpp>

#include <vector>

namespace Grid
{
	typedef std::vector<sf::VertexArray> Lines;

	class IGrid
	{
	public:
		enum class EGridType
		{
			Map,
			Combat,
			Interaction,
			Storage
		};

		IGrid(sf::RenderWindow &window,
			  EGridType gridType,
			  const sf::Vector2u &topLeft,
			  const sf::Vector2u &bottomRight,
			  const std::string &name,
			  unsigned linesOffset);
		~IGrid();

		virtual void processEvents(sf::Event event) = 0;
		virtual void update() = 0;
		virtual void draw();

		const sf::Vector2u position() const { return m_topLeft; }
		const sf::Vector2u size() const { return m_size; }
		const std::string name() const { return m_name; }

	protected:
		sf::RenderWindow &m_window;

		sf::Vector2u m_topLeft;
		sf::Vector2u m_bottomRight;

		unsigned m_offset;

		std::string m_name;

		sf::Vector2u m_size;

		sf::Vector2u m_linesAmount;

		Lines m_verticalLines;
		Lines m_horizontalLines;
	};
}
