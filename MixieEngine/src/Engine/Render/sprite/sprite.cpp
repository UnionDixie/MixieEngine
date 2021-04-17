#include "sprite.h"

#include "../Shader/Shader.h"
#include "../Texture/Texture.h"
#include "../vao/vao.h"
#include "../vbo/vbo.h"

namespace Render {

	Sprite::Sprite()
	{
		Matrix = glm::mat4(1.0f);
	}

	void Sprite::setParam(std::list<Render::VBO> vboL,
						  std::list<Render::VAO> vaoL,
						  shader_ptr shader_Ptr, texture_ptr texture_Ptr)
	{
		vboList = std::move(vboL);
		vaoList = std::move(vaoL);
		shaderPtr = shader_Ptr;
		texturePtr = texture_Ptr;
	}

	void Sprite::setMat4(const std::string& name, const glm::mat4& matrix)
	{
		NameMatrix = name;
		Matrix = matrix;
	}

	void Sprite::setEBO(const unsigned int* indices, const int n)
	{
		//Render::EBO tmp(indices, n);
		//ebo = tmp;
	}

	void Sprite::transform()
	{
		shaderPtr->use();
		unsigned int transformLoc = glGetUniformLocation(shaderPtr->getID(), "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(Matrix));
	}

	void Sprite::draw()
	{
		transform();
		shaderPtr->use();
		texturePtr->bind();
		glBindVertexArray(vaoList.front().getID());
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}

	Sprite::~Sprite()
	{
		//vboList.clear();
		//vaoList.clear();
		//glDeleteProgram(shaderPtr->idShader);
		//texturePtr->~Texture();
	}
}