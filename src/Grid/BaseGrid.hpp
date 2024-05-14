#pragma once

#include "IGrid.hpp"

#include "Cell/Cell.hpp"

namespace Grid
{
	class BaseGrid : public IGrid
	{
		unsigned m_layer;

		std::string m_name;

	public:
		BaseGrid(const std::string &name,
				 EGridType eGridType,
				 const sf::Vector2i &topLeft,
				 const sf::Vector2i &bottomRight,
				 unsigned layer = 0,
				 unsigned linesOffset = 40);

		void move(const sf::Vector2i &position) override;
		void resize(const sf::Vector2i &point) override;

		void setBorder(const IGrid &grid);
		void setBorder(sf::RenderWindow &window);

		const std::string name() const { return m_name; }
		const unsigned layer() const { return m_layer; }
	};
}
