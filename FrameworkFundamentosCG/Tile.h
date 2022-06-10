#pragma once

#include "GameObject.h"

class Tile
{
public:
	Tile(const std::string& spritePath, int normalizedTileTextureWidth,
		int normalizedTileTextureHeight, const glm::vec2& tileSetOffset);
private:
	const std::string& spritePath;
	GameObject gameObject;
	int normalizedTileTextureWidth;
	int normalizedTileTextureHeight;
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