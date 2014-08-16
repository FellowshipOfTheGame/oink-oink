#include "pathfinder.h"
#include <cmath>
#include <cstdlib>
#include <iostream>

Pathfinder::Pathfinder() {
	Tile *tile;
	for (int i = WORLD_WIDTH - 1; i >= 0; i--) {
		for (int j = WORLD_HEIGHT - 1; j >= 0; j--) {
			tile = &grid[i][j];

			tile->parent = 0;
			tile->busy = false;
			tile->opened = false;
			tile->closed = false;

			tile->x = i;
			tile->y = j;

			tile->g = 0;
			tile->h = 0;
			tile->f = 0;
		}
	}
}

void Pathfinder::registerTower(int x, int y) {
	this->grid[x][y].busy = true;
}

void Pathfinder::deleteTower(int x, int y) {
	this->grid[x][y].busy = false;
}

std::list<Tile*> Pathfinder::getPath(int fromX, int fromY, int toX, int toY) {
	std::list<Tile*> path;

	if (fromX == toX && fromY == toY && isPathWalkable(fromX, fromY, toX, toY)) {
		int size = std::abs((fromX - toX)) + std::abs((fromY - toY));

		Tile *tmp = new Tile[size];
		for (int i = 0; i < size; i++) {
			tmp[i].x = fromX + i + 1;
			tmp[i].y = fromY;
			path.push_back(&tmp[i]);
		}
		delete[] tmp;
	}
	else {
		path = aStar(fromX, fromY, toX, toY);
	}

	return path;
}

bool Pathfinder::isPathWalkable(int fromX, int fromY, int toX, int toY) {
	for (int i = toX; i > 0; i--) {
		if (!isEmpty(i, fromY))
			return false;
	}

	return true;
}

bool Pathfinder::isEmpty(int x, int y) {
	if (this->grid[x][y].busy)
		return false;

	return true;
}

int Pathfinder::getGScore(Tile* t1, Tile* t2) {
	return t2->g + ((t1->y == t2->y || t1->x == t2->x) ? 10 : 14);
}

int Pathfinder::getHScore(Tile* t1, Tile* t2) {
	return (std::abs(t1->x - t2->x) + std::abs(t2->y - t1->y))*10;
}

void Pathfinder::computeScores(Tile *t1, Tile *t2)
{
    t1->g = getGScore(t1, t1->parent);
    t1->h = getHScore(t1, t2);
    t1->f = t1->g + t1->h;
}

std::list<Tile*> Pathfinder::aStar(int x1, int y1, int x2, int y2) {
	std::list<Tile*> path;
	std::list<Tile*> opened;
	std::list<Tile*> closed;

	Tile* start = &this->grid[x1][y1];
	Tile* end = &this->grid[x2][y2];

	Tile* current = 0;
	Tile* child = 0;

	std::list<Tile*>::iterator i;

	opened.push_back(start);
	start->opened = true;

	unsigned short int n = 0;

	while(n == 0 || (current != end && n < 200)) {
		for (i = opened.begin(); i != opened.end(); ++i) {
			if (i == opened.begin() || current->f >= (*i)->f) {
				current = (*i);
			}
		}

		if (current == end)
			break;

		opened.remove(current);
		current->opened = false;

		closed.push_back(current);
		current->closed = true;

		for (int x = -1; x <= 1; x++){
			for (int y = -1; y <= 1; y++) {
				if ((x == 0 && y == 0) || (current->x + x <= 0 || current->y + y <= 0) || (current->x + x >= 20 || current->y + y >= 10)) {
					continue;
				}

				child = &this->grid[current->x + x][current->y + y];
				if (child->closed || !isEmpty(child->x, child->y))
					continue;

				if (x != 0 && y != 0) {
					if (!isEmpty(current->x + x, current->y) || this->grid[current->x + x][y].closed)
						continue;
					if (!isEmpty(current->x, current->y + y) || this->grid[current->x][current->y + y].closed)
						continue;
				}

				if (child->opened) {
					if (child->g > getGScore(child, current)) {
						child->parent = current;
						computeScores(child, end);
					}
				} else {
						opened.push_back(child);
						child->opened = true;

						child->parent = current;
						computeScores(child, end);
				}
			}
		}

		n++;
	}

	for (i = opened.begin(); i != opened.end(); ++i) {
		(*i)->opened = false;
	}

	for (i = closed.begin(); i != closed.end(); ++i) {
		(*i)->closed = false;
	}

	while (current->parent != 0 || current != start) {
		path.push_back(current);
		current = current->parent;
		n++;
	}

	path.push_back(start);

	return path;
}