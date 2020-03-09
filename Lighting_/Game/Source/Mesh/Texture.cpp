#include "GamePCH.h"

#include "Mesh/Texture.h"

Texture::Texture(const char* filename)
{
    m_TextureID = LoadTexture( filename );
}

Texture::Texture(GLuint textureID)
{
    m_TextureID = textureID;
}

Texture::Texture(const char** cubemapFilenames)
{
    m_TextureID = LoadTextureCubemap(cubemapFilenames);
}

Texture::~Texture()
{
    glDeleteTextures( 1, &m_TextureID );
}
