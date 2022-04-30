#pragma once

#include "IndexedTriangleList.h"
#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Colors.h"

class Cube
{
public:
	template <typename T> 
	static IndexedTriangleList<T> GetIndexedVertices(float size, Color color)
	{
		std::vector<glm::vec3> vertices;

		const float side = size / 2.0f;
		vertices.reserve(24);

		vertices.emplace_back( -side,-side,-side ); // 0 near side
		vertices.emplace_back( side,-side,-side ); // 1
		vertices.emplace_back( -side,side,-side ); // 2
		vertices.emplace_back( side,side,-side ); // 3
		vertices.emplace_back( -side,-side,side ); // 4 far side
		vertices.emplace_back( side,-side,side ); // 5
		vertices.emplace_back( -side,side,side ); // 6
		vertices.emplace_back( side,side,side ); // 7
		vertices.emplace_back( -side,-side,-side ); // 8 left side
		vertices.emplace_back( -side,side,-side ); // 9
		vertices.emplace_back( -side,-side,side ); // 10
		vertices.emplace_back( -side,side,side ); // 11
		vertices.emplace_back( side,-side,-side ); // 12 right side
		vertices.emplace_back( side,side,-side ); // 13
		vertices.emplace_back( side,-side,side ); // 14
		vertices.emplace_back( side,side,side ); // 15
		vertices.emplace_back( -side,-side,-side ); // 16 bottom side
		vertices.emplace_back( side,-side,-side ); // 17
		vertices.emplace_back( -side,-side,side ); // 18
		vertices.emplace_back( side,-side,side ); // 19
		vertices.emplace_back( -side,side,-side ); // 20 top side
		vertices.emplace_back( side,side,-side ); // 21
		vertices.emplace_back( -side,side,side ); // 22
		vertices.emplace_back( side,side,side ); // 23

		std::vector<T> verts;
		verts.reserve(size_t(vertices.size() * 6));
		int i = 0;
		for (auto& v : vertices)
		{
			verts.emplace_back((T)v.x);
			verts.emplace_back((T)v.y);
			verts.emplace_back((T)v.z);
			verts.emplace_back((T)color.r);
			verts.emplace_back((T)color.g);
			verts.emplace_back((T)color.b);
		}

		return{
			std::move(verts),{
				0,2,1,    2,3,1,
				4,5,7,    4,7,6,
				8,10,9,   10,11,9,
				12,13,15, 12,15,14,
				16,17,18, 18,17,19,
				20,23,21, 20,22,23
			}
		};
	}
};