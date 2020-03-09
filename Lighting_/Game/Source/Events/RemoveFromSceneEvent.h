#ifndef __RemoveFromSceneEvent_H__
#define __RemoveFromSceneEvent_H__

#include "Events/GameEventTypes.h"
#include "../Framework/Source/Events/Event.h"

class Scene;
class GameObject;

class RemoveFromSceneEvent : public Event
{
protected:
    Scene* m_pScene;
    GameObject* m_pGameObject;

public:
    RemoveFromSceneEvent(Scene* pScene, GameObject* gameobject)
    {
        m_pScene = pScene;
        m_pGameObject = gameobject;
    }

    virtual EventTypes GetEventType() override { return (EventTypes)GameEventType_RemoveFromScene; }

    Scene* GetScene() { return m_pScene; }
    GameObject* GetGameObject() { return m_pGameObject; }
};

#endif //__RemoveFromSceneEvent_H__