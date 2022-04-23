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
					IndexedTriangleList<T> iVerts = Cube::GetIndexedVertices<T>(cubesSize, {0.0f, 0.0f, 0.0f, 1.0f});
					
					for (int i = 0; i < iVerts.vertices.size(); i += 3)
					{
						iVerts.vertices[i++] += (float(x) - float(unitsWidth) / 2.0f) * cubesSize;
						iVerts.vertices[i++] += (float(y) - float(unitsHeight) / 2.0f) * cubesSize;
						iVerts.vertices[i++] += (float(z) - float(unitsDepth) / 2.0f) * cubesSize;
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
	const std::vector<IndexedTriangleList<T>>& GetCubesVertices() const
	{
		return cubesVertices;
	}
private:
	float cubesSize;
	int unitsWidth;
	int unitsHeight;
	int unitsDepth;
	std::vector<bool> renderBuffer;
	std::vector<IndexedTriangleList<T>> cubesVertices;
};
