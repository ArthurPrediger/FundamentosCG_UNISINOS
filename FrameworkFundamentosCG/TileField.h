#pragma once

#include "Tile.h"

class TileField
{
public:
	TileField() = default;
	TileField(int xDimension, int yDimension, 
	    const std::vector<int>& tileMap, 
	    const std::vector<std::string>& tilesTypes,
	    const std::vector<std::string>& tileSetPaths, 
	    const std::vector<glm::vec2>& normalizedTexturesPositions, 
	    const glm::vec2& fieldCenterPos, 
	    const std::vector<glm::vec2>& tileSetOffsets, 
		Shader* shader);
	void draw() const;
	glm::vec2 getTilePosition(int tileIndex) const
	{
		auto pos = tiles[tileIndex].getPosition();
		return { pos.x , pos.y + tileHeight / 2.0f };
	}
	const std::string getTileType(int tyleIndex) const
	{
		return tiles[tyleIndex].getType();
	}
private:
	Shader* shader = nullptr;
	std::vector<Tile> tiles;
	float tileWidth = 96.0f;
	float tileHeight = 48.0f;
};