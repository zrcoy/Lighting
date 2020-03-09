#include "GamePCH.h"

#include "Game/Game.h"
#include "Mesh/Mesh.h"
#include "GameObjects/GameObject.h"
#include "BulletScenePlayer.h"
#include "GameObjects/PlayerController.h"
#include "Game/Scene.h"
#include "LightSampleScene/LightSampleScene.h"

BulletScenePlayer::BulletScenePlayer(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, Material* pMaterial)
    : GameObject(pScene, name, pos, rot, scale, pMesh, pMaterial)
    , m_pPlayerController(nullptr)
{
}

BulletScenePlayer::~BulletScenePlayer()
{
}

void BulletScenePlayer::Update(float deltaTime)
{

    GameObject::Update(deltaTime);

    vec3 dir(0, 0, 0);
    btScalar mass = m_p3DBody->getInvMass();
    btVector3 vDiff = btVector3(0, 0, 0);
    static float tweak =20.0f;
    if (m_pPlayerController)
    {
        m_p3DBody->activate(true);
        vec3 camPos = m_pScene->GetGameObjectByName("Camera")->GetPosition();
        vec3 camDir = m_Position - camPos;
        camDir.Normalize();
        camDir.y = 0;
        if (m_pPlayerController->IsHeld_Up())
            dir += camDir;

        if (m_pPlayerController->IsHeld_Down())
            dir += camDir * -1;

        if (m_pPlayerController->IsHeld_Left())
            dir += vec3(-camDir.z, 0, camDir.x);

        if (m_pPlayerController->IsHeld_Right())
            dir += vec3(camDir.z, 0, -camDir.x);;

        /*if (m_pPlayerController->IsHeld_Lift())
            dir += vec3(0, 1, 0);*/

        if (m_pPlayerController->IsHeld_Drop())
            dir += vec3(0, -1, 0);

        btVector3 currentV = m_p3DBody->getLinearVelocity();

        btVector3 targetV = btVector3(dir.x, dir.y, dir.z) * tweak;
        vDiff = targetV - currentV;
    }

    m_p3DBody->applyImpulse(vDiff * mass, btVector3(0, 0, 0));
    if (m_pScene->GetGame()->GetImGuiFlag())
    {
        ImGui::Text("player graphics X : %f, graphic Y : %f, graohic Z : %f,", m_Position.x, m_Position.y, m_Position.z);
        ImGui::Text("player physics X : %f, physics Y : %f, physics Z : %f,", m_p3DBody->getWorldTransform().getOrigin().getX(), m_p3DBody->getWorldTransform().getOrigin().getY(), m_p3DBody->getWorldTransform().getOrigin().getZ());
        //ImGui::SliderFloat("Tweak", &tweak, 30.0f, 150.0f);

    }

}


