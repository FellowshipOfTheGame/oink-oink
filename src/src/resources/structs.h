#ifndef __STRUCTS_H__
#define __STRUCTS_H__

struct Tile {
	Tile* parent;
	bool busy;
	bool opened;
	bool closed;

	unsigned int f, g, h;
	int x, y;
};

#endif