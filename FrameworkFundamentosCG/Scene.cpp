#include "Scene.h"

Scene::Scene(GLuint shaderID)
	:
	shaderID(shaderID)
{
	GameObject skyline = GameObject::createGameObject();
	skyline.transform.translation = glm::vec3(400.0f, 300.0f, 0.0f);
	skyline.transform.rotation = glm::vec3(0.0f, 0.0f, glm::pi<float>());
	skyline.transform.scale = glm::vec3(800.0f, 600.0f, 1.0f);
	skyline.model = std::make_shared<Model>(triangles, "../Textures/skyline.png", skyline.transform.mat4());

	gameObjects.push_back(std::move(skyline));

	GameObject buildings = GameObject::createGameObject();
	buildings.transform.translation = glm::vec3(150.0f, 190.0f, 0.0f);
	buildings.transform.rotation = glm::vec3(0.0f, 0.0f, glm::pi<float>());
	buildings.transform.scale = glm::vec3(300.0f, 200.0f, 1.0f);
	buildings.model = std::make_shared<Model>(triangles, "../Textures/buildings_bg.png", buildings.transform.mat4());

	gameObjects.push_back(std::move(buildings));

	GameObject near_buildings = GameObject::createGameObject();
	near_buildings.transform.translation = glm::vec3(550.0f, 230.0f, 0.0f);
	near_buildings.transform.rotation = glm::vec3(0.0f, 0.0f, glm::pi<float>());
	near_buildings.transform.scale = glm::vec3(550.0f, 280.0f, 1.0f);
	near_buildings.model = std::make_shared<Model>(triangles, "../Textures/near_buildings_bg.png", near_buildings.transform.mat4());

	gameObjects.push_back(std::move(near_buildings));

	GameObject pavement = GameObject::createGameObject();
	pavement.transform.translation = glm::vec3(400.0f, 45.0f, 0.0f);
	pavement.transform.rotation = glm::vec3(0.0f, 0.0f, glm::pi<float>());
	pavement.transform.scale = glm::vec3(800.0f, 90.0f, 1.0f);
	pavement.model = std::make_shared<Model>(triangles, "../Textures/pavement.png", pavement.transform.mat4());

	gameObjects.push_back(std::move(pavement));

	GameObject truck = GameObject::createGameObject();
	truck.transform.translation = glm::vec3(120.0f, 150.0f, 0.0f);
	truck.transform.rotation = glm::vec3(0.0f, 0.0f, glm::pi<float>());
	truck.transform.scale = glm::vec3(140.0f, 60.0f, 1.0f);
	truck.model = std::make_shared<Model>(triangles, "../Textures/truck.png", truck.transform.mat4());

	gameObjects.push_back(std::move(truck));

	GameObject police_car = GameObject::createGameObject();
	police_car.transform.translation = glm::vec3(650.0f, 230.0f, 0.0f);
	police_car.transform.rotation = glm::vec3(0.0f, 0.0f, glm::pi<float>());
	police_car.transform.scale = glm::vec3(240.0f, 100.0f, 1.0f);
	police_car.model = std::make_shared<Model>(triangles, "../Textures/police_car.png", police_car.transform.mat4());

	gameObjects.push_back(std::move(police_car));

	GameObject drone = GameObject::createGameObject();
	drone.transform.translation = glm::vec3(700.0f, 180.0f, 0.0f);
	drone.transform.rotation = glm::vec3(0.0f, 0.0f, glm::pi<float>());
	drone.transform.scale = glm::vec3(80.0f, 80.0f, 1.0f);
	drone.model = std::make_shared<Model>(triangles, "../Textures/drone_1.png", drone.transform.mat4());

	gameObjects.push_back(std::move(drone));

	GameObject character = GameObject::createGameObject();
	character.transform.translation = glm::vec3(310.0f, 140.0f, 0.0f);
	character.transform.rotation = glm::vec3(0.0f, 0.0f, glm::pi<float>());
	character.transform.scale = glm::vec3(200.0f, 200.0f, 1.0f);
	character.model = std::make_shared<Model>(triangles, "../Textures/character.png", character.transform.mat4());

	gameObjects.push_back(std::move(character));
}

void Scene::draw() const
{
	for (auto& obj : gameObjects)
	{
		obj.model->draw(shaderID);
	}
}
