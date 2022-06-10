#include "Tile.h"

Tile::Tile(const std::string& spritePath, int normalizedTileTextureWidth,
	int normalizedTileTextureHeight, const glm::vec2& tileSetOffset)
	:
	spritePath(spritePath),
	gameObject(GameObject::createGameObject()),
	normalizedTileTextureWidth(normalizedTileTextureWidth),
	normalizedTileTextureHeight(normalizedTileTextureHeight),
	tileSetOffset(tileSetOffset)
{}