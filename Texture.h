#pragma once
#include <string>
#include <glad/glad.h>
#include "stb/stb_image.h"

class Texture
{
public:
	Texture();
	Texture(const std::string& texturePath, std::tuple<int&, int&, int&>& textrueInform, const int textureFormat) throw (std::string_view);
	Texture(const Texture&) = delete;
	~Texture() = default;

	unsigned int getTextureID() const;
	void createTexture(const std::string& texturePath, std::tuple<int&, int&, int&>& textrueInform, const int textureFormat) const throw (std::string_view);
	void activate(const int index) const;

private:
	unsigned int textureID;
};

