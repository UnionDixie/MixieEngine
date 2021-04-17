#include "vbo.h"


namespace Render {

	VBO::VBO(const GLfloat* data, const int count)
	{
		id = 0;
		glGenBuffers(1, &id);
		glBindBuffer(GL_ARRAY_BUFFER, id);
		glBufferData(GL_ARRAY_BUFFER, sizeof(*data) * count, data, GL_STATIC_DRAW);
	}

	GLuint VBO::getID() const
	{
		return id;
	}

	VBO::~VBO()
	{
		glDeleteBuffers(1, &id);
	}
}