#pragma once

#include <GLAD/include/glad/glad.h>

namespace Render {
	//building...
	class EBO
	{
	public:
		EBO() = delete;
		EBO(const unsigned int* indices, const int n);
		GLuint getID() const;
		~EBO();

	private:
		GLuint id;
	};
}
