#include "GamePCH.h"
#include "SceneManager.h"
#include "Game/Scene.h"

SceneManager::SceneManager()
{

}

SceneManager::~SceneManager()
{
    for (auto pScene : m_pScenes)
        delete pScene.second;
}

void SceneManager::AddScene(std::string name, Scene* pScene)
{
    m_pScenes[name] = pScene;
}

Scene* SceneManager::PushToActiveScenes(std::string name)
{
    m_pActiveScenes.push_back(m_pScenes[name]);
    return m_pScenes[name];
}

void SceneManager::PopScene()
{
    m_pActiveScenes.pop_back();
}

void SceneManager::PopAllScenes()
{
    while (!m_pActiveScenes.empty())
        PopScene();
}

void SceneManager::LoadContent()
{
    //load every scene content in the map
    for (auto pScene : m_pScenes)
    {
        pScene.second->LoadContent();
    }
}

void SceneManager::OnEvent(Event* pEvent)
{
    m_pActiveScenes.back()->OnEvent(pEvent);
}

void SceneManager::Update(float deltaTime)
{
   
        m_pActiveScenes.back()->Update(deltaTime);
    
}

void SceneManager::Draw()
{
    for (unsigned int i = 0; i < m_pActiveScenes.size(); i++)
    {
        m_pActiveScenes[i]->Draw();
    }
}


std::string SceneManager::GetActiveSceneName(Scene* pScene)
{
    
    for (auto p : m_pScenes)
    {
        if (p.second == pScene)
        {
            return p.first;// find the matching scene's string name  
        }
    }
}