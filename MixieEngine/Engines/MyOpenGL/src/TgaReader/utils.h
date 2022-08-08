#pragma once

#include "tgaimage.h"

namespace Tga {

	struct Point
	{
		int x;
		int y;
	};

	void line(Point p1, Point p2, TgaImage& image, const TGAColor color)
	{
        bool steep = false;
        if (std::abs(p1.x - p2.x) < std::abs(p1.y - p2.y)) { // if the line is steep, we transpose the image
            std::swap(p1.x, p1.y);
            std::swap(p2.x, p2.y);
            steep = true;
        }
        if (p1.x > p2.x) { // make it left-to-right
            std::swap(p1.x, p2.x);
            std::swap(p1.y, p2.y);
        }

        for (int x = p1.x; x <= p2.x; x++) {
            float t = (x - p1.x) / (float)(p2.x - p1.x);
            int y = p1.y * (1. - t) + p2.y * t;
            if (steep) {
                image.set(y, x, color); // if transposed, de-transpose
            }
            else {
                image.set(x, y, color);
            }
        }
	}


}