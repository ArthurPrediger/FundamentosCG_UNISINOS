#pragma once

#include "IndexedTriangleList.h"
#include "TileField.h"

class Scene
{
public:
	Scene(Shader* shader);
	void draw() const;
private:
	TileField tf;
};