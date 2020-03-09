#include "GamePCH.h"

#include "OptionScene.h"
#include "GameObjects/GameObject.h"
#include "BulletScene1/ThirdP_Camera.h"
#include "Game/ResourceManager.h"
#include "Game/Game.h"
#include "Game/SceneManager.h"
#include "LightSampleScene/LightSampleScene.h"
#include "Audio/SoundPlayer.h"

OptionScene::OptionScene(Game* pGame, ResourceManager* pResource)
    :Scene(pGame, pResource)
{
    //m_IsOpaque = true;//main menu is the first scene to be pushed , so by default this is opaque
    m_CanSelect = true;
}

OptionScene::~OptionScene()
{

}

void OptionScene::LoadContent()
{
    //just a normal Camera, no need for ThirdP_Camera
    CameraObject* pCamera = new CameraObject(this, "Camera", vec3(0, 0, -5), vec3(0), vec3(1));
    pCamera->SetIsOrtho(true);
    AddGameObject(pCamera);

    //Volumn item
    GameObject* pVolumn_Item = new GameObject(this, "Volumn_Item", vec3(0, 1, 0), vec3(0), vec3(3, 1, 1), m_pResources->GetMesh("Box"), m_pResources->GetMaterial("Volumn_Item"));
    AddGameObject(pVolumn_Item);
    m_pItems.push_back(pVolumn_Item);

    //Back item
    GameObject* pBack_Item = new GameObject(this, "Back_Item", vec3(0, -3, 0), vec3(0), vec3(3, 1, 1), m_pResources->GetMesh("Box"), m_pResources->GetMaterial("Back_Item"));
    AddGameObject(pBack_Item);
    m_pItems.push_back(pBack_Item);

    //Volumn Bar
    //GameObject* pVolumnBar=new GameObject(this,"VolumnBar",vec3(0),vec3(0),vec3(1),m_pResources->GetMesh("Box"),m_pResources->GetMaterial(""))


    //Hight Light item
    GameObject* pHighLight = new GameObject(this, "HighLight", vec3(0, 1, 0), vec3(0), vec3(3, 1, 1), m_pResources->GetMesh("Box"), m_pResources->GetMaterial("HighLight_Item"));
    AddGameObject(pHighLight);




}

void OptionScene::OnEvent(Event* pEvent)
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

        static float ratio = 0.0f;
        //handle select scene 
        if (pInput->GetInputDeviceType() == InputDeviceType_Keyboard && pInput->GetID() == VK_RETURN)
        {
            if (pInput->GetInputState() == InputState_Pressed && m_CanSelect)
            {
                switch (m_SelectedItemIdx)
                {

                case(1):
                    m_pGame->GetSceneManager()->PopAllScenes();
                    m_pGame->GetSceneManager()->PushToActiveScenes("MainMenuScene");

                    m_CanSelect = false;
                    break;


                default:
                    break;
                }

            }
            else if (pInput->GetInputState() == InputState_Released)
                m_CanSelect = true; // when released, we can select again now
        }

        //if (pInput->GetInputDeviceType() == InputDeviceType_Keyboard && pInput->GetID() == VK_LEFT && m_SelectedItemIdx==0)
        {
            if (pInput->GetInputState() == InputState_Pressed && m_CanSelect && m_SelectedItemIdx==0)
            {

                if (pInput->GetID() == VK_LEFT)
                {
                    
                    ((LightSampleScene*)m_pGame->GetSceneManager()->GetScene("LightTestScene"))->GetSoundPlayer()->AdjustVolumn(ratio -= 0.15f, 0);
                    if (ratio <= 0)
                        ratio = 0.1f;
                }
                else if (pInput->GetID() == VK_RIGHT)
                {
                    ((LightSampleScene*)m_pGame->GetSceneManager()->GetScene("LightTestScene"))->GetSoundPlayer()->AdjustVolumn(ratio += 0.15f, 0);
                    if (ratio  >0.5f)
                        ratio = 0.5f;
                }

                m_CanSelect = false;
            }
            else if (pInput->GetInputState() == InputState_Released)
                m_CanSelect = true; // when released, we can select again now
        }
    }
}

void OptionScene::Update(float delta)
{
    Scene::Update(delta);


}


void OptionScene::Draw()
{
    Scene::Draw();
}

void OptionScene::Reset()
{
    //every time run into this scene, make sure reset neccecery stuff
    m_CanSelect = true;
    m_SelectedItemIdx = 0;
    //m_IsOpaque = true;
}
