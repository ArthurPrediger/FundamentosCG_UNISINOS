#pragma once

#include "GameObject.h"

class Tile
{
public:
	Tile(const std::string& tileSetPath, const std::string& type,
		Shader* shader, const glm::vec2& pos, const glm::vec2& scale,
		const glm::vec2& normalizedTileTexturePosition, const glm::vec2& tileSetOffset);
	void draw() const;
	glm::vec2 getPosition() const
	{
		return glm::vec2(gameObject.transform.translation);
	}
	const std::string getType() const
	{
		return type;
	}
private:
	std::string tileSetPath;
	std::string type;
	Shader* shader;
	GameObject gameObject;
	glm::vec2 normalizedTileTexturePosition;
	glm::vec2 tileSetOffset;
	std::vector<Model::Vertex> vertices = {
		// posicoes            // cores              // coordenadas de textura
	   { { 0.5f,  0.5f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { normalizedTileTexturePosition.x, 0.0f }}, // superior direito
	   { { 0.5f, -0.5f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { normalizedTileTexturePosition.x, normalizedTileTexturePosition.y }}, // inferior direito
	   { { -0.5f, -0.5f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, normalizedTileTexturePosition.y } }, // inferior esquerdo
	   { { -0.5f,  0.5f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f } }  // superior esquerdo
	};
	std::vector<unsigned int> indices = {
	0, 1, 3, // primeiro triangulo
	1, 2, 3  // segundo triangulo
	};
	IndexedTriangleList<Model::Vertex> triangles{ vertices, indices };
};