#ifndef __SceneSample_H__
#define __SceneSample_H__

#include "Game/Scene.h"

class Game;
class GameObject;
class ResourceManager;

class SceneSample : public Scene
{
protected:

public:
    SceneSample(Game* pGame, ResourceManager* pResources);
    virtual ~SceneSample();

    virtual void LoadContent() override;

    virtual void OnEvent(Event* pEvent) override;
    virtual void Update(float deltaTime) override;
    virtual void Draw() override;
};

#endif //__SceneSample_H__
