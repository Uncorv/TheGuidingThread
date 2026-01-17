#pragma once

#include <vector>

class GridMap
{
public:
	struct Cell
	{
		int x;
		int y;
	};

	GridMap();

	void generate(int width, int height, float density);
	void clear();

	int getWidth() const;
	int getHeight() const;
	bool isWalkable(int x, int y) const;
	const std::vector<Cell> &getFreeCells() const;

private:
	int m_width;
	int m_height;
	std::vector<std::vector<bool>> m_walkable;
	std::vector<Cell> m_free_cells;
};
