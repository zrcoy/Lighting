#ifndef __CameraObject_H__
#define __CameraObject_H__

#include "GameObject.h"

class CameraObject : public GameObject
{
protected:
    mat4 m_ViewMatrix;
    mat4 m_ProjMatrix;
    vec3 m_LookAtPosition;
    GameObject* m_pTarget;
    vec3 m_Offset;
    bool m_IsOrtho;
    bool m_IsPauseScene;
public:
    CameraObject(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale);
    virtual ~CameraObject();

    virtual void Update(float deltaTime) override;

    mat4* GetViewMatrix() { return &m_ViewMatrix; }
    mat4* GetProjMatrix() { return &m_ProjMatrix; }
    void SetLookAtPosition(vec3 pos) { m_LookAtPosition = pos; }

    void SetObjectToFollow(GameObject* pTarget, vec3 offset);

    void SetIsOrtho(bool b) { m_IsOrtho = b; }

    void SetIsPauseScene(bool b) { m_IsPauseScene = b; }
};

#endif //__CameraObject_H__
