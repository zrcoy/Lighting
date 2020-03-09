#include "GamePCH.h"

#include "Game.h"
#include "Game/ResourceManager.h"
#include "Game/ObjectPool.h"
#include "Scene.h"
#include "GameObjects/GameObject.h"
#include "GameObjects/CameraObject.h"
#include "GameObjects/Player.h"
#include "Physics/BulletManager.h"
#include "Mesh/LightInfo.h"

Scene::Scene(Game* pGame, ResourceManager* pResources)
{
    m_pGame = pGame;
    m_pResources = pResources;

    m_pBulletManager = nullptr;
    //m_IsOpaque = false;
}

Scene::~Scene()
{
    Cleanup();
}

void Scene::Cleanup()
{
    for( auto pObject: m_pGameObjects )
    {
        delete pObject;
    }
    m_pGameObjects.clear();

    for (auto light : m_vLights)
    {
        delete light;
    }
    m_vLights.clear();
}

void Scene::LoadContent()
{
}

void Scene::Reset()
{
    // Reset all of the Scene objects in the list.
    for( auto pObject: m_pGameObjects )
    {
        pObject->Reset();
    }
}

void Scene::OnEvent(Event* pEvent)
{
    // Send the event to Scene objects in the list.
    for( auto pObject: m_pGameObjects )
    {
        pObject->OnEvent( pEvent );
    }
}

void Scene::Update(float deltaTime)
{
    if (m_pBulletManager != nullptr)
    {

        m_pBulletManager->Update(deltaTime);
    }

    CheckForGLErrors();

    // Update all of the Scene objects in the list.
    for( unsigned int i=0; i<m_pGameObjects.size(); i++ )
    {
        m_pGameObjects[i]->Update( deltaTime );
    }

    CheckForGLErrors();
}

void Scene::Draw()
{
    CheckForGLErrors();

    CameraObject* pCamera = static_cast<CameraObject*>( GetGameObjectByName( "Camera" ) );
    assert( pCamera );

    // Render all of the Scene objects in the list.
    for( auto pObject: m_pGameObjects )
    {
        glDisable(GL_CULL_FACE);
        pObject->Draw( pCamera );
        glEnable(GL_CULL_FACE);

    }

    CheckForGLErrors();
}

void Scene::AddGameObject(GameObject* pObject)
{
    m_pGameObjects.push_back( pObject );
}

bool Scene::RemoveGameObject(GameObject* pObject)
{
    auto iteratorForObject = std::find( m_pGameObjects.begin(), m_pGameObjects.end(), pObject );
    
    if( iteratorForObject != m_pGameObjects.end() )
    {
        m_pGameObjects.erase( iteratorForObject );
        return true;
    }

    return false;
}

bool Scene::IsGameObjectInScene(GameObject* pObject)
{
    auto iteratorForObject = std::find( m_pGameObjects.begin(), m_pGameObjects.end(), pObject );

    if( iteratorForObject != m_pGameObjects.end() )
    {
        return true;
    }

    return false;
}

GameObject* Scene::GetGameObjectByName(std::string name)
{
    for( auto pObject: m_pGameObjects )
    {
        if( pObject->GetName() == name )
        {
            return pObject;
        }
    }

    return nullptr;
}

LightInfo* Scene::GetLight(std::string name)
{
    for (auto light : m_vLights)
    {
        if (light->m_Name == name)
        {
            return light;
        }
    }
    return nullptr;
}


