#include "Scene.h"

Scene::Scene(Shader* shader)
{
	std::vector<int> tileMap;

	for (int i = 0; i < 100; i++)
	{
		tileMap.push_back(0);
	}

	std::vector<std::string> tileSetPaths = {"../TileSets/Solid_Tiles_Flat_128x88.png"};

	std::vector<glm::vec2> normalizedTexturesDimensions = { { 1.0f / 6.0f, 1.0f } };

	std::vector<glm::vec2> tileSetOffsets = { { 5.0f / 6.0f, 0.0f } };

	tf = { tileMap, tileSetPaths, normalizedTexturesDimensions, { 400.0f, 150.0f }, tileSetOffsets, shader };
}

void Scene::draw() const
{
	tf.draw();
}
