#include "GamePCH.h"

#include "LevelChoiceScene.h"
#include "GameObjects/GameObject.h"
#include "BulletScene1/ThirdP_Camera.h"
#include "Game/ResourceManager.h"
#include "Game/Game.h"
#include "Game/SceneManager.h"
#include "LightSampleScene/LightSampleScene.h"

LevelChoiceScene::LevelChoiceScene(Game* pGame, ResourceManager* pResource)
    :Scene(pGame, pResource)
{
    m_CanSelect = true;
}

LevelChoiceScene::~LevelChoiceScene()
{

}

void LevelChoiceScene::LoadContent()
{
    //just a normal Camera, no need for ThirdP_Camera
    CameraObject* pCamera = new CameraObject(this, "Camera", vec3(0, 0, -5), vec3(0), vec3(1));
    pCamera->SetIsOrtho(true);
    AddGameObject(pCamera);

    //BulletTestScene item
    GameObject* pBulletTestScene_Item = new GameObject(this, "BulletTestScene_Item", vec3(0, 1, 0), vec3(0), vec3(3, 1, 1), m_pResources->GetMesh("Box"), m_pResources->GetMaterial("BulletScene_Item"));
    AddGameObject(pBulletTestScene_Item);
    m_pItems.push_back(pBulletTestScene_Item);

    //LightTestScene item
    GameObject* pLightTestScene_Item = new GameObject(this, "LightTestScene_Item", vec3(0, -1, 0), vec3(0), vec3(3, 1, 1), m_pResources->GetMesh("Box"), m_pResources->GetMaterial("LightScene_Item"));
    AddGameObject(pLightTestScene_Item);
    m_pItems.push_back(pLightTestScene_Item);

    //Back item
    GameObject* pBack_Item = new GameObject(this, "Back_Item", vec3(0, -3, 0), vec3(0), vec3(3, 1, 1), m_pResources->GetMesh("Box"), m_pResources->GetMaterial("Back_Item"));
    AddGameObject(pBack_Item);
    m_pItems.push_back(pBack_Item);


    //Hight Light item must be drawn later than all the items
    GameObject* pHighLight = new GameObject(this, "HighLight", vec3(0, 1, 0), vec3(0), vec3(3, 1, 1), m_pResources->GetMesh("Box"), m_pResources->GetMaterial("HighLight_Item"));
    AddGameObject(pHighLight);




}

void LevelChoiceScene::OnEvent(Event* pEvent)
{
    Scene::OnEvent(pEvent);

    if (pEvent->GetEventType() == EventType_Input)
    {
        InputEvent* pInput = (InputEvent*)pEvent;

        if (pInput->GetInputDeviceType() == InputDeviceType_Mouse && pInput->GetID() == 2)      // scroll up
        {
            m_SelectedItemIdx--;
            if (m_SelectedItemIdx < 0)// clamp upside edge
                m_SelectedItemIdx = m_pItems.size() - 1;

        }
        if (pInput->GetInputDeviceType() == InputDeviceType_Mouse && pInput->GetID() == 3)      // scroll down
        {
            m_SelectedItemIdx++;
            if (m_SelectedItemIdx >(m_pItems.size() - 1))//clamp downside edge
                m_SelectedItemIdx = 0;
        }
        GetGameObjectByName("HighLight")->SetPosition(m_pItems[m_SelectedItemIdx]->GetPosition());// high light the selected item



        //handle select scene 
        if (pInput->GetInputDeviceType() == InputDeviceType_Keyboard && pInput->GetID() == VK_RETURN)
        {
            if (pInput->GetInputState() == InputState_Pressed && m_CanSelect)
            {

                switch (m_SelectedItemIdx)
                {
                case(0):
                    m_pGame->GetSceneManager()->PopAllScenes();
                    m_pGame->GetSceneManager()->PushToActiveScenes("BulletTestScene")->Reset();

                    m_CanSelect = false;
                    break;
                case(1):
                    m_pGame->GetSceneManager()->PopAllScenes();
                    m_pGame->GetSceneManager()->PushToActiveScenes("LightTestScene")->Reset();
                    ((LightSampleScene*)m_pGame->GetSceneManager()->GetScene("LightTestScene"))->SetPause(false);
                    ((LightSampleScene*)m_pGame->GetSceneManager()->GetScene("LightTestScene"))->Reset();
                    m_CanSelect = false;
                    break;
                case(2):
                    m_pGame->GetSceneManager()->PopScene();

                    m_CanSelect = false;
                    break;

                default:
                    break;
                }
            }
            else if(pInput->GetInputState() == InputState_Released)
                m_CanSelect = true; // when released, we can select again now
        }
    }
}

void LevelChoiceScene::Update(float delta)
{
    Scene::Update(delta);


}


void LevelChoiceScene::Draw()
{
    Scene::Draw();
}

void LevelChoiceScene::Reset()
{
    //every time run into this scene, make sure reset neccecery stuff
    m_CanSelect = true;
    m_SelectedItemIdx = 0;
    //m_IsOpaque = true;
}
