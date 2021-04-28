#pragma once

#include <Glad/include/glad/glad.h>

#include <string_view>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cmath>

namespace Render {
	class Shader
	{
	public:
		Shader(const std::string_view vertexSrc,const std::string_view fragSrc);
		bool isCompiled() const;
		void use() const;
		void setUniform(const std::string_view name, const GLint value) const;

		GLuint getID() const;

		Shader() = delete;
		Shader(Shader&) = delete;
		Shader& operator=(const Shader&) = delete;
		Shader& operator=(Shader&& shader) noexcept;//move assignment
		Shader(Shader&& shader) noexcept;//move constructor

		~Shader();
	private:
		GLuint idShader = 0;
	private:
		bool createShader(const std::string_view shaderSrc, const GLenum shaderType, GLuint& shaderID);
		void catchError(GLuint shaderId);
		void Init(const std::string_view vertexSrc, const std::string_view fragSrc);
		bool successCompiled = false;
	};
}
