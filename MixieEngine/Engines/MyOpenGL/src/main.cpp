#include "TgaReader/TgaReader.h"

using namespace Tga;
const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red = TGAColor(255, 0, 0, 255);

int main(int argc, char** argv)
{
	TgaReader image(100, 100, TgaReader::RGB);
	image.set(52, 41, red);
	image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
	image.write_tga_file("output.tga");

	return 0;
}