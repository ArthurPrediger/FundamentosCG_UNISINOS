#pragma once

#include "Grid.h"

static constexpr float PI = 3.14159265359;

Color ColorBlend(Color c1, Color c2, float alpha)
{
	Color color = Colors::Black;
	color.r = (c1.r * alpha + c2.r * (1.0f - alpha));
	color.g = (c1.g * alpha + c2.g * (1.0f - alpha));
	color.b = (c1.b * alpha + c2.b * (1.0f - alpha));

	return color;
};

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

			if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS)
				selectedColor = Colors::White;
			else if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
				selectedColor = Colors::Black;
			else if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
				selectedColor = Colors::Blue;
			else if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
				selectedColor = Colors::Orange;
			else if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
				selectedColor = Colors::Green;
			else if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)
				selectedColor = Colors::Yellow;
			else if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS)
				selectedColor = Colors::Magenta;
			else if (glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS)
				selectedColor = Colors::Purple;
			else if (glfwGetKey(window, GLFW_KEY_8) == GLFW_PRESS)
				selectedColor = Colors::Red;
			else if (glfwGetKey(window, GLFW_KEY_9) == GLFW_PRESS)
				selectedColor = Colors::Brown;

			dt = 0.0f;
		}

		float cubesSize = grid.GetCubesSize();
		(alpha > 2.0f) ? alpha = 0.0f : alpha += dt_in;
		Color cubeColor = ColorBlend(Colors::Red, grid.GetCubeColor(selectedCubeIndex), std::abs(sin(alpha * PI)));
		IndexedTriangleList<T> selCubeVerts = Cube::GetIndexedVertices<T>(cubesSize, cubeColor);

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

		grid.InsertCubesTriangles(triangles);
	}
private:
	enum class CoordinatePlane { XY, XZ };
private:
	Grid<T>& grid;
	glm::ivec3 selectedCubePos = { 0, 0, grid.GetUnitsDepth() - 1};
	int selectedCubeIndex = 0;
	Color selectedColor = Colors::Black;
	float dt = 0.0f;
	float alpha = 0.0f;
	CoordinatePlane cp = CoordinatePlane::XY;
};