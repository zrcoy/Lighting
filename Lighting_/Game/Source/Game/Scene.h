#ifndef __Scene_H__
#define __Scene_H__

class Game;
class GameObject;
class ResourceManager;
class BulletManager;
class LightInfo;


class Scene
{   
protected:
    std::vector<GameObject*> m_pGameObjects;
    Game* m_pGame;
    ResourceManager* m_pResources;

    BulletManager * m_pBulletManager;

    //bool m_IsOpaque;
public:
    std::vector<LightInfo*> m_vLights;
    Scene(Game* pGame, ResourceManager* pResources);
    virtual ~Scene();

    void Cleanup();

    virtual void LoadContent();

    virtual void Reset();

    virtual void OnEvent(Event* pEvent);
    virtual void Update(float deltaTime);
    virtual void Draw();

    void AddGameObject(GameObject* pObject);
    bool RemoveGameObject(GameObject* pObject);
    bool IsGameObjectInScene(GameObject* pObject);
    GameObject* GetGameObjectByName(std::string name);

    Game* GetGame() { return m_pGame; }
    ResourceManager* GetResourceManager() { return m_pResources; }

    BulletManager* GetBulletManager() { return m_pBulletManager; }

    LightInfo* GetLight(std::string name);

    //bool IsOpaque() { return m_IsOpaque; }
    //void SetOpaque(bool b) { m_IsOpaque = b; }
};

#endif //__Scene_H__
