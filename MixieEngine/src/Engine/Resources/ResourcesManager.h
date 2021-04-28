#pragma once

#include <string_view>//
#include <memory>
#include <map>//or unordered_map

namespace Render {
	class Shader;
	class Texture;
}

class ResourcesManager
{
public:
	ResourcesManager(const std::string_view dataDir);
	~ResourcesManager() = default;

	ResourcesManager(const ResourcesManager&) = delete;
	ResourcesManager& operator=(const ResourcesManager&) = delete;
	ResourcesManager& operator=(ResourcesManager&&) = delete;
	ResourcesManager(ResourcesManager&&) = delete;

	std::shared_ptr<Render::Shader> loadShader(const std::string_view shaderName,
										       const std::string_view vertexPath,
											   const std::string_view fragPath);
	std::shared_ptr<Render::Shader> getShader(const std::string_view shaderName);

	std::shared_ptr<Render::Texture> loadTexture(const std::string_view textureName,
												 const std::string_view texturePath);
	std::shared_ptr<Render::Texture> getTexture(const std::string_view textureName);

private:
	std::string getFileString(const std::string_view filePath) const;
private:
	typedef std::map<const std::string_view, std::shared_ptr<Render::Shader>> ShaderMap;
	typedef std::map<const std::string_view, std::shared_ptr<Render::Texture>> TextureMap;
private:
	ShaderMap shaders;
	TextureMap textureMap;
	const std::string_view dataDir;
};



