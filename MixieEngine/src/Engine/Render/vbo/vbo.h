#pragma once

#include <Glad/include/glad/glad.h>

namespace Render {
	class VBO
	{
	public:
		VBO(const GLfloat* data, const int count);
		GLuint getID() const;
		~VBO();
		//delete copy!
	private:
		GLuint id;
	};

	inline VBO::VBO(const GLfloat* data, const int count)
	{
		id = 0;
		glGenBuffers(1, &id);
		glBindBuffer(GL_ARRAY_BUFFER, id);
		glBufferData(GL_ARRAY_BUFFER, sizeof(*data) * count, data, GL_STATIC_DRAW);
	}

	inline GLuint VBO::getID() const
	{
		return id;
	}

	inline VBO::~VBO()
	{
		glDeleteBuffers(1, &id);
	}

}