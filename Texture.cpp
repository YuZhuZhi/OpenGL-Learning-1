#include "Texture.h"

// ----------------------PUBLIC-----------------------------

Texture::Texture()
{
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

Texture::Texture(const std::string& texturePath, std::tuple<int&, int&, int&>& textrueInform, const int textureFormat) throw (std::string_view)
{
    this->Texture::Texture();
    createTexture(texturePath, textrueInform, textureFormat);
}

unsigned int Texture::getTextureID() const
{
    return textureID;
}

void Texture::createTexture(const std::string& texturePath, std::tuple<int&, int&, int&>& textrueInform, const int textureFormat) const throw (std::string_view)
{
    unsigned char* data = stbi_load(texturePath.c_str(), &std::get<0>(textrueInform), &std::get<1>(textrueInform), &std::get<2>(textrueInform), 0);
    if (data != nullptr) {
        glTexImage2D(GL_TEXTURE_2D, 0, textureFormat, std::get<0>(textrueInform), std::get<1>(textrueInform), 0, textureFormat, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        throw ("Failed to load texture");
    }
    stbi_image_free(data);
}

void Texture::activate(const int index) const
{
    glActiveTexture(GL_TEXTURE0 + index);
    glBindTexture(GL_TEXTURE_2D, textureID);
}


// ----------------------PRIVATE-----------------------------

