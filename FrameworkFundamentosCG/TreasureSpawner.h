#pragma once

#include "GameObject.h"
#include "TileField.h"
#include <random>

class TreasureSpawner
{
public:
	TreasureSpawner(Shader* shader, 
		std::shared_ptr<TileField> tf, 
		const glm::ivec2& playerFieldPos,
		int numTreasures);
	void update(float dt);
	void draw() const;
	bool checkIfTreasureCaught(const glm::ivec2& pos);
	int getNumTreasures() const
	{
		return int(treasures.size());
	}
private:
	void changeTreasuresPos();
private:
	struct Treasure
	{
		GameObject gameObject;
		glm::ivec2 fieldPos;
	};
private:
	std::mt19937 rng;
	std::uniform_int_distribution<int> spawnPosDist;
	Shader* shader;
	std::shared_ptr<TileField> tf;
	std::string treasureSpritePath;
	const glm::ivec2& playerFieldPos;
	std::vector<unsigned int> indexSpawnableTiles;
	const float minSqrSpawnDist = 9.0f;
	float time = 0.0f;
	const float changePosRate = 8.0f;
	std::vector<Treasure> treasures;
	std::vector<Model::Vertex> vertices = {
		// posicoes            // cores              // coordenadas de textura
	   { { 0.5f,  0.5f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 0.0f }}, // superior direito
	   { { 0.5f, -0.5f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0 }}, // inferior direito
	   { { -0.5f, -0.5f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0 } }, // inferior esquerdo
	   { { -0.5f,  0.5f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f } }  // superior esquerdo
	};
	std::vector<unsigned int> indices = {
	0, 1, 3, // primeiro triangulo
	1, 2, 3  // segundo triangulo
	};
	IndexedTriangleList<Model::Vertex> triangles{ vertices, indices };
};