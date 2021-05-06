#pragma once

#include <glad/glad.h> // подключаем glad для активации всех заголовочных файлов OpenGL

//#include <string>
#include <fstream>
//#include <sstream>
#include <iostream>

#include <string_view>
#include <filesystem>

class Shader
{
private:
    using ui = unsigned int;
    // ID - идентификатор программы
    ui ID = 0;
public:
    Shader() = delete;
    // Конструктор считывает данные и выполняет построение шейдера
    Shader(std::string_view vertexPath, std::string_view fragmentPath);

    // Использование/активация шейдера
    void use();

    // Полезные uniform-функции
    void setBool(const std::string_view name, bool value) const;
    void setInt(const std::string_view name, int value) const;
    void setFloat(const std::string_view name, float value) const;
private:
    std::string getStringFromFile(std::string_view path);
    void checkError(ui shader, std::string_view type);
};




