#pragma once

#include <fstream>

#include "tgaheader.h"
#include "tgacolor.h"

namespace Tga {

	class TgaImage {
	public:
		enum Format {
			GRAYSCALE = 1, RGB = 3, RGBA = 4
		};

		TgaImage() = default;
		TgaImage(int w, int h, int bpp);
		TgaImage(const TgaImage& img);
		bool read_tga_file(const char* filename);
		bool write_tga_file(const char* filename, bool rle = true);
		bool flip_horizontally();
		bool flip_vertically();
		bool scale(int w, int h);
		TGAColor get(int x, int y);
		bool set(int x, int y, TGAColor c);
		~TgaImage();
		TgaImage& operator =(const TgaImage& img);
		int get_width();
		int get_height();
		int get_bytespp();
		unsigned char* buffer();
		void clear();
	protected:
		unsigned char* data = nullptr;
		int width = 0;
		int height = 0;
		int bytespp = 0;

		bool load_rle_data(std::ifstream& in);
		bool unload_rle_data(std::ofstream& out);
	};

}