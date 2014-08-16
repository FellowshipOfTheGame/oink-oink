#include "enemy.h"

void Monsters::addMonster(int x, int y, int type, int dir) {
	Monster* new_monster = new Monster;

	new_monster->x = x;
	new_monster->y = y;
	new_monster->dir = dir;
	new_monster->type = type;

	this->monsters.push_back(new_monster);
}

void Monsters::deleteMonster(int x, int y) {
	std::list<Monster*>::iterator i;

	for (i = this->monsters.begin(); i != this->monsters.end(); ++i) {
		if ((*i)->x == x && (*i)->y == y)
			this->monsters.remove(*i);
	}
}

void Monsters::addPath(std::list<Tile*> path) {
	this->path = path;
}

void Monsters::walk() {
	Monster* current;
	Monster* next;

	Tile* next_tile;

	std::list<Monster*>::reverse_iterator i;

	for (i = this->monsters.rbegin(); i != this->monsters.rend(); ++i) {
		if ((++i) == this->monsters.rend()) {
			--i;

			next_tile = this->getNextPathTile((*i)->x, (*i)->y);

			(*i)->x = next_tile->x;
			(*i)->y = next_tile->y;

			if (next_tile == *this->path.begin())
				this->monsters.remove(*i);

			break;
		}

		--i;

		current = *i;
		next = *(++i);

		--i;

		current->x = next->x;
		current->y = next->y;
	}
}

Tile* Monsters::getNextPathTile(int x, int y) {
	std::list<Tile*>::reverse_iterator i;

	for (i = this->path.rbegin(); i != this->path.rend(); ++i) {
		if ((*i)->x == x && (*i)->y == y) {
			++i;
		return *i;
		}
	}

	return 0;
}

std::list<Monster*> Monsters::getMonsters() {
	return this->monsters;
}