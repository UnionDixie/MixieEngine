#include "Shader.h"

namespace Render {
	Render::Shader::Shader(const std::string& vertexSrc, const std::string& fragSrc)
	{
		if (!vertexSrc.empty() && !fragSrc.empty()) {
			Init(vertexSrc, fragSrc);
		}
		else {
			std::cerr << "Warning:Empty src shaders\n";
		}
	}

	bool Render::Shader::isCompiled() const
	{
		return successCompiled;
	}

	void Render::Shader::use() const
	{
		glUseProgram(idShader);
	}

	void Shader::setUniform(const std::string& name, const GLint value) const
	{
		glUniform1i(glGetUniformLocation(idShader, name.c_str()), value);
	}

	bool Shader::createShader(const std::string& shaderSrc, const GLenum shaderType, GLuint& shaderID)
	{
		shaderID = glCreateShader(shaderType);
		const char* source = shaderSrc.c_str();
		glShaderSource(shaderID, 1, &source, nullptr);
		glCompileShader(shaderID);
		//check error
		GLint success;
		glGetShaderiv(shaderID,GL_COMPILE_STATUS, &success);
		if (!success) {
			catchError(shaderID);
		}
		return success;
	}

	void Shader::catchError(GLuint shaderId)
	{
		GLchar infoLog[1024];
		glGetShaderInfoLog(shaderId, 1024, nullptr, infoLog);
		std::cerr << "Error::Shader::Compile-time-error:\n" << infoLog << '\n';
	}

	void Shader::Init(const std::string& vertexSrc, const std::string& fragSrc)
	{
		GLuint vertxShader = 0;
		if (!createShader(vertexSrc, GL_VERTEX_SHADER, vertxShader)) {
			std::cerr << "VertexShader compile-time-error\n";
			//return;
		}

		GLuint fragShader = 0;
		if (!createShader(fragSrc, GL_FRAGMENT_SHADER, fragShader)) {
			std::cerr << "FragmentShader compile-time-error\n";
			//glDeleteShader(vertxShader);
			//return;
		}

		idShader = glCreateProgram();
		glAttachShader(idShader, vertxShader);
		glAttachShader(idShader, fragShader);
		glLinkProgram(idShader);

		GLint success = 0;
		glGetProgramiv(idShader, GL_LINK_STATUS, &success);
		if (!success) {
			std::cerr << "ShaderProgram compile-time-error\n";
			catchError(idShader);
		}
		else {
			successCompiled = true;
		}

		glDeleteShader(vertxShader);
		glDeleteShader(fragShader);
	}

	Shader& Shader::operator=(Shader&& shader) noexcept
	{
		glDeleteProgram(idShader);
		//think maybe func?
		idShader = shader.idShader;
		successCompiled = shader.successCompiled;
		shader.idShader = 0;
		shader.successCompiled = false;
		//
		return *this;
	}

	Shader::Shader(Shader&& shader) noexcept
	{
		idShader = shader.idShader;
		successCompiled = shader.successCompiled;
		shader.idShader = 0;
		shader.successCompiled = false;
	}

	Render::Shader::~Shader()
	{
		glDeleteProgram(idShader);
	}
}