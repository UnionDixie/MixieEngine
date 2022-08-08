#pragma once

#include <fstream>

#include "tgaheader.h"
#include "tgacolor.h"

namespace Tga {

	class TgaReader {
	public:
		enum Format {
			GRAYSCALE = 1, RGB = 3, RGBA = 4
		};

		TgaReader() = default;
		TgaReader(int w, int h, int bpp);
		TgaReader(const TgaReader& img);
		bool read_tga_file(const char* filename);
		bool write_tga_file(const char* filename, bool rle = true);
		bool flip_horizontally();
		bool flip_vertically();
		bool scale(int w, int h);
		TGAColor get(int x, int y);
		bool set(int x, int y, TGAColor c);
		~TgaReader();
		TgaReader& operator =(const TgaReader& img);
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