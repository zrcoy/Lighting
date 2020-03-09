#ifndef __ResourceManager_H__
#define __ResourceManager_H__

class ResourceManager;

#include "Mesh/Material.h"
#include "Mesh/Mesh.h"
#include "Mesh/Texture.h"

class Game;
class ShaderProgram;
class SoundObject;
class TweenObject;

class ResourceManager
{
protected:
    std::map<std::string, Mesh*> m_pMeshes;
    std::map<std::string, ShaderProgram*> m_pShaders;
    std::map<std::string, Texture*> m_pTextures;
    std::map<std::string, Material*> m_pMaterials;
    std::map<std::string, btCollisionShape*> m_pCollisionShapes;
    std::map<std::string, SoundObject*> m_pSoundObjects;
    //std::map<std::string, TweenObject*> m_pTweenObjects;

public:
    ResourceManager();
    virtual ~ResourceManager();

    Mesh* AddMesh(std::string name, Mesh* pMesh);
    void AddShader(std::string name, ShaderProgram* pShader);
    void AddTexture(std::string name, Texture* pTexture);
    void AddMaterial(std::string name, Material* pMaterial);
    void AddCollisionShapes(std::string name, btCollisionShape* pCollisionShape);
    void AddSoundObject(std::string name, SoundObject* pSoundObj);
    //void AddTweenObject(std::string name, TweenObject* pTweenObj);

    Mesh*          GetMesh(const std::string name);
    ShaderProgram* GetShader(const std::string name);
    Texture*       GetTexture(const std::string name);
    Material*      GetMaterial(const std::string name);
    btCollisionShape* GetCollisionShape(const std::string name);
    SoundObject*   GetSoundObject(const std::string name);
    //TweenObject*   GetTweenObject(const std::string name);
};

#endif //__ResourceManager_H__
