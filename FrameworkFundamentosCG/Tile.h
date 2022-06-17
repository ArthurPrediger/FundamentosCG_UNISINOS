#pragma once

#include "GameObject.h"

class Tile
{
public:
	Tile(const std::string& tileSetPath, Shader* shader, const glm::vec2& pos, const glm::vec2& scale,
		float normalizedTileTextureWidth, float normalizedTileTextureHeight, const glm::vec2& tileSetOffset);
	void draw() const;
	glm::vec2 getPosition() const
	{
		return glm::vec2(gameObject.transform.translation);
	}
private:
	const std::string& tileSetPath;
	Shader* shader;
	GameObject gameObject;
	float normalizedTileTextureWidth;
	float normalizedTileTextureHeight;
	glm::vec2 tileSetOffset;
	std::vector<Model::Vertex> vertices = {
		// posicoes            // cores              // coordenadas de textura
	   { { 0.5f,  0.5f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { normalizedTileTextureWidth, 0.0f }}, // superior direito
	   { { 0.5f, -0.5f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { normalizedTileTextureWidth, normalizedTileTextureHeight }}, // inferior direito
	   { { -0.5f, -0.5f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, normalizedTileTextureHeight } }, // inferior esquerdo
	   { { -0.5f,  0.5f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f } }  // superior esquerdo
	};
	std::vector<unsigned int> indices = {
	0, 1, 3, // primeiro triangulo
	1, 2, 3  // segundo triangulo
	};
	IndexedTriangleList<Model::Vertex> triangles{ vertices, indices };
};