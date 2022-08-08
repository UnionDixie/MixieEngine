#include "TgaReader/tgaimage.h"
#include "TgaReader/utils.h"

using namespace Tga;
const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red = TGAColor(255, 0, 0, 255);

int main(int argc, char** argv)
{
	TgaImage image(100, 100, TgaImage::RGB);
	image.set(52, 41, red);
	image.flip_vertically(); // i want to have the origin at the left bottom corner of the image

	line(Point{ 10, 10 }, Point{ 70, 70 }, image, white);

	image.write_tga_file("output.tga");

	return 0;
}