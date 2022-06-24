#include "Tile.h"
#include <memory>

Tile::Tile(const std::string& tilesetPath, const std::string& type,
	Shader* shader, const glm::vec2& pos, const glm::vec2& scale,
	const glm::vec2& normalizedTileTexturePosition, const glm::vec2& tilesetOffset)
	:
	tilesetPath(tilesetPath),
	type(type),
	shader(shader),
	gameObject(GameObject::createGameObject()),
	normalizedTileTexturePosition(normalizedTileTexturePosition),
	tilesetOffset(tilesetOffset)
{
	gameObject.transform.translation = { pos, 1.0f };
	gameObject.transform.scale = { scale, 1.0f };
	gameObject.model = std::make_shared<Model>(
		shader,
		triangles,
		tilesetPath,
		gameObject.transform.mat4());
}

void Tile::draw() const
{
	shader->setVec2("offsets", tilesetOffset.x, tilesetOffset.y);
	gameObject.model->draw();
}

