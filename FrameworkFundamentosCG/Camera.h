#pragma once

#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera
{
public:
	Camera() = default;
	const glm::vec3& GetPos() const
	{
		return cameraPos;
	}
	void SetPos(const glm::vec3& pos)
	{
		cameraPos = pos;
	}
	const glm::vec3& GetFront() const
	{
		return cameraFront;
	}
	void SetFront(const glm::vec3& front)
	{
		cameraFront = front;
	}
	const glm::vec3& GetUp() const
	{
		return cameraUp;
	}
	void SetUp(const glm::vec3& up)
	{
		cameraUp = up;
	}
	void updateCameraPos(GLFWwindow* window, float dt)
	{
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			cameraPos += cameraSpeed * cameraFront * dt;

		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			cameraPos -= cameraSpeed * cameraFront * dt;

		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed * dt;

		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed * dt;
	}
private:
	float cameraSpeed = 5.0f;
	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
};