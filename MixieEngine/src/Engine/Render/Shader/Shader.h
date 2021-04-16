#pragma once

#include <Glad/include/glad/glad.h>

#include <string>
//#include <string_view>
#include <iostream>

namespace Render {
	class Shader
	{
	public:
		Shader(const std::string& vertexSrc, const std::string& fragSrc);
		bool isCompiled() const;
		void use() const;
		void setUniform(const std::string& name, const GLint value) const;


		Shader() = delete;
		Shader(Shader&) = delete;
		Shader& operator=(const Shader&) = delete;
		Shader& operator=(Shader&& shader) noexcept;//move assignment
		Shader(Shader&& shader) noexcept;//move constructor

		GLuint idShader = 0;

		~Shader();
	private:
		bool createShader(const std::string& shaderSrc, const GLenum shaderType, GLuint& shaderID);
		void catchError(GLuint shaderId);
		void Init(const std::string& vertexSrc, const std::string& fragSrc);
		bool successCompiled = false;
		//GLuint idShader = 0;

	};
}
