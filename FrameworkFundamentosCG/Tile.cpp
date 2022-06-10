#include "Tile.h"
#include <memory>

Tile::Tile(const std::string& tileSetPath, Shader* shader, const glm::vec2& pos, const glm::vec2& scale,
	float normalizedTileTextureWidth, float normalizedTileTextureHeight,
	const glm::vec2& tileSetOffset)
	:
	tileSetPath(tileSetPath),
	shader(shader),
	gameObject(GameObject::createGameObject()),
	normalizedTileTextureWidth(normalizedTileTextureWidth),
	normalizedTileTextureHeight(normalizedTileTextureHeight),
	tileSetOffset(tileSetOffset)
{
	gameObject.transform.translation = { pos, 1.0f };
	gameObject.transform.scale = { scale, 1.0f };
	gameObject.model = std::make_shared<Model>(
		shader,
		triangles,
		tileSetPath,
		gameObject.transform.mat4());
}

void Tile::draw() const
{
	shader->setVec2("offsets", tileSetOffset.x, tileSetOffset.y);
	gameObject.model->draw();
}

