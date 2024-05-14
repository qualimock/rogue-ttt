#pragma once

#include <SFML/Graphics.hpp>

#include <vector>

namespace Grid
{
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

		IGrid(EGridType gridType,
			  const sf::Vector2i &topLeft,
			  const sf::Vector2i &bottomRight,
			  unsigned linesOffset);

		virtual void update();
		virtual void render(sf::RenderTarget &target);

		virtual void move(const sf::Vector2i &position) = 0;
		virtual void resize(const sf::Vector2i &point) = 0;

		const EGridType type() const { return m_type; }
		const sf::Vector2i position() const { return m_topLeft; }
		const sf::Vector2u size() const { return m_size; }

	private:
		std::vector<sf::VertexArray> m_verticalLines;
		std::vector<sf::VertexArray> m_horizontalLines;

		EGridType m_type;

	protected:
		sf::Vector2i m_topLeft;
		sf::Vector2i m_bottomRight;

		sf::Vector2u m_linesAmount;

		unsigned m_offset;

		sf::Vector2u m_size;
	};
}
