#pragma once

#include <vector>

static constexpr float PI = 3.14159265359;

class Square
{
public:
	static std::vector<float> Make(float squareSideLength = 20.0f)
	{
		std::vector<float> vertices;
		vertices.reserve(size_t(4 * 3));

		for (int y = 0; y < 2; y++)
		{
			for (int x = 0; x < 2; x++)
			{
				vertices.push_back(float(x) * squareSideLength);
				vertices.push_back(float(y) * squareSideLength);
				vertices.push_back(0.0f);
			}
		}

		return vertices;
	}
};