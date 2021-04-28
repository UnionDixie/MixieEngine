#pragma once

#include <Glad/include/glad/glad.h>
//#include <string_view>
#include <map>

namespace Render {
	//raw data(texture) width,height,data*,channels
	typedef std::tuple<GLuint, GLuint, unsigned char*, GLuint> rawData;
	//Texturefilter and wrapMode
	typedef std::pair<GLenum, GLenum> Filters;
	class Texture
	{
	public:
		Texture(rawData data, Filters filter = { GL_LINEAR, GL_CLAMP_TO_EDGE });

		Texture() = delete;
		Texture(const Texture&) = delete;
		Texture& operator=(const Texture&) = delete;
		Texture(Texture&&) noexcept;
		Texture& operator=(Texture&&) noexcept;

		void bind() const;

		~Texture();
	private:
		GLuint id;
		rawData Data;
		Filters Filter;
		const std::map<GLuint, GLenum> modeChannels = { {4,GL_RGBA}, {3,GL_RGB} };
	};
}


