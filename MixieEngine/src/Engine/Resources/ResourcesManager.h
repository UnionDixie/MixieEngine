#pragma once

#include <string>//string_view
#include <memory>
#include <map>//or unordered_map

namespace Render {
	class Shader;
}

class ResourcesManager
{
public:
	ResourcesManager(const std::string& dataDir);
	~ResourcesManager() = default;

	ResourcesManager(const ResourcesManager&) = delete;
	ResourcesManager& operator=(const ResourcesManager&) = delete;
	ResourcesManager& operator=(ResourcesManager&&) = delete;
	ResourcesManager(ResourcesManager&&) = delete;

	std::shared_ptr<Render::Shader> loadShader(const std::string& shaderName,
											   const std::string& vertexPath,
											   const std::string& fragPath);
	std::shared_ptr<Render::Shader> getShader(const std::string& shaderName);
private:
	std::string getFileString(const std::string& filePath) const;
private:
	typedef std::map<const std::string, std::shared_ptr<Render::Shader>> ShaderMap;
	ShaderMap shaders;
	std::string dataDir;
};



