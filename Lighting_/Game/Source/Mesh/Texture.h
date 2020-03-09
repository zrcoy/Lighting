#ifndef __Texture_H__
#define __Texture_H__

class Texture
{
protected:
    GLuint m_TextureID;

public:
    Texture(const char* filename);
    Texture(const char** cubemapFilenames);
    Texture(GLuint textureID);
    virtual ~Texture();
    
    GLuint GetTextureID() { return m_TextureID; }
};

#endif //__Texture_H__
