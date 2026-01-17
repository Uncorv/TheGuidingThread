#include "GridMap.h"

#include "Roads2DGenerator.h"

GridMap::GridMap()
	: m_width(0)
	, m_height(0)
{
}

void GridMap::generate(int width, int height, float density)
{
	clear();
	if (width <= 0 || height <= 0)
		return;

	m_width = width;
	m_height = height;

	Roads2DGenerator generator(width, height);
	generator.generate(density);
	m_walkable = generator.exportToPixelMap();

	for (int x = 0; x < width; ++x)
	{
		for (int y = 0; y < height; ++y)
		{
			if (isWalkable(x, y))
				m_free_cells.push_back({x, y});
		}
	}
}

void GridMap::clear()
{
	m_width = 0;
	m_height = 0;
	m_walkable.clear();
	m_free_cells.clear();
}

int GridMap::getWidth() const
{
	return m_width;
}

int GridMap::getHeight() const
{
	return m_height;
}

bool GridMap::isWalkable(int x, int y) const
{
	if (x < 0 || y < 0)
		return false;
	if (x >= static_cast<int>(m_walkable.size()))
		return false;
	if (m_walkable[x].empty() || y >= static_cast<int>(m_walkable[x].size()))
		return false;
	return m_walkable[x][y];
}

const std::vector<GridMap::Cell> &GridMap::getFreeCells() const
{
	return m_free_cells;
}
