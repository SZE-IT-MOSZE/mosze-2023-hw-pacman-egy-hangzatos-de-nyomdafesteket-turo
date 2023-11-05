#ifndef TILE
#define TILE

#include "Tile.hpp"


#endif

Tile::Tile()
{
	Tile::Init();
	Tile::SetTileType(TileType::Wall);
}

Tile::Tile(TileType t)
{
	Tile::Init();
	Tile::SetTileType(t);
}

Tile::~Tile()
{
	// TODO
}

bool Tile::Passable()
{
	return this->passable;
}

Tile::TileType Tile::GetTileType()
{
	return this->tileType;
}

void Tile::SetTileType(TileType t)
{
	switch (t)
	{
	case Wall:
		this->icon = '#';
		this->passable = false;
		break;

	case Floor:
		this->icon = ' ';
		this->passable = true;
		break;

	default:
		this->icon = '\0';
		this->passable = false;
		break;
	}
}

char Tile::GetIcon()
{
	return this->icon;
}

void Tile::Init()
{
	content = nullptr;
}
