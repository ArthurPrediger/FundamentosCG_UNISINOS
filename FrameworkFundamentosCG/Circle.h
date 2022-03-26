#pragma once

#include <vector>
static constexpr float PI = 3.14159265359;

class Circle
{
public:
	static std::vector<float> Make(float radius, std::pair<float, float> center, int width, int height, int nVertices = 20)
	{
		const float halfWidth = width / 2.0f;
		const float halfHeight = height / 2.0f;

		std::vector<float> vertices;
		vertices.push_back(center.first / halfWidth);
		vertices.push_back(center.second / height / 2);
		vertices.push_back(0.0f);

		vertices.reserve(float(nVertices + 1) * 3);
		const float angle = 2 * PI / (float)nVertices;
		for (float i = 0; i < nVertices; i++)
		{
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

class Pizza
{
public:
	static std::vector<float> Make(float radius, std::pair<float, float> center, int width, int height)
	{
		const float halfWidth = width / 2.0f;
		const float halfHeight = height / 2.0f;

		const int nVertices = 34;
		std::vector<float> vertices;
		vertices.push_back(center.first / halfWidth);
		vertices.push_back(center.second / halfHeight);
		vertices.push_back(0.0f);

		vertices.reserve(6 * 3);
		const float angle = 2 * PI / (float)nVertices;
		for (float i = 6; i < 12; i++)
		{
			float x = (cos(i * angle) * radius + center.first) / halfWidth;
			float y = (sin(i * angle) * radius + center.second) / halfHeight;
			vertices.push_back(x);
			vertices.push_back(y);
			vertices.push_back(0.0f);
		}

		return vertices;
	}
};