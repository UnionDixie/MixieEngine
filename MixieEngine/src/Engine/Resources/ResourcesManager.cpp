#include "ResourcesManager.h"

#include "../Render/Shader/Shader.h"

#include <sstream>
#include <fstream>
#include <iostream>

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