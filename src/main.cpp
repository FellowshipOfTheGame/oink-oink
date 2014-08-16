#include "pathfinder/pathfinder.h"
#include "scene/enemy.h"
#include <iostream>
#include <list>

// TODO: Remover antes de entregar
#include "debugger.h"

int main(int argc, char* argv[]) {
	// TODO: Remover antes de entregar
	install_debugger();

	Pathfinder* Path = new Pathfinder();
	Monsters* Monster_ = new Monsters();

	Monster_->addMonster(5, 8, 1, RIGHT);
	Monster_->addMonster(4, 8, 2, RIGHT);

	Path->registerTower(9, 5);
	Path->registerTower(9, 6);
	Path->registerTower(11, 6);
	Path->registerTower(12, 6);
	Path->registerTower(6, 8);
	Path->registerTower(5, 7);

	Path->deleteTower(5, 7);

	std::list<Tile*> path_tiles = Path->getPath(5, 8, 12, 5);

	Monster_->addPath(path_tiles);
	std::list<Monster*> monster_list = Monster_->getMonsters();

	for (int n = 0; n <= 12; n++) {
		std::cout << n << std::endl;

		if (n != 0)
			Monster_->walk();
	}

	std::cout << std::endl;

	std::list<Monster*>::iterator it;

	for (it = monster_list.begin(); it != monster_list.end(); ++it) {
		std::cout << "x: " << (*it)->x << " " << "y: " << (*it)->y << std::endl;
		std::cout << "dir: " << (*it)->dir << " " << "type: " << (*it)->type << std::endl;
	}

	return 0;
}