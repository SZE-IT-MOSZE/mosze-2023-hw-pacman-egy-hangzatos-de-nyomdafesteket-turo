#ifndef TILE_H
#define TILE_H

#include "DDelegate.hpp"
#include "Engine.hpp"

class Tile
{

public:

	enum TileType { Other = 0, Wall = 1, Floor = 2};

	Tile();

	Tile(char icon, bool passable);

	Tile(TileType t);

	~Tile();

	bool Passable();

	TileType GetTileType();

	void SetTileType(TileType t);

	char GetIcon();


private:
	void Init();
	char icon;
	bool passable;
	TileType tileType;
};

#endif
