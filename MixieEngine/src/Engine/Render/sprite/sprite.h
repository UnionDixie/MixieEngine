#pragma once

#include <GLAD/include/glad/glad.h>
#include <list>
#include <memory>
#include <GLM/glm.hpp>
#include <string>

namespace Render {
	class Shader;
	class Texture;
	class VAO;
	class VBO;
}

namespace Render {
	class Sprite
	{
	private:
		typedef std::shared_ptr<Render::Shader> shader_ptr;
		typedef std::shared_ptr<Render::Texture> texture_ptr;
	public:
		Sprite();
		void setParam(std::list<Render::VBO> vboL,
					  std::list<Render::VAO> vaoL,
					  shader_ptr shader_Ptr, texture_ptr texture_Ptr);
		void setMat4(const std::string& name, const glm::mat4& matrix);
		void draw();
		~Sprite();

	private:
		void transform();
	private:
		glm::mat4 Matrix;
		std::string NameMatrix;
		std::list<Render::VBO> vboList;
		std::list<Render::VAO> vaoList;
		std::shared_ptr<Render::Shader> shaderPtr;
		std::shared_ptr<Render::Texture> texturePtr;
	};

}