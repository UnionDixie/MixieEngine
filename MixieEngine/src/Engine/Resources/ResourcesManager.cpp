#include "ResourcesManager.h"

#include "../Render/Shader/Shader.h"
#include "../Render/Texture/Texture.h"


#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG
#include "stb_image.h"//turn off warnings


ResourcesManager::ResourcesManager(const std::string_view dataDir) : dataDir(dataDir)
{

}

std::shared_ptr<Render::Shader> ResourcesManager::loadShader(const std::string_view shaderName, const std::string_view vertexPath, const std::string_view fragPath)
{
	std::shared_ptr<Render::Shader> it = nullptr;
	std::string srcVertex = getFileString(vertexPath),
	            srcFragment = getFileString(fragPath);

	if (srcVertex.empty() || srcFragment.empty()) {
		std::cerr << "Failed load to Shader file\n";
	}
	else {
		auto res = shaders.try_emplace(shaderName, std::make_shared<Render::Shader>(srcVertex, srcFragment));
		it = res.first->second;
		if (!it->isCompiled()) {
			std::cerr << "Failed compile shader\n";
			it = nullptr;
		}
	}
	
	return it;
}

std::shared_ptr<Render::Shader> ResourcesManager::getShader(const std::string_view shaderName)
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

std::shared_ptr<Render::Texture> ResourcesManager::loadTexture(const std::string_view textureName,
															   const std::string_view texturePath)
{
	int channels = 0, width = 0, height = 0;
	stbi_set_flip_vertically_on_load(true);//opengl used dekart,load used coor screen
	auto pathToFile = std::string(dataDir) + std::string(texturePath);
	auto pixels = stbi_load(pathToFile.c_str(), &width, &height, &channels, 0);//ptr
	std::shared_ptr<Render::Texture> result = nullptr;
	if (!pixels) {
		std::cerr << "Failed load to image file\n";
	}
	else {
		result = textureMap.try_emplace(textureName,
			     std::make_shared<Render::Texture>(std::make_tuple(width, height, pixels, channels))).first->second;
	}
	stbi_image_free(pixels);

	return result;
}

std::shared_ptr<Render::Texture> ResourcesManager::getTexture(const std::string_view textureName)
{
	TextureMap::const_iterator it = textureMap.find(textureName);
	std::shared_ptr<Render::Texture> texture = nullptr;
	if (it != textureMap.cend()) {
		texture = it->second;
	}
	else {
		std::cerr << "Not found shader in textureMap\n";
	}
	return texture;
}


#include <iostream>
#include <filesystem>
#include <fstream>

std::string ResourcesManager::getFileString(const std::string_view filePath) const
{
	auto pathToFile = std::string(dataDir) + std::string(filePath);
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