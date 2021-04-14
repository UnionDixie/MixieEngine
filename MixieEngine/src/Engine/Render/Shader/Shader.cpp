#include "Shader.h"

namespace Render {
	Render::Shader::Shader(const std::string& vertexSrc, const std::string& fragSrc, bool file)
	{
		if (!vertexSrc.empty() && !fragSrc.empty()) {
			if (file) {
				auto [src1,src2] = loadShaderFromFile(vertexSrc, fragSrc);
				Init(src1, src2);
			}else {
				Init(vertexSrc, fragSrc);
			}
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
		GLchar infoLog[2048];
		glGetShaderInfoLog(shaderId, 1024, nullptr, infoLog);
		std::cerr << "Error::Shader::Compile-time-error:\n" << infoLog << '\n';
	}

	std::pair<std::string, std::string> Shader::loadShaderFromFile(const std::string& vertexPath,const std::string& fragPath)
	{
		std::string vertexCode, fragmentCode;
		std::ifstream vShaderFile, fShaderFile;

		vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try
		{
			// Открываем файлы
			vShaderFile.open(vertexPath);
			fShaderFile.open(fragPath);
			std::stringstream vShaderStream, fShaderStream;

			// Считываем содержимое файловых буферов в потоки
			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();

			// Закрываем файлы
			vShaderFile.close();
			fShaderFile.close();

			// Конвертируем данные из потока в строковые переменные
			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();
		}
		catch (std::ifstream::failure e)
		{
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ\n";
		}
		return { vertexCode ,fragmentCode };
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