#pragma once

#include <vector>
static constexpr float PI = 3.14159265359;

class Star
{
public:
	static std::vector<float> Make(float outerRadius, float innerRadius, std::pair<float, float> center = { 0.0f, 0.0f }, int nFlares = 5)
	{
		std::vector<float> vertices;
		vertices.reserve(float(nFlares + 2) * 2 * 3);

		vertices.push_back(center.first);
		vertices.push_back(center.second);
		vertices.push_back(0.0f);

		const float angle = 2.0f * PI / float(nFlares * 2);
		for (int i = 0; i < nFlares * 2; i++)
		{
			const float radius = (i % 2 == 0) ? outerRadius : innerRadius;
			float x = (cos(i * angle) * radius + center.first);
			float y = (sin(i * angle) * radius + center.second);
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