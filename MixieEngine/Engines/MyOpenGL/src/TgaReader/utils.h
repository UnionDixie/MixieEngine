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
        if (std::abs(p1.x - p2.x) < std::abs(p1.y - p2.y)) {
            std::swap(p1.x, p1.y);
            std::swap(p2.x, p2.y);
            steep = true;
        }
        if (p1.x > p2.x) {
            std::swap(p1.x, p2.x);
            std::swap(p1.y, p2.y);
        }
        int dx = p2.x - p1.x;
        int dy = p2.y - p1.y;
        int derror2 = std::abs(dy) * 2;
        int error2 = 0;
        int y = p1.y;
        for (int x = p1.x; x <= p2.x; x++) {
            if (steep) {
                image.set(y, x, color);
            }
            else {
                image.set(x, y, color);
            }
            error2 += derror2;

            if (error2 > dx) {
                y += (p2.y > p1.y ? 1 : -1);
                error2 -= dx * 2;
            }
        }
	}


}