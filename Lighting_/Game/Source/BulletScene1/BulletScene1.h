#pragma once
#include "Game/Scene.h"

class Game;
class GameObject;
class ResourceManager;


class BulletScene1:public Scene
{
protected:
    bool m_CanSelect = true;
public:
    BulletScene1(Game* pGame, ResourceManager* pResources);
    virtual ~BulletScene1();

    virtual void LoadContent() override;

    virtual void OnEvent(Event* pEvent) override;
    virtual void Update(float deltaTime) override;
    virtual void Draw() override;
    void SpawnHingeJoint(vec3 posA, vec3 posB);
    void SpawnP2PJoint(vec3 posA, vec3 posB);
    void Spawn6FreeJoint(vec3 posA, vec3 posB);
    virtual void Reset() override;
};


