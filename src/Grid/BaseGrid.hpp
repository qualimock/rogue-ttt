#pragma once

#include "IGrid.hpp"

namespace Grid
{
	class BaseGrid : public IGrid
	{
	public:
		BaseGrid(sf::RenderWindow &window,
				 EGridType eGridType,
				 const std::string &name,
				 const sf::Vector2u &topLeft,
				 const sf::Vector2u &bottomRight,
				 unsigned linesOffset = 40);

		void move(const sf::Vector2u &position) override;
		void resize(const sf::Vector2u &point) override;

		void setBorder(const IGrid &grid);
		void setBorder(sf::RenderWindow &window);

		const std::string name() const { return m_name; }

	protected:
		std::string m_name;
	};
}
