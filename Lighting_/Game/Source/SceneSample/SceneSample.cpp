#include "GamePCH.h"

#include "SceneSample.h"
#include "Game/Game.h"
#include "Game/ResourceManager.h"
#include "Game/Scene.h"
#include "Game/ObjectPool.h"
#include "GameObjects/CameraObject.h"
#include "GameObjects/GameObject.h"
#include "GameObjects/Player.h"

SceneSample::SceneSample(Game* pGame, ResourceManager* pResources)
: Scene( pGame, pResources )
{
}

SceneSample::~SceneSample()
{
}

void SceneSample::LoadContent()
{
    Scene::LoadContent();

    // Create our GameObjects.
    {
        // Camera.
        CameraObject* pCamera = new CameraObject( this, "Camera", vec3(0,0,-15), vec3(0,0,0), vec3(1,1,1) );
        AddGameObject( pCamera );

        Player* pPlayer = new Player( this, "Player", vec3(0,0,0), vec3(0,0,0), vec3(1,1,1), m_pResources->GetMesh( "Box" ), m_pResources->GetMaterial( "Megaman" ) );
        AddGameObject( pPlayer );

        // Assign our controllers.
        pPlayer->SetPlayerController( m_pGame->GetController( 0 ) );



       
    }
}

void SceneSample::OnEvent(Event* pEvent)
{
    Scene::OnEvent( pEvent );
}

void SceneSample::Update(float deltaTime)
{
    Scene::Update( deltaTime );
}

void SceneSample::Draw()
{
    Scene::Draw();
}
