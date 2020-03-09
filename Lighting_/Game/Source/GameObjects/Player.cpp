#include "GamePCH.h"

#include "Game/Game.h"
#include "Mesh/Mesh.h"
#include "GameObjects/GameObject.h"
#include "GameObjects/Player.h"
#include "GameObjects/PlayerController.h"

Player::Player(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, Material* pMaterial)
: GameObject( pScene, name, pos, rot, scale, pMesh, pMaterial )
, m_pPlayerController( nullptr )
, m_Speed( PLAYER_SPEED )
{
}
    
Player::~Player()
{
}

void Player::Update(float deltaTime)
{
    
    GameObject::Update(deltaTime);

    vec3 dir( 0, 0 ,0);

    if( m_pPlayerController )
    {
        if( m_pPlayerController->IsHeld_Up() )
        {
            dir.y = 1;
        }

        if( m_pPlayerController->IsHeld_Down() )
        {
            dir.y = -1;
        }

        if( m_pPlayerController->IsHeld_Left() )
        {
            dir.x = -1;
        }

        if( m_pPlayerController->IsHeld_Right() )
        {
            dir.x = 1;
        }
    }

    //m_Position += dir * m_Speed * deltaTime;
    m_p3DBody->applyForce(btVector3(dir.x * 10, 0, 0), btVector3(0, 0, 0));
    ImGui::Text("graphics X : %f, physic X : %f, physic Z : %f,", m_Position.x, m_Position.y, m_Position.z);

}
