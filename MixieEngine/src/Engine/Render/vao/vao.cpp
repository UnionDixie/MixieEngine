#include "vao.h"

namespace Render {
    VAO::VAO(const std::initializer_list<vboPacket>& list)
    {
        id = 0;
        glGenVertexArrays(1, &id);
        glBindVertexArray(id);

        for (const auto [id, attrib, n] : list)
        {
            if (id != NULL) {
                glEnableVertexAttribArray(attrib);
                glBindBuffer(GL_ARRAY_BUFFER, id);
                glVertexAttribPointer(attrib, n, GL_FLOAT, false, 0, nullptr);
            }
        }
        //safe
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
        
    }

    GLuint VAO::getID() const
    {
        return id;
    }

    VAO::~VAO()
    {
        glDeleteVertexArrays(1, &id);
    }
}