#pragma once

#include "Cube.h"

template <typename T>
class Grid
{
public:
	Grid(float cubesSize, int unitsWidth, int unitsHeight, int unitsDepth)
		:
		cubesSize(cubesSize),
		unitsWidth(unitsWidth),
		unitsHeight(unitsHeight),
		unitsDepth(unitsDepth)
	{
		const size_t numCubes = size_t(unitsWidth * unitsHeight * unitsDepth);
		cubesVertices.reserve(numCubes);
		renderBuffer.reserve(numCubes);

		for (int z = 0; z < unitsDepth; z++)
		{
			for (int y = 0; y < unitsHeight; y++)
			{
				for (int x = 0; x < unitsWidth; x++)
				{
					IndexedTriangleList<T> iVerts = Cube::GetIndexedVertices<T>(cubesSize, Colors::Black);
					
					for (int i = 0; i < iVerts.vertices.size(); i += 3)
					{
						iVerts.vertices[i++] += (T(x) - T(unitsWidth) / (T)2) * cubesSize;
						iVerts.vertices[i++] += (T(y) - T(unitsHeight) / (T)2) * cubesSize;
						iVerts.vertices[i++] += (T(z) - T(unitsDepth) / (T)2) * cubesSize;
					}

					cubesVertices.emplace_back(iVerts);
					renderBuffer.emplace_back(false);
				}
			}
		}
	}
	float GetCubesSize() const
	{
		return cubesSize;
	}
	Color GetCubeColor(int cubeIndex)
	{
		if (RenderCube(cubeIndex))
		{
			auto vertices = cubesVertices[cubeIndex].vertices;

			Color color = Colors::Black;
			int i = 3;
			color.r = vertices[i++];
			color.g = vertices[i++];
			color.b = vertices[i];

			return color;
		}
		else
		{
			return backgroundColor;
		}
	}
	int GetUnitsWidth() const
	{
		return unitsWidth;
	}
	int GetUnitsHeight() const
	{
		return unitsHeight;
	}
	int GetUnitsDepth() const
	{
		return unitsDepth;
	}
	int GetTotalNumCubes() const
	{
		return unitsWidth * unitsHeight * unitsDepth;
	}
	bool RenderCube(int pos) const
	{
		return renderBuffer[pos];
	}
	void ApplyCubeColor(int cubeIndex, Color color)
	{
		auto& cubeVerts = cubesVertices[cubeIndex].vertices;

		for (int i = 3; i < cubeVerts.size(); i += 3)
		{
			cubeVerts[i++] = color.r;
			cubeVerts[i++] = color.g;
			cubeVerts[i++] = color.b;
		}

		renderBuffer[cubeIndex] = true;
	}
	void RemoveCubeColor(int cubeIndex)
	{
		renderBuffer[cubeIndex] = false;
	}
	void InsertCubesTriangles(std::vector<T>& triangles)
	{
		int cubeIndex = 0;
		for (int z = 0; z < GetUnitsDepth(); z++)
		{
			for (int y = 0; y < GetUnitsHeight(); y++)
			{
				for (int x = 0; x < GetUnitsWidth(); x++, cubeIndex++)
				{
					if (!RenderCube(cubeIndex))
						continue;

					const auto& vertices = cubesVertices[cubeIndex].vertices;
					const auto& indices = cubesVertices[cubeIndex].indices;

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
			}
		}
	}
	void InsertGridVertices(std::vector<T>& vertices)
	{
		if (gridLinesUpdate)
		{
			std::vector<T> gridVertsIndices{
				0, 1, 3, 2, // front side
				0, 4, 5, 1, // bottom sidde
				3, 7, 5, // left side
				7, 6, 4, // back side
				0, 2, 6, //right side
				// top is drawn indirectly
			};

			std::vector<T> gridVerts;

			for (int z = -1; z < 2; z += 2)
			{
				for (int y = -1; y < 2; y += 2)
				{
					for (int x = -1; x < 2; x += 2)
					{
						gridVerts.emplace_back(T(x) * T((float)unitsWidth / 2.0f * cubesSize) - (T)cubesSize / (T)2);
						gridVerts.emplace_back(T(y) * T((float)unitsHeight / 2.0f * cubesSize) - (T)cubesSize / (T)2);
						gridVerts.emplace_back(T(z * (-1)) * T((float)unitsDepth / 2.0f * cubesSize) - (T)cubesSize / (T)2);
						gridVerts.emplace_back(colorGridLines.r);
						gridVerts.emplace_back(colorGridLines.g);
						gridVerts.emplace_back(colorGridLines.b);
					}
				}
			}

			for (int i = 0; i < gridVertsIndices.size(); i++)
			{
				int offset = (gridVertsIndices[i]) * 6;
				gridVertices.insert(gridVertices.end(), gridVerts.begin() + offset, gridVerts.begin() + offset + 6);
			}

			vertices.insert(vertices.end(), gridVertices.begin(), gridVertices.end());

			gridLinesUpdate = false;
		}
		else
		{
			vertices.insert(vertices.end(), gridVertices.begin(), gridVertices.end());
		}
	}
private:
	float cubesSize;
	int unitsWidth;
	int unitsHeight;
	int unitsDepth;
	std::vector<bool> renderBuffer;
	std::vector<IndexedTriangleList<T>> cubesVertices;
	std::vector<T> gridVertices;
	Color colorGridLines = Colors::Black;
	bool gridLinesUpdate = true;
	Color backgroundColor = Colors::Gray;
};
