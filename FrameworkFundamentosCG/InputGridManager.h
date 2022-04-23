#pragma once

#include "Grid.h"

template <typename T>
class InputGridManager
{
public:
	InputGridManager(Grid<T>& grid)
		:
		grid(grid)
	{}
	void Update(GLFWwindow* window, std::vector<T>& triangles , float dt_in)
	{
		dt += dt_in;
		if (dt > 0.1f)
		{
			if (cp == CoordinatePlane::XY)
			{
				if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
					(selectedCubePos.x == grid.GetUnitsWidth() - 1) ? selectedCubePos.x = 0 : selectedCubePos.x++;
				if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
					(selectedCubePos.x == 0) ? selectedCubePos.x = grid.GetUnitsWidth() - 1 : selectedCubePos.x--;
				if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
					(selectedCubePos.y == grid.GetUnitsHeight() - 1) ? selectedCubePos.y = 0 : selectedCubePos.y++;
				if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
					(selectedCubePos.y == 0) ? selectedCubePos.y = grid.GetUnitsHeight() - 1 : selectedCubePos.y--;
				if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
					cp = CoordinatePlane::XZ;

				selectedCubeIndex = selectedCubePos.z * grid.GetUnitsHeight() * grid.GetUnitsWidth() + 
					selectedCubePos.y * grid.GetUnitsWidth() + selectedCubePos.x;
			}
			else if(cp == CoordinatePlane::XZ)
			{
				if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
					(selectedCubePos.x == grid.GetUnitsWidth() - 1) ? selectedCubePos.x = 0 : selectedCubePos.x++;
				if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
					(selectedCubePos.x == 0) ? selectedCubePos.x = grid.GetUnitsWidth() - 1 : selectedCubePos.x--;
				if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
					(selectedCubePos.z == grid.GetUnitsHeight() - 1) ? selectedCubePos.z = 0 : selectedCubePos.z++;
				if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
					(selectedCubePos.z == 0) ? selectedCubePos.z = grid.GetUnitsHeight() - 1 : selectedCubePos.z--;
				if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
					cp = CoordinatePlane::XY;

				selectedCubeIndex = selectedCubePos.z * grid.GetUnitsHeight() * grid.GetUnitsWidth() +
					selectedCubePos.y * grid.GetUnitsWidth() + selectedCubePos.x;
			}
			
			if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
			{
				if (grid.RenderCube(selectedCubeIndex))
				{
					grid.RemoveCubeColor(selectedCubeIndex);
				}
				else
				{
					grid.ApplyCubeColor(selectedCubeIndex, selectedColor);
				}
			}

			Colors color = Colors::Default;
			if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS)
				color = Colors::White;
			else if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
				color = Colors::Black;
			else if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
				color = Colors::Blue;
			else if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
				color = Colors::Orange;
			else if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
				color = Colors::Green;
			else if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)
				color = Colors::Yellow;
			else if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS)
				color = Colors::Magenta;
			else if (glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS)
				color = Colors::Purple;
			else if (glfwGetKey(window, GLFW_KEY_8) == GLFW_PRESS)
				color = Colors::Red;
			else if (glfwGetKey(window, GLFW_KEY_9) == GLFW_PRESS)
				color = Colors::Brown;

			switch (color)
			{
			case Colors::White:
				selectedColor = { 1.0f, 1.0f, 1.0f, 1.0f };
				break;
			case Colors::Black:
				selectedColor = { 0.0f, 0.0f, 0.0f, 1.0f };
				break;
			case Colors::Blue:
				selectedColor = { 0.0f, 0.0f, 1.0f, 1.0f };
				break;
			case Colors::Orange:
				selectedColor = { 1.0f, 153.0f / 255.0f, 51.0f / 255.0f, 1.0f };
				break;
			case Colors::Green:
				selectedColor = { 0.0f, 1.0f, 0.0f, 1.0f };
				break;
			case Colors::Yellow:
				selectedColor = { 1.0f, 1.0f, 0.0f, 1.0f };
				break;
			case Colors::Magenta:
				selectedColor = { 1.0f, 0.0f, 1.0f, 1.0f };
				break;
			case Colors::Purple:
				selectedColor = { 102.0f / 255.0f, 0.0f, 204.0f / 255.0f, 1.0f };
				break;
			case Colors::Red:
				selectedColor = { 1.0f, 0.0f, 0.0f, 1.0f };
				break;
			case Colors::Brown:
				selectedColor = { 165.0f / 255.0f, 42.0f / 255.0f, 42.0f / 255.0f, 1.0f };
				break;
			default:
				break;
			}

			dt = 0.0f;
		}

		float cubesSize = grid.GetCubesSize();
		IndexedTriangleList<T> selCubeVerts = Cube::GetIndexedVertices<T>(cubesSize, { 1.0f, 0.0f, 0.0f, 1.0f });

		for (int i = 0; i < selCubeVerts.vertices.size(); i += 3)
		{
			selCubeVerts.vertices[i++] += (float(selectedCubePos.x) - float(grid.GetUnitsWidth()) / 2.0f) * cubesSize;
			selCubeVerts.vertices[i++] += (float(selectedCubePos.y) - float(grid.GetUnitsHeight()) / 2.0f) * cubesSize;
			selCubeVerts.vertices[i++] += (float(selectedCubePos.z) - float(grid.GetUnitsDepth()) / 2.0f) * cubesSize;
		}
		
		const auto& vertices = selCubeVerts.vertices;
		const auto& indices = selCubeVerts.indices;

		for (int i = 0; i < indices.size(); i++)
		{
			int offset = (indices[i]) * 6;
			triangles.insert(triangles.end(), vertices.begin() + offset, vertices.begin() + offset + 6);
			offset = (indices[++i]) * 6;
			triangles.insert(triangles.end(), vertices.begin() + offset, vertices.begin() + offset + 6);
			offset = (indices[++i]) * 6;
			triangles.insert(triangles.end(), vertices.begin() + offset, vertices.begin() + offset + 6);
		}
	}
private:
	enum class CoordinatePlane { XY, XZ };
	enum class Colors { White, Black, Blue, Orange, Green, Yellow, Magenta, Purple, Red, Brown, Default };
private:
	Grid<T>& grid;
	glm::ivec3 selectedCubePos = { 0, 0, grid.GetUnitsDepth() - 1};
	int selectedCubeIndex = 0;
	Color selectedColor = { 0.0f, 0.0f, 0.0f, 1.0f };
	float dt = 0.0f;
	CoordinatePlane cp = CoordinatePlane::XY;
};