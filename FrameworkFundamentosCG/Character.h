#pragma once

#include "Animation.h"

class Character
{
private:
	enum class Sequence
	{
		WalkingDown,
		WalkingLeft,
		WalkingRight,
		WalkingUp,
		StandingDown,
		StandingLeft,
		StandingRight,
		StandingUp,
		Count
	};
public:
	Character(const glm::vec2& pos, const glm::vec2& scale);
	void update(float dt, Shader* shader);
	void handleInput(GLFWwindow* window);
	void draw() const;
private:
	void setDirection(const glm::vec2& dir);
private:
	std::string spritePath;
	glm::vec2 vel = { 0.0f, 0.0f };
	int nFrames = 4;
	int nAnimations = 4;
	std::vector<Animation> animations;
	Sequence iCurSequence = Sequence::StandingDown;
	float speed = 150.0f;
	GameObject gameObject;
	std::vector<Model::Vertex> vertices = {
		// posicoes            // cores              // coordenadas de textura
	   { { 0.5f,  0.5f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f / nFrames, 0.0f }}, // superior direito
	   { { 0.5f, -0.5f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f / nFrames, 1.0 / nAnimations }}, // inferior direito
	   { { -0.5f, -0.5f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0 / nAnimations } }, // inferior esquerdo
	   { { -0.5f,  0.5f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f } }  // superior esquerdo
	};
	std::vector<unsigned int> indices = {
	0, 1, 3, // primeiro triangulo
	1, 2, 3  // segundo triangulo
	};
	IndexedTriangleList<Model::Vertex> triangles{ vertices, indices };
};