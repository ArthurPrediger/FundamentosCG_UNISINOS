#include "TileField.h"

TileField::TileField(int xDimension, int yDimension, 
	const std::vector<int>& tileMap, 
	const std::vector<std::string>& tilesTypes,
	const std::vector<std::string>& tileSetPaths, 
	const std::vector<glm::vec2>& normalizedTexturesPositions, 
	const glm::vec2& fieldOffsets, 
	const std::vector<glm::vec2>& tileSetOffsets, 
	Shader* shader)
	:
	shader(shader)
{
	for (int tileY = 0; tileY < yDimension; tileY++)
	{
		for (int tileX = 0; tileX < xDimension; tileX++)
		{
			size_t index = size_t(tileY) * xDimension + tileX;
			tiles.emplace_back(Tile(
				tileSetPaths[tileMap[index]],
				tilesTypes[tileMap[index]],
				shader,
				{ fieldOffsets.x + (tileX - tileY) * tileWidth / 2.0f, fieldOffsets.y / 2.0f + (tileX + tileY) * tileHeight / 2.0f },
				{ tileWidth, tileHeight },
				normalizedTexturesPositions[tileMap[index]],
				tileSetOffsets[tileMap[index]]));
		}
	}
}

void TileField::draw() const
{
	for (const auto& tile : tiles)
	{
		tile.draw();
	}
}
