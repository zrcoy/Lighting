#include "GamePCH.h"

#include "Game/Game.h"
#include "Mesh/Mesh.h"
#include "Game/Scene.h"
#include "GameObjects/GameObject.h"
#include "BulletScene_Telepoter.h"
#include "Game/ResourceManager.h"


BulletScene_Telepoter::BulletScene_Telepoter(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, Material* pMaterial)
    : GameObject(pScene, name, pos, rot, scale, pMesh, pMaterial)

{
    m_CloseEnough = false;
    m_AnimationCounter = 0.0f;
    m_ChangeCounter = 0.0f;
    m_Destnation = vec3(0);
}

BulletScene_Telepoter::~BulletScene_Telepoter()
{
}

void BulletScene_Telepoter::Update(float deltaTime)
{
    GameObject::Update(deltaTime);

    Teleport(deltaTime);

}

void BulletScene_Telepoter::Draw(CameraObject* pCam)
{

    glDisable(GL_CULL_FACE);
    GameObject::Draw(pCam);
    glEnable(GL_CULL_FACE);

}


void BulletScene_Telepoter::Teleport(float deltaTime)
{
    vec3 dir = m_Position - m_pScene->GetGameObjectByName("LightPlayer")->GetPosition();
    float dist = dir.Length();
    //detect range of teleport
    if (dist <= 3.0f)
    {
        m_CloseEnough = true;

    }
    else {
        m_CloseEnough = false;
    }

    //teleport animation flag set, timer started
    if (m_CloseEnough && m_AnimationCounter <= 0)
    {
        m_AnimationCounter = ANIMATION_TELEPORT;

    }

    if (m_AnimationCounter < 0)
    {
        m_AnimationCounter = 0;
    }

    if (m_AnimationCounter > 0 && m_CloseEnough == true)
    {
        m_AnimationCounter -= deltaTime;
        AnimateTeleport(deltaTime);
        if (m_AnimationCounter <= 0)
        {
            //Teleport player after 3 seconds
            assert(m_Destnation.Length() > 0);
            //vec3 targetPos = m_pScene->GetGameObjectByName("B")->GetPosition() + vec3(0, 3, 0);
            m_pScene->GetGameObjectByName("LightPlayer")->SetPosition(m_Destnation);
            m_pScene->GetGameObjectByName("LightPlayer")->SyncPhysicsBodyToGraphic(m_Destnation, vec3(0));
            m_pMaterial = m_pScene->GetResourceManager()->GetMaterial("T1");  // when finishing teleport , set material back to origin state
            
        }
    }
}

void BulletScene_Telepoter::SetDestination(vec3 target)
{
    m_Destnation = target;
}

void BulletScene_Telepoter::AnimateTeleport(float delta)
{
    static int count = 0;
    m_ChangeCounter += delta;
    if (m_ChangeCounter >= ANIMATION_CHANGE_SPRITE)
    {
        count++;
        ChangeSprite(count);
        m_ChangeCounter = 0;
    }
}

void BulletScene_Telepoter::ChangeSprite(int index)
{
    index %= 8;
    switch (index)
    {
    case(0):
        m_pMaterial = m_pScene->GetResourceManager()->GetMaterial("T1");
        break;
    case(1):
        m_pMaterial = m_pScene->GetResourceManager()->GetMaterial("T2");
        break;
    case(2):
        m_pMaterial = m_pScene->GetResourceManager()->GetMaterial("T3");
        break;
    case(3):
        m_pMaterial = m_pScene->GetResourceManager()->GetMaterial("T4");
        break;
    case(4):
        m_pMaterial = m_pScene->GetResourceManager()->GetMaterial("T5");
        break;
    case(5):
        m_pMaterial = m_pScene->GetResourceManager()->GetMaterial("T6");
        break;
    case(6):
        m_pMaterial = m_pScene->GetResourceManager()->GetMaterial("T7");
        break;
    case(7):
        m_pMaterial = m_pScene->GetResourceManager()->GetMaterial("T8");
        break;
    default:
        break;
    }
}


