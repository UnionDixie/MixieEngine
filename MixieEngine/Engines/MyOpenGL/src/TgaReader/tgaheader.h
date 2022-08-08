#pragma once

namespace Tga {

#pragma pack(push,1)
	struct TgaHeader {
		char idLength;
		char colorMapType;
		char dataTypeCode;
		short colorMapOrigin;
		short colorMapLength;
		char colorMapDepth;
		short xOrigin;
		short yOrigin;
		short width;
		short height;
		char  bitsPerPixel;
		char  imageDescriptor;
	};
#pragma pack(pop)

}