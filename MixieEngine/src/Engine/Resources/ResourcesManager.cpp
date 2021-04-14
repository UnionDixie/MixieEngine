#include "ResourcesManager.h"

#include "../Render/Shader/Shader.h"

#include <sstream>
#include <fstream>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG
#include "stb_image.h"

ResourcesManager::ResourcesManager(const std::string& dataDir) : dataDir(dataDir)
{

}

std::shared_ptr<Render::Shader> ResourcesManager::loadShader(const std::string& shaderName, const std::string& vertexPath, const std::string& fragPath)
{
	std::shared_ptr<Render::Shader> it = nullptr;
	std::string srcVertex = getFileString(vertexPath), fragmentPath = getFileString(fragPath);
	if (srcVertex.empty() || fragPath.empty()) {
		std::cerr << "Failed load to Shader file\n";
	}
	else {
		auto res = shaders.try_emplace(shaderName, std::make_shared<Render::Shader>(srcVertex, fragmentPath));
		it = res.first->second;
		if (!it->isCompiled()) {
			std::cerr << "Failed compile shader\n";
			it = nullptr;
		}
	}

	return it;
}

std::shared_ptr<Render::Shader> ResourcesManager::getShader(const std::string& shaderName)
{
	ShaderMap::const_iterator it = shaders.find(shaderName);
	std::shared_ptr<Render::Shader> shader = nullptr;
	if (it != shaders.cend()) {
		shader = it->second;
	}
	else {
		std::cerr << "Not found shader in shadersMap\n";
	}
	return shader;	
}

void ResourcesManager::loadTexture(const std::string& textureName, const std::string& texturePath)
{
	int channels = 0, width = 0, height = 0;

	stbi_set_flip_vertically_on_load(true);//opengl used dekart,load used coor screen
	unsigned char* pixels = stbi_load((dataDir + texturePath).c_str(), &width, &height, &channels, 0);//unique
	if (!pixels) {
		std::cerr << "Failed load to image file\n";
	}
	else {

	}

	stbi_image_free(pixels);
}

std::string ResourcesManager::getFileString(const std::string& filePath) const
{
	std::string result = "";
	std::ifstream file;
	file.open(dataDir + filePath, std::ios::in || std::ios::binary);
	if (!file.is_open()) {
		std::cerr << "Failed to open shader file: " << dataDir + filePath << "\n";
	}
	else {
		std::stringstream buffer;
		buffer << file.rdbuf();
		result = buffer.str();
	}
	return result;
}