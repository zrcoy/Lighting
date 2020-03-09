#pragma once

#include "GameObjects/CameraObject.h"

class GameObject;

class ThirdP_Camera : public CameraObject
{
protected:
    GameObject * m_ObjectFollowing;
    float m_Distance;

    bool m_MouseLocked;
    vec2 m_MouseChangeSinceLastFrame;
    vec2 m_LastMousePosition;

public:
    ThirdP_Camera(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale);
    virtual ~ThirdP_Camera();

    virtual void OnEvent(Event* pEvent);
    virtual void Update(float deltaTime);

    void SetObjectToFollow(GameObject* pObject, float dist) { m_ObjectFollowing = pObject; m_Distance = dist; }
};



