#ifndef __PATHFINDER_H__
#define __PATHFINDER_H__

#include <list>
#include "../resources/structs.h"
#include "../resources/const.h"

class Pathfinder {
	public:
		Pathfinder();

		std::list<Tile*> getPath(int fromX, int fromY, int toX, int toY);
		void registerTower(int x, int y);

	private:
		Tile grid[WORLD_WIDTH][WORLD_HEIGHT];

		std::list<Tile*> aStar(int x1, int y1, int x2, int y2);
		int getHScore(Tile* t1, Tile* t2);
		int getGScore(Tile* t1, Tile* t2);
		void computeScores(Tile* t1, Tile* t2);

		bool isEmpty(int x, int y);
		bool isPathWalkable(int fromX, int fromY, int toX, int toY);

};


#endif