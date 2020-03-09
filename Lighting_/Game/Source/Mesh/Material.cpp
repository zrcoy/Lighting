#include "GamePCH.h"

#include "Material.h"
#include "Mesh/Texture.h"

Material::Material(ShaderProgram* pShader, Texture* pTexture, Texture* pCubemap)
{
    m_pShader = pShader;
    m_pTexture = pTexture;
    m_pCubemap = pCubemap;
}

Material::~Material()
{
    
}
