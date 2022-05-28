#pragma once

#include "IndexedTriangleList.h"
#include "GameObject.h"

class Scene
{
public:
	Scene(GLuint shaderID);
	void draw() const;
private:
	GLuint shaderID;
	std::vector<GameObject> gameObjects;
	std::vector<Model::Vertex> vertices = {
		 // posicoes            // cores              // coordenadas de textura
		{ { 0.5f,  0.5f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0 } }, // superior direito
		{ { 0.5f, -0.5f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f } }, // inferior direito
		{ { -0.5f, -0.5f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 0.0f } }, // inferior esquerdo
		{ { -0.5f,  0.5f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0 } }  // superior esquerdo
	};
	std::vector<unsigned int> indices = {
	0, 1, 3, // primeiro triangulo
	1, 2, 3  // segundo triangulo
	};
	IndexedTriangleList<Model::Vertex> triangles{ vertices, indices };
};