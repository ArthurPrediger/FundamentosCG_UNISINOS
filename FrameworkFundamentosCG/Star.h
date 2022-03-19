#pragma once

#include <vector>

class Star
{
public:
	static std::vector<float> Make(float outerRadius,  float innerRadius, std::pair<float, float> center, int width, int height, int nFlares = 5)
	{
		std::vector<float> vertices;
		vertices.push_back(center.first / width);
		vertices.push_back(center.second / height);
		vertices.push_back(0.0f);

		vertices.reserve(nFlares * 2 * 3);
		const float angle = 2.0f * PI / float(nFlares * 2);
		for (int i = 0; i < nFlares * 2; i++)
		{
			const float radius = (i % 2 == 0) ? outerRadius : innerRadius;
			float x = (cos(i * angle) * radius + center.first) / width;
			float y = (sin(i * angle) * radius + center.second) / height;
			vertices.push_back(x);
			vertices.push_back(y);
			vertices.push_back(0.0f);
		}
		return vertices;
	}
};