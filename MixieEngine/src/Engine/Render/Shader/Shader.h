#pragma once

#include <glad/glad.h>

#include <string>
//#include <string_view>
#include <iostream>
//
#include <fstream>
#include <sstream>
#include <filesystem>

namespace Render {
	class Shader
	{
	public:
		Shader(const std::string& vertexSrc, const std::string& fragSrc);
		bool isCompiled() const;
		void use() const;

		Shader() = delete;
		Shader(Shader&) = delete;
		Shader& operator=(const Shader&) = delete;
		Shader& operator=(Shader&& shader) noexcept;//move assignment
		Shader(Shader&& shader) noexcept;//move constructor

		~Shader();
	private:
		bool createShader(const std::string& shaderSrc, const GLenum shaderType, GLuint& shaderID);
		void catchError(GLuint shaderId);
		void Init(const std::string& vertexSrc, const std::string& fragSrc);
		bool successCompiled = false;
		GLuint idShader = 0;

	};
}
