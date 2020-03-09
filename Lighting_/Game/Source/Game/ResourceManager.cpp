#include "GamePCH.h"

#include "ResourceManager.h"

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
    for( auto object: m_pMeshes )
        delete object.second;

    for( auto object: m_pMaterials )
        delete object.second;

    for( auto object: m_pShaders )
        delete object.second;

    for( auto object: m_pTextures )
        delete object.second;

    for (auto object : m_pCollisionShapes)
        delete object.second;

    //for (auto object : m_pSoundObjects)
    //    delete object.second;

  /*  for (auto object : m_pTweenObjects)
        delete object.second;*/
}

Mesh* ResourceManager::AddMesh(std::string name, Mesh* pMesh)
{
    assert( m_pMeshes.find( name ) == m_pMeshes.end() );

    m_pMeshes[name] = pMesh;
    pMesh->SetResourceManager(this);//use this in mesh to get unique texture ID for skybox

    return pMesh;
}

void ResourceManager::AddShader(std::string name, ShaderProgram* pShader)
{
    assert( m_pShaders.find( name ) == m_pShaders.end() );

    m_pShaders[name] = pShader;
}

void ResourceManager::AddTexture(std::string name, Texture* pTexture)
{
    assert( m_pTextures.find( name ) == m_pTextures.end() );
    if (m_pTextures.find(name) == m_pTextures.end())
    {

        m_pTextures[name] = pTexture;
    }
}

void ResourceManager::AddMaterial(std::string name, Material* pMaterial)
{
    assert( m_pMaterials.find( name ) == m_pMaterials.end() );

    m_pMaterials[name] = pMaterial;
}

void ResourceManager::AddCollisionShapes(std::string name, btCollisionShape* pCollisionShape)
{
    assert(m_pCollisionShapes.find(name) == m_pCollisionShapes.end());

    m_pCollisionShapes[name] = pCollisionShape;
}

void ResourceManager::AddSoundObject(std::string name, SoundObject* pSoundOBj)
{
    assert(m_pSoundObjects.find(name) == m_pSoundObjects.end());

    m_pSoundObjects[name] = pSoundOBj;

}

//void ResourceManager::AddTweenObject(std::string name, TweenObject* pTweenObj)
//{
//    assert(m_pSoundObjects.find(name) == m_pSoundObjects.end());
//
//    m_pTweenObjects[name] = pTweenObj;
//
//}

Mesh* ResourceManager::GetMesh(std::string name)
{
    auto it = m_pMeshes.find( name );
    if( it == m_pMeshes.end() )
        return nullptr;

    return it->second;
}

ShaderProgram* ResourceManager::GetShader(std::string name)
{
    auto it = m_pShaders.find( name );
    if( it == m_pShaders.end() )
        return nullptr;

    return it->second;
}

Texture* ResourceManager::GetTexture(std::string name)
{
    auto it = m_pTextures.find( name );
    if( it == m_pTextures.end() )
        return nullptr;

    return it->second;
}

Material* ResourceManager::GetMaterial(std::string name)
{
    auto it = m_pMaterials.find( name );
    if( it == m_pMaterials.end() )
        return nullptr;

    return it->second;
}

btCollisionShape* ResourceManager::GetCollisionShape(std::string name)
{
    auto it = m_pCollisionShapes.find(name);
    if (it == m_pCollisionShapes.end())
        return nullptr;

    return it->second;
}

SoundObject* ResourceManager::GetSoundObject(std::string name)
{
    auto it = m_pSoundObjects.find(name);
    if (it == m_pSoundObjects.end())
        return nullptr;

    return it->second;
}

//TweenObject* ResourceManager::GetTweenObject(std::string name)
//{
//    auto it = m_pTweenObjects.find(name);
//    if (it == m_pTweenObjects.end())
//        return nullptr;
//
//    return it->second;
//}