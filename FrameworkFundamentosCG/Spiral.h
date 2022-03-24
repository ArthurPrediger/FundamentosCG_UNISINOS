#pragma once

#pragma once

#include <vector>
static constexpr float PI = 3.14159265359;

class Spiral
{
public:
	static std::vector<float> Make(int width, int height, float maxRadius = 300.0f, int nLaps = 3, 
		std::pair<float, float> center = { 0.0f, 0.0f }, int nVertices = 500)
	{
		std::vector<float> vertices;
		vertices.reserve(float(nVertices + 1) * 3);

		vertices.push_back(center.first / width);
		vertices.push_back(center.second / height);
		vertices.push_back(0.0f);
 
		const float dTheta = 2 * PI * nLaps / (float)nVertices;
		const float dRadius = maxRadius / (float)nVertices;
		float radius = 0.0f;
		for (int i = 0; i < nVertices; i++, radius += dRadius)
		{
			const float angle = i * dTheta;
			float x = (cos(angle) * radius + center.first) / width;
			float y = (sin(angle) * radius + center.second) / height;
			vertices.push_back(x);
			vertices.push_back(y);
			vertices.push_back(0.0f);
		}

		return vertices;
	}
};
