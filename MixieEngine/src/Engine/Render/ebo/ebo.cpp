#include "ebo.h"

namespace Render {

	EBO::EBO(const unsigned int* indices, const int n)
	{
		glGenBuffers(1, &id);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(*indices) * n, indices, GL_STATIC_DRAW);
	}

	GLuint EBO::getID() const
	{
		return id;
	}

	EBO::~EBO()
	{
	}

}