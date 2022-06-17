#pragma once

#include "IndexedTriangleList.h"
#include "TileField.h"
#include "Character.h"

class Scene
{
public:
	Scene(Shader* shader);
	void update(GLFWwindow* window, float dt);
private:
	void handleInput(GLFWwindow* window);
private:
	Shader* shader;
	glm::ivec2 charFieldPos = { 0 , 0 };
	glm::vec2 charDir = { 0.0f , 0.0f };
	std::unique_ptr<Character> character;
	int xDimField = 10;
	int yDimField = 10;
	TileField tf;
	float time = 0.0f;
};