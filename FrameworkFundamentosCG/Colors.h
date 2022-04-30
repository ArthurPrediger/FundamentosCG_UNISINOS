#pragma once

struct Color
{
	float r;
	float g;
	float b;
	float a;
};

namespace Colors
{
	static constexpr Color White = { 1.0f, 1.0f, 1.0f, 1.0f };
	static constexpr Color Black = { 0.0f, 0.0f, 0.0f, 1.0f };
	static constexpr Color Blue = { 0.0f, 0.0f, 1.0f, 1.0f };
	static constexpr Color Orange = { 1.0f, 153.0f / 255.0f, 51.0f / 255.0f, 1.0f };
	static constexpr Color Green = { 0.0f, 1.0f, 0.0f, 1.0f };
	static constexpr Color Yellow = { 1.0f, 1.0f, 0.0f, 1.0f };
	static constexpr Color Magenta = { 1.0f, 0.0f, 1.0f, 1.0f };
	static constexpr Color Purple = { 102.0f / 255.0f, 0.0f, 204.0f / 255.0f, 1.0f };
	static constexpr Color Red = { 1.0f, 0.0f, 0.0f, 1.0f };
	static constexpr Color Brown = { 165.0f / 255.0f, 42.0f / 255.0f, 42.0f / 255.0f, 1.0f };
}
