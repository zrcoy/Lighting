#include "GamePCH.h"

#include "MainMenuScene.h"
#include "GameObjects/GameObject.h"
#include "BulletScene1/ThirdP_Camera.h"
#include "Game/ResourceManager.h"
#include "Game/Game.h"
#include "Game/SceneManager.h"

MainMenuScene::MainMenuScene(Game* pGame, ResourceManager* pResource)
    :Scene(pGame, pResource)
{
    //m_IsOpaque = true;//main menu is the first scene to be pushed , so by default this is opaque
    m_CanSelect = true;
}

MainMenuScene::~MainMenuScene()
{

}

void MainMenuScene::LoadContent()
{
    //just a normal Camera, no need for ThirdP_Camera
    CameraObject* pCamera = new CameraObject(this, "Camera", vec3(0, 0, -5), vec3(0), vec3(1));
    pCamera->SetIsOrtho(true);
    AddGameObject(pCamera);

    //Play item
    GameObject* pPlay_Item = new GameObject(this, "Play_Item", vec3(0, 1, 0), vec3(0), vec3(3,1,1), m_pResources->GetMesh("Box"), m_pResources->GetMaterial("Play_Item"));
    AddGameObject(pPlay_Item);
    m_pItems.push_back(pPlay_Item);


    //Option item
    GameObject* pOption_Item = new GameObject(this, "Option_Item", vec3(0, -1, 0), vec3(0), vec3(3, 1, 1), m_pResources->GetMesh("Box"), m_pResources->GetMaterial("Option_Item"));
    AddGameObject(pOption_Item);
    m_pItems.push_back(pOption_Item);

    //Quit item
    GameObject* pQuit_Item = new GameObject(this, "Quit_Item", vec3(0, -3, 0), vec3(0), vec3(3, 1, 1), m_pResources->GetMesh("Box"), m_pResources->GetMaterial("Quit_Item"));
    AddGameObject(pQuit_Item);
    m_pItems.push_back(pQuit_Item);


    //Hight Light item
    GameObject* pHighLight = new GameObject(this, "HighLight", vec3(0, 1, 0), vec3(0), vec3(3, 1, 1), m_pResources->GetMesh("Box"), m_pResources->GetMaterial("HighLight_Item"));
    AddGameObject(pHighLight);

    


}

void MainMenuScene::OnEvent(Event* pEvent)
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
            if (m_SelectedItemIdx > (m_pItems.size() - 1))//clamp downside edge
                m_SelectedItemIdx = 0;
        }
        GetGameObjectByName("HighLight")->SetPosition(m_pItems[m_SelectedItemIdx]->GetPosition());// high light the selected item

        vec3 pos = GetGameObjectByName("HighLight")->GetPosition();
        int bp = 0;
    
     
        //handle select scene 
        if (pInput->GetInputDeviceType() == InputDeviceType_Keyboard && pInput->GetID() == VK_RETURN)
        {
            if (pInput->GetInputState() == InputState_Pressed && m_CanSelect)
            {
                switch (m_SelectedItemIdx)
                {
                case(0):
                    
                    m_pGame->GetSceneManager()->PushToActiveScenes("LevelChoiceScene")->Reset();


                    m_CanSelect = false;
                    break;
                case(1):
                    m_pGame->GetSceneManager()->PopAllScenes();
                    m_pGame->GetSceneManager()->PushToActiveScenes("OptionScene")->Reset();

                    m_CanSelect = false;
                    break;
                case(2):
                    //Close the framework
                    m_pGame->GetFramework()->SetCloseRequestBool(true);
                    m_CanSelect = false;
                    break;

                default:
                    break;
                }

            }
            else if (pInput->GetInputState() == InputState_Released)
                m_CanSelect = true; // when released, we can select again now
        }
    }
}

void MainMenuScene::Update(float delta)
{
    Scene::Update(delta);

  
}


void MainMenuScene::Draw()
{
    Scene::Draw();
}

void MainMenuScene::Reset()
{
    //every time run into this scene, make sure reset neccecery stuff
    m_CanSelect = true;
    m_SelectedItemIdx = 0;
    //m_IsOpaque = true;
}
