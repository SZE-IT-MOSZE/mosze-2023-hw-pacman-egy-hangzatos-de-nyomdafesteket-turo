#ifndef TILE_H
#define TILE_H

#include "DDelegate.hpp"
#include "Engine.hpp"


class Tile
{

public:

	enum TileType { Wall = 0, Floor = 1};

	Tile();

	Tile(char icon, bool passable);

	Tile(TileType t);

	~Tile();

	bool Passable();

	TileType GetTileType();

	void SetTileType(TileType t);

	char GetIcon();

	GameObject* content;

private:
	void Init();
	char icon;
	bool passable;
	TileType tileType;
};

#endif
