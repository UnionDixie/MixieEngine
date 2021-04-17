#pragma once

#include <GLAD/include/glad/glad.h>

namespace Render {
	class EBO
	{
	public:
		EBO();
		EBO(const unsigned int* indices, const int n);
		GLuint getID() const;
		~EBO();

	private:
		GLuint id;
	};
}
