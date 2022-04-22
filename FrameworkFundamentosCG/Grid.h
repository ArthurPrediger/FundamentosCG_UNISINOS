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

		for (int z = -unitsDepth / 2; z < unitsDepth / 2; z++)
		{
			for (int y = -unitsHeight / 2; y < unitsHeight / 2; y++)
			{
				for (int x = -unitsWidth / 2; x < unitsWidth / 2; x++)
				{
					IndexedTriangleList<T> iVerts = Cube::GetIndexedVertices<T>(cubesSize, {0.0f, 0.0f, 0.0f, 1.0f});
					
					for (int i = 0; i < iVerts.vertices.size(); i += 3)
					{
						iVerts.vertices[i++] += x * cubesSize;
						iVerts.vertices[i++] += y * cubesSize;
						iVerts.vertices[i++] += z * cubesSize;
					}

					cubesVertices.emplace_back(iVerts);
					renderBuffer.emplace_back(false);
				}
			}
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
	bool RenderCube(int pos) const
	{
		return renderBuffer[pos];
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
