#pragma once

#include <Glad/include/glad/glad.h>

namespace Render {
	class VBO
	{
	public:
		VBO(const GLfloat* data, const int count);

		VBO() = delete;
		//VBO(const VBO&) = delete;
		//VBO& operator=(const VBO&) = delete;


		GLuint getID() const;
		~VBO();
		//delete copy!
	private:
		GLuint id;
	};

}