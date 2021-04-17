#include "sprite.h"

#include "../Shader/Shader.h"
#include "../Texture/Texture.h"
#include "../vao/vao.h"
#include "../vbo/vbo.h"

namespace Render {

	Sprite::Sprite()
	{
		Matrix = glm::mat4(1.0f);
		postion = glm::vec3(0.0f, 0.0f, 0.0f);
		float angle = 0;
		scales = glm::vec3(1.0f, 1.0f, 1.0f);
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

	void Sprite::transform()
	{
		shaderPtr->use();
		update();
		unsigned int transformLoc = glGetUniformLocation(shaderPtr->getID(), "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(Matrix));
	}

	void Sprite::update()
	{
		//Transform object
		glm::mat4 transformMat = glm::mat4(1.0f); //
		transformMat = glm::translate(transformMat, postion);
		transformMat = glm::rotate(transformMat, angle, glm::vec3(0.0f, 1.0f, 1.0f));//pitch,yaw,roll
		transformMat = glm::scale(transformMat, scales);
		Matrix = transformMat;
	}

	void Sprite::draw()
	{
		transform();
		shaderPtr->use();
		texturePtr->bind();
		glBindVertexArray(vaoList.front().getID());
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}

	void Sprite::setPos(glm::vec3 newPos)
	{
		postion = newPos;
	}

	void Sprite::move(glm::vec3 moves)
	{
		postion += moves;
	}

	void Sprite::rotate(float angles,bool fl)
	{
		if (!fl) {
			angle += angles;
		}
		else {
			angle = angles;
		}
	}

	void Sprite::scale(glm::vec3 scale, bool fl)
	{
		if (!fl) {
			scales += scale;
		}
		else {
			scales = scale;
		}
	}

	Sprite::~Sprite()
	{
		//vboList.clear();
		//vaoList.clear();
		//glDeleteProgram(shaderPtr->idShader);
		//texturePtr->~Texture();
	}
}