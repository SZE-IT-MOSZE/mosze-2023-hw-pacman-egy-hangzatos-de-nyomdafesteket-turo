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

bool Tile::IsPassable()
{
	return this->passable;
}

void Tile::SetPassable(bool value)
{
	this->passable = value;
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

GameObject* Tile::GetContent()
{
	return content;
}

void Tile::SetContent(GameObject* what)
{
	passable = (what == nullptr);
	content = what;
}


void Tile::Init()
{
	content = nullptr;
}
