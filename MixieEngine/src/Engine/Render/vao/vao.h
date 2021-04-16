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
        GLuint getID() const;
        ~VAO();

    private:
        GLuint id;
    };

    inline VAO::VAO(const std::initializer_list<vboPacket>& list)
    {
        id = 0;
        glGenVertexArrays(1, &id);
        glBindVertexArray(id);

        for (const auto [id, attrib, n] : list)
        {
            glEnableVertexAttribArray(attrib);
            glBindBuffer(GL_ARRAY_BUFFER, id);
            glVertexAttribPointer(attrib, n, GL_FLOAT, false, 0, nullptr);
        }
    }

    inline GLuint VAO::getID() const
    {
        return id;
    }

    inline VAO::~VAO()
    {
        glDeleteVertexArrays(1, &id);
    }

}