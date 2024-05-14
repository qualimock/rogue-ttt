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
			  const sf::Vector2i &topLeft,
			  const sf::Vector2i &bottomRight,
			  unsigned linesOffset);
		~IGrid();

		virtual void update();
		virtual void draw();

		virtual void move(const sf::Vector2i &position) = 0;
		virtual void resize(const sf::Vector2i &point) = 0;

		const EGridType type() const { return m_type; }
		const sf::Vector2i position() const { return m_topLeft; }
		const sf::Vector2u size() const { return m_size; }

	private:
		Lines m_verticalLines;
		Lines m_horizontalLines;

		EGridType m_type;

	protected:
		sf::RenderWindow &m_window;

		sf::Vector2i m_topLeft;
		sf::Vector2i m_bottomRight;

		sf::Vector2u m_linesAmount;

		unsigned m_offset;

		sf::Vector2u m_size;
	};
}
