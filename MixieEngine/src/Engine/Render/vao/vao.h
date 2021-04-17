#pragma once

#include <Glad/include/glad/glad.h>
#include <tuple>

#include <initializer_list>

namespace Render {

    class VAO
    {
    public:
        //id attrib and n
        typedef std::tuple<GLuint, GLuint, GLuint> vboPacket;
        VAO(const std::initializer_list<vboPacket>& list);

        VAO() = delete;
        //VAO(const VAO&) = delete;
        //VAO& operator=(const VAO&) = delete;

        GLuint getID() const;
        ~VAO();

    private:
        GLuint id;
    };
}