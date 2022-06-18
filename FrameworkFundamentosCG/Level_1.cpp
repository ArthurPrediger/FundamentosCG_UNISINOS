#include "Level_1.h"

Level_1::Level_1(const std::string name, Shader* shader)
	:
	Scene(name),
	shader(shader)
{
	std::vector<int> tileMap;

	tileMap.insert(tileMap.end(),
		{ 1, 1, 0, 0, 1, 0, 1, 0, 0, 0,
		  0, 1, 0, 1, 1, 1, 1, 0, 0, 0,
		  0, 1, 1, 1, 1, 1, 1, 0, 0, 1,
		  0, 0, 0, 1, 1, 0, 1, 1, 1, 1,
		  0, 0, 0, 1, 0, 1, 1, 0, 0, 0,
		  0, 1, 0, 1, 1, 1, 1, 0, 0, 0,
		  0, 1, 1, 1, 1, 0, 1, 1, 1, 0,
		  0, 1, 0, 1, 1, 1, 1, 0, 1, 0,
		  0, 0, 0, 1, 1, 0, 1, 0, 1, 1,
		  0, 1, 1, 0, 1, 0, 1, 0, 1, 1 });

	std::vector<std::string> tilesTypes = {
		"water",
		"ground"
	};

	std::vector<std::string> tileSetPaths = {
		"../TileSets/Solid_Tiles_Flat_128x88.png", 
		"../TileSets/Ground_Rocky1_256x128.png"
	};

	std::vector<glm::vec2> normalizedTexturesDimensions = { 
		{ 1.0f / 6.0f, 1.0f },
		{ 1.0f / 3.0f, 1.0f / 5.0f }
	};

	std::vector<glm::vec2> tileSetOffsets = { 
		{ 5.0f / 6.0f, 0.0f },
		{ 2.0f / 3.0f, 3.0f / 5.0f }
	};

	tf = { xDimField, yDimField, 
		   std::move(tileMap), 
		   std::move(tilesTypes),
		   std::move(tileSetPaths), 
		   std::move(normalizedTexturesDimensions), 
		   { 480.0f, 180.0f },
		   std::move(tileSetOffsets), 
		   shader };

	auto pos = tf.getTilePosition(initialCharPos.y * xDimField + initialCharPos.x);
	character = std::make_unique<Character>(shader, pos, glm::vec2{60.0f, 75.0f});
}

void Level_1::update(GLFWwindow* window, float dt)
{
	time += dt;
	if (!resetting)
	{
		handleInput(window);
	}
	else
	{
		reset();
	}
	character->update(dt);
}

void Level_1::draw()
{
	tf.draw();
	character->draw();
}

void Level_1::handleInput(GLFWwindow* window)
{
	const auto holdTime = 0.5f;
	const auto prevPos = charFieldPos;

	// east
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS && 
		charFieldPos.x < xDimField - 1 && charFieldPos.y > 0
		&& time > holdTime)
		charFieldPos += glm::ivec2{ 1, -1 };
	// west
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS && 
		charFieldPos.x > 0 && charFieldPos.y < yDimField - 1
		&& time > holdTime)
		charFieldPos += glm::ivec2{ -1, 1 };
	// north
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS &&
		charFieldPos.x < xDimField - 1 && charFieldPos.y < yDimField - 1
		&& time > holdTime)
		charFieldPos += glm::ivec2{ 1, 1 };
	// south
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS &&
		charFieldPos.x > 0 && charFieldPos.y > 0
		&& time > holdTime)
		charFieldPos += glm::ivec2{ -1, -1 };
	// northeast
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS &&
		charFieldPos.x < xDimField - 1 && time > holdTime)
		charFieldPos += glm::ivec2{ 1, 0 };
	// northwest
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS &&
		charFieldPos.y < yDimField - 1 && time > holdTime)
		charFieldPos += glm::ivec2{ 0, 1 };
	// southeast
	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS &&
		charFieldPos.y > 0 && time > holdTime)
		charFieldPos += glm::ivec2{ 0, -1 };
	// southwest
	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS &&
		charFieldPos.x > 0 && time > holdTime)
		charFieldPos += glm::ivec2{ -1, 0 };

	auto index = charFieldPos.y * xDimField + charFieldPos.x;
	if (charFieldPos != prevPos)
	{
		charDir = glm::normalize(tf.getTilePosition(index) - character->getPosition());
		time = 0.0f;
	}
	if (glm::dot(tf.getTilePosition(index) - character->getPosition(), charDir) < 0)
	{
		charDir = { 0.0f, 0.0f };
	}

	character->setDirection(charDir);
	CheckWinLoseCases();
}

void Level_1::CheckWinLoseCases()
{
	if (tf.getTileType(charFieldPos.y * xDimField + charFieldPos.x) == "water")
	{
		reset();
	}
}

void Level_1::reset()
{
	if (!resetting)
	{
		resetting = true;
		time = 0.0f;
	}
	if (charDir != glm::vec2{ 0.0f, 0.0f } &&
		glm::dot(tf.getTilePosition(charFieldPos.y * xDimField + charFieldPos.x) - character->getPosition(), charDir) < 0)
	{
		charDir = { 0.0f, 0.0f };
		character->setDirection(charDir);
	}
	else if (time >= 2.0f)
	{
		resetting = false;
		time = 0.0f;
		charFieldPos = initialCharPos;
		character->setPosition(tf.getTilePosition(charFieldPos.y * xDimField + charFieldPos.x));
		character->setDirection({ 0.0f, 1.0f }); // Lazy way of setting character to look up
		character->setDirection(charDir);
	}
}
