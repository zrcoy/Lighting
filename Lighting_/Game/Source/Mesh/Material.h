#ifndef __Material_H__
#define __Material_H__

class ShaderProgram;
class Texture;

class Material
{
protected:
    ShaderProgram* m_pShader;
    Texture* m_pTexture;
    Texture* m_pCubemap;
    
public:
    Material(ShaderProgram* pShader, Texture* pTexture, Texture* pCubemap=nullptr);
    virtual ~Material();

    ShaderProgram* GetShader() { return m_pShader; }
    Texture* GetTexture() { return m_pTexture; }
    Texture* GetCubemap() { return m_pCubemap; }
};

#endif //__Material_H__
