#pragma once

#include <GLAD/include/glad/glad.h>
#include <list>
#include <memory>
#include <GLM/glm.hpp>
#include <string>

//#include "../ebo/ebo.h"

namespace Render {
	class Shader;
	class Texture;
	class VAO;
	class VBO;
	//class EBO;
}

namespace Render {
	class Sprite
	{
	private:
		typedef std::shared_ptr<Render::Shader> shader_ptr;
		typedef std::shared_ptr<Render::Texture> texture_ptr;
	public:
		Sprite();

		//VAO() = delete;
		Sprite(const Sprite&) = delete;
		Sprite& operator=(const Sprite&) = delete;

		~Sprite();
	public:
		void setParam(std::list<Render::VBO> vboL,
			std::list<Render::VAO> vaoL,
			shader_ptr shader_Ptr, texture_ptr texture_Ptr);
		//void setMat4(const std::string& name, const glm::mat4& matrix);
		//void setEBO(const unsigned int* indices,const int n);
		void draw();
		void setPos(glm::vec3 newPos);
		void move(glm::vec3 moves);
		void rotate(float angle, bool fl = true);
		void scale(glm::vec3 scale, bool fl = true);

	private:
		void transform();
		void update();
	private:
		glm::vec3 postion;
		float angle;
		glm::vec3 scales;

		glm::mat4 Matrix;
		std::string NameMatrix;
		std::list<Render::VBO> vboList;
		std::list<Render::VAO> vaoList;
		//Render::EBO ebo;
		std::shared_ptr<Render::Shader> shaderPtr;
		std::shared_ptr<Render::Texture> texturePtr;
	};

}