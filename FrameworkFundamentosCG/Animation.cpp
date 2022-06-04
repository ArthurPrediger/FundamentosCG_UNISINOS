#include "Animation.h"

Animation::Animation(std::shared_ptr<Model> model, const IndexedTriangleList<Model::Vertex>& triangles,
	float x_first, float y_first, float dx, float dy, int count, const std::string& spritePath,
	float holdTime, glm::vec3 chroma)
	:
	model(model),
	triangles(triangles),
	spritePath(spritePath),
	holdTime(holdTime),
	chroma(chroma)
{
	for (int i = 0; i < count; i++)
	{
		framesOffsets.push_back({ x_first + dx * i, y_first + dy * i });
	}
}

void Animation::draw() const
{
	model->draw();
}

void Animation::update(float dt, Shader* shader, const glm::mat4& transformationMatrix)
{
	curFrameTime += dt;
	while (curFrameTime >= holdTime)
	{
		advance();
		curFrameTime -= holdTime;
	}

	shader->setVec2("offsets", framesOffsets[(size_t)iCurFrame].x, framesOffsets[(size_t)iCurFrame].y);
	model = std::make_shared<Model>(shader, triangles, spritePath, transformationMatrix);
}

void Animation::advance()
{
	iCurFrame++;
	if (iCurFrame >= (int)framesOffsets.size())
	{
		iCurFrame = 0;
	}
}