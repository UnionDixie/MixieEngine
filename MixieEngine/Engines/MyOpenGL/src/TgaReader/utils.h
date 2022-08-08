#pragma once

#include "tgaimage.h"

namespace Tga {

	struct Point
	{
		int x;
		int y;
	};

	void line(const Point p1, const Point p2, TgaImage& image, const TGAColor color)
	{
		for (float t = 0.f; t < 1; t += 0.1f)
			image.set(
				p1.x * (1.f - t) + p2.x * t,
				p1.y * (1.f - t) + p2.y * t,
				color);
	}

}