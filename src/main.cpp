#include "pathfinder/pathfinder.h"
#include <iostream>
#include <list>

// TODO: Remover antes de entregar
#include "debugger.h"

int main(int argc, char* argv[]) {
	// TODO: Remover antes de entregar
	install_debugger();

	Pathfinder* Path = new Pathfinder();

	Path->registerTower(9, 5);
	Path->registerTower(9, 6);
	Path->registerTower(11, 6);
	Path->registerTower(12, 6);
	Path->registerTower(6, 8);
	Path->registerTower(5, 7);

	std::list<Tile*> path_tiles = Path->getPath(5, 8, 12, 5);

	std::list<Tile*>::iterator i;

	for (i = path_tiles.begin(); i != path_tiles.end(); ++i)
		std::cout << "x: " << (*i)->x << " " << "y: " << (*i)->y << std::endl;

	return 0;
}