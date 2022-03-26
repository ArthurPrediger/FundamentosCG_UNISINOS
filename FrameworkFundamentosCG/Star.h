#pragma once

#include <vector>

class Star
{
public:
	static std::vector<float> Make(float outerRadius,  float innerRadius, std::pair<float, float> center, int width, int height, int nFlares = 5)
	{
		const float halfWidth = width / 2.0f;
		const float halfHeight = height / 2.0f;

		std::vector<float> vertices;
		vertices.push_back(center.first / halfWidth);
		vertices.push_back(center.second / halfHeight);
		vertices.push_back(0.0f);

		vertices.reserve(float(nFlares + 1) * 2 * 3);
		const float angle = 2.0f * PI / float(nFlares * 2);
		for (int i = 0; i < nFlares * 2; i++)
		{
			const float radius = (i % 2 == 0) ? outerRadius : innerRadius;
			float x = (cos(i * angle) * radius + center.first) / halfWidth;
			float y = (sin(i * angle) * radius + center.second) / halfHeight;
			vertices.push_back(x);
			vertices.push_back(y);
			vertices.push_back(0.0f);
		}

		for (int i = 3; i < 6; i++)
		{
			vertices.push_back(vertices[i]);
		}

		return vertices;
	}
};