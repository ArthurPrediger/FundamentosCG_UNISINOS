#pragma once

#include "IndexedTriangleList.h"
#include "TileField.h"
#include "Character.h"
#include "Scene.h"

class Level_1 : public Scene
{
public:
	Level_1(const std::string name, Shader* shader);
	void update(GLFWwindow* window, float dt) override;
	void draw() override;
private:
	void handleInput(GLFWwindow* window);
	void CheckWinLoseCases();
	void reset();
private:
	Shader* shader;
	glm::ivec2 initialCharPos = { 0 , 0 };
	glm::ivec2 charFieldPos = initialCharPos;
	glm::vec2 charDir = { 0.0f , 0.0f };
	std::unique_ptr<Character> character;
	int xDimField = 10;
	int yDimField = 10;
	TileField tf;
	float time = 0.0f;
	bool resetting = false;
};