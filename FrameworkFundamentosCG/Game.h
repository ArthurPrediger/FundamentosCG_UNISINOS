#pragma once

#include "Level.h"

class Game
{
public:
	Game(Shader* shader)
	{
		scenes.push_back(std::make_unique<Level>("Level_1", shader, this));
		curScene = scenes.begin();
	}
	void update(GLFWwindow* window, float dt)
	{
		(*curScene)->update(window, dt);
	}
	void draw() const
	{
		(*curScene)->draw();
	}
	void changeScene()
	{
		(std::next(curScene) == scenes.end()) ? curScene = scenes.begin() : curScene++;
	}
private:
	std::vector<std::unique_ptr<Scene>> scenes;
	std::vector<std::unique_ptr<Scene>>::iterator curScene;
};