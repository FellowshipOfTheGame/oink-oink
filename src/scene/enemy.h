#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "../resources/structs.h"
#include "../resources/const.h"
#include <list>
#include <iostream>

class Monsters {
	public:
		void addMonster(int x, int y, int type, int dir = RIGHT);
		void deleteMonster(int x, int y);

		std::list<Monster*> getMonsters();

		void addPath(std::list<Tile*> path);

		void walk();

	private:
		std::list<Monster*> monsters;
		std::list<Tile*> path;

		Tile* getNextPathTile(int x, int y);

};

#endif