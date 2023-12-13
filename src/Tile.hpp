#ifndef TILE_H
#define TILE_H

#include "DDelegate.hpp"
#include "Engine.hpp"

/// <summary>
/// A tile, of which the map is made of
/// </summary>
class Tile
{

public:

	enum TileType { Wall = 0, Floor = 1};

	Tile();

	Tile(char icon, bool passable);

	Tile(TileType t);

	~Tile();

	bool IsPassable();
	void SetPassable(bool value);

	TileType GetTileType();

	void SetTileType(TileType t);

	char GetIcon();

	GameObject* GetContent();
	void SetContent(GameObject* what);

private:
	GameObject* content;
	void Init();
	char icon;
	bool passable;
	TileType tileType;
};

#endif
