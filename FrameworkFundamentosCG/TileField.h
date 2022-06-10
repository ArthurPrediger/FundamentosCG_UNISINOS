#pragma once

#include "Tile.h"

class TileField
{
public:
	TileField() = default;
	TileField(const std::vector<int>& tileMap, const std::vector<std::string>& tileSetPaths,
		const std::vector<glm::vec2>& normalizedTexturesDimensions, const glm::vec2& fieldCenterPos,
		const std::vector<glm::vec2>& tileSetOffsets, Shader* shader);
	void draw() const;
private:
	Shader* shader;
	std::vector<Tile> tiles;
	float tileWidth = 64.0f;
	float tileHeight = 32.0f;
};