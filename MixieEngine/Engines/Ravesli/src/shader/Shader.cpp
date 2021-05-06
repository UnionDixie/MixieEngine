#include "Shader.h"


Shader::Shader(std::string_view vertexPath, std::string_view fragmentPath) {
	auto vertexSrc   = getStringFromFile(vertexPath),
		 fragmentSrc = getStringFromFile(fragmentPath);
	auto vSrc = vertexSrc.c_str(), fSrc = fragmentSrc.c_str();

	// 2. Компилируем шейдеры
	ui vertex, fragment;

	// Вершинный шейдер
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vSrc, NULL);
	glCompileShader(vertex);
	checkError(vertex, "VERTEX");

	// Фрагментный шейдер
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fSrc, NULL);
	glCompileShader(fragment);
	checkError(fragment, "FRAGMENT");

	// Шейдерная программа
	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);
	checkError(ID, "PROGRAM");

	// После того, как мы связали шейдеры с нашей программой, удаляем их, т.к. они нам больше не нужны
	glDeleteShader(vertex);
	glDeleteShader(fragment);


}


void Shader::use()
{
	glUseProgram(ID);
}

void Shader::setBool(const std::string_view name, bool value) const
{
	glUniform1i(glGetUniformLocation(ID, name.data()), (int)value);
}

void Shader::setInt(const std::string_view name, int value) const
{
	glUniform1i(glGetUniformLocation(ID, name.data()), value);
}

void Shader::setFloat(const std::string_view name, float value) const
{
	glUniform1f(glGetUniformLocation(ID, name.data()), value);
}

std::string Shader::getStringFromFile(std::string_view path)
{
	auto pathToFile = std::string(path);
	std::string result;
	std::ifstream file(pathToFile, std::ios::in | std::ios::binary);
	if (!file.is_open()) {
		std::cerr << "Failed to open shader file: " << pathToFile << "\n";
	}
	else {
		const auto size = std::filesystem::file_size(pathToFile);
		result.resize(size, '\0');
		file.read(result.data(), size);
		file.close();
	}
	return result;
}

void Shader::checkError(ui shader, std::string_view type)
{
	int success;
	char infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
}
