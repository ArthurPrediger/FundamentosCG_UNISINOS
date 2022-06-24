#include "TileField.h"

TileField::TileField(const glm::ivec2& dimensions,
	const glm::vec2& fieldOffsets,
	const std::vector<int>& tileMap, 
	const std::vector<std::string>& tilesTypes,
	const std::vector<std::string>& tilesetPaths, 
	const std::vector<glm::vec2>& normalizedTexturesPositions, 
	const std::vector<glm::vec2>& tilesetOffsets, 
	Shader* shader)
	:
	dimensions(dimensions),
	shader(shader)
{
	for (int tileY = 0; tileY < dimensions.y; tileY++)
	{
		for (int tileX = 0; tileX < dimensions.x; tileX++)
		{
			size_t index = size_t(tileY) * dimensions.x + tileX;
			tiles.emplace_back( Tile(
				tilesetPaths[tileMap[index]],
				tilesTypes[tileMap[index]],
				shader,
				{ fieldOffsets.x + (tileX - tileY) * tileWidth / 2.0f, fieldOffsets.y / 2.0f + (tileX + tileY) * tileHeight / 2.0f },
				{ tileWidth, tileHeight },
				normalizedTexturesPositions[tileMap[index]],
				tilesetOffsets[tileMap[index]]));
		}
	}
}

void TileField::changeTileTypes(const std::vector<glm::ivec2>& tilesAtPos)
{
	for (size_t i = 0; i < changedPositions.size(); i++)
	{
		auto index = changedPositions[i].y * dimensions.x + changedPositions[i].x;
		tiles[index] = Tile(
			changedTiles[i].getTexPath(),
			changedTiles[i].getType(),
			shader,
			changedTiles[i].getPosition(),
			{ tileWidth, tileHeight },
			changedTiles[i].getNorTexDim(),
			changedTiles[i].getTilesetOff()
		);
	}

	changedTiles.clear();
	changedPositions = tilesAtPos;

	for (size_t i = 0; i < tilesAtPos.size(); i++)
	{
		auto index = tilesAtPos[i].y * dimensions.x + tilesAtPos[i].x;
		changedTiles.push_back(std::move(tiles[index]));
		tiles[index] = Tile(
			"../Tilesets/Ground_Rocky1_256x128.png",
			"cursed",
			shader,
			changedTiles[i].getPosition(),
			{ tileWidth, tileHeight },
			{ 0.33333333333f, 0.2f },
			{ 0.0f, 0.2f }
		);
	}
}

void TileField::draw() const
{
	for (const auto& tile : tiles)
	{
		tile.draw();
	}
}
