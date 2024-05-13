#pragma once

#include "IGrid.hpp"

#include <set>
#include <map>

#include "Cell/Cell.hpp"

namespace Grid
{
	class BaseGrid : public IGrid
	{
	public:
		BaseGrid(sf::RenderWindow &window,
				 EGridType eGridType,
				 const std::string &name,
				 const sf::Vector2i &topLeft,
				 const sf::Vector2i &bottomRight,
				 unsigned linesOffset = 40);

		void processEvent(sf::Event &event) override;

		void move(const sf::Vector2i &position) override;
		void resize(const sf::Vector2i &point) override;

		void setBorder(const IGrid &grid);
		void setBorder(sf::RenderWindow &window);

		const std::string name() const { return m_name; }

	protected:
		std::string m_name;
	private:
		std::map<sf::Vector2u, Cell> m_cells;
	};
}
