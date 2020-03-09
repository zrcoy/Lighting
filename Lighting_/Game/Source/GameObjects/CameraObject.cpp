#include "GamePCH.h"

#include "GameObject.h"
#include "CameraObject.h"
#include "Game/Game.h"
#include "Game/Scene.h"

CameraObject::CameraObject(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale)
    : GameObject(pScene, name, pos, rot, scale, 0, 0)
{
    m_LookAtPosition.Set(0, 0, 0);
    m_pTarget = nullptr;
    m_Offset = vec3(0, 0, 0);
    m_IsOrtho = false;
    m_IsPauseScene = false;
}

CameraObject::~CameraObject()
{
}

void CameraObject::Update(float deltaTime)
{
    if (m_pTarget != nullptr)
    {
        m_Position = m_pTarget->GetPosition() + m_Offset;
        m_LookAtPosition = m_pTarget->GetPosition();
    }

    // Setup camera/view matrix.
    m_ViewMatrix.CreateLookAtView(m_Position, vec3(0, 1, 0), m_LookAtPosition);

    float windowWidth = (float)m_pScene->GetGame()->GetFramework()->GetWindowWidth();
    float windowHeight = (float)m_pScene->GetGame()->GetFramework()->GetWindowHeight();

    if (m_IsOrtho)
    {
        if (m_IsPauseScene)
            m_ProjMatrix.CreateOrtho(-2, 2, -4, 4, -5, 5);
        else
            m_ProjMatrix.CreateOrtho(-5, 5, -5, 5, -5, 5);
    }
    else
        m_ProjMatrix.CreatePerspectiveVFoV(45, windowWidth / windowHeight, 0.01f, 1000.0f);
}

void CameraObject::SetObjectToFollow(GameObject* pTarget, vec3 offset)
{
    m_pTarget = pTarget;
    m_Offset = offset;
}
