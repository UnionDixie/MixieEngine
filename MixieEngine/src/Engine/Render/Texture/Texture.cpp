#include "Texture.h"

namespace Render {

	Texture::Texture(rawData data, Filters filter) : Data(data),Filter(filter)
	{
		glGenTextures(1, &id);
		glBindTexture(GL_TEXTURE_2D, id);
		auto [x, y, pixels, channels] = Data;
		GLenum mode;
		if (auto find = modeChannels.find(channels); find != modeChannels.end()) {
			mode = find->second;
		}
		else {
			mode = modeChannels.cend()->second;//RGBA
		}
		glTexImage2D(GL_TEXTURE_2D, 0, mode, x, y, 0, mode, GL_UNSIGNED_BYTE, pixels);
		auto [texFilter,wrapMode] = Filter;
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, texFilter);//GL_NEAREST
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, texFilter);//GL_LINEAR

		glGenerateMipmap(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 0);
	}
	Texture::Texture(Texture&& newTexture)
	{
		id = std::move(newTexture.id);
		Data = std::move(newTexture.Data);
		Filter = std::move(newTexture.Filter);
	}
	Texture& Texture::operator=(Texture&& newTexture)
	{
		glDeleteTextures(1, &id);
		id = std::move(newTexture.id);
		Data = std::move(newTexture.Data);
		Filter = std::move(newTexture.Filter);

		return *this;
	}

	void Texture::bind() const
	{
		
	}

	Texture::~Texture()
	{
		glDeleteTextures(1, &id);
		//auto [x, y, pixels, channels] = Data;
		//pixels = nullptr;
		//Filter = { 0,0 };
	}

}