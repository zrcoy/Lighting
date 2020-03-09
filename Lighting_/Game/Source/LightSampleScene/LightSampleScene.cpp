#include "GamePCH.h"
#include <string>
#include "LightSampleScene.h"
#include "Game/Game.h"
#include "Game/ResourceManager.h"
#include "Game/Scene.h"
#include "Game/ObjectPool.h"
#include "GameObjects/CameraObject.h"
#include "GameObjects/GameObject.h"
#include "GameObjects/Player.h"
#include "BulletScene1/ThirdP_Camera.h"
#include "Mesh/LightInfo.h"

#include "Physics/BulletManager.h"
#include "LightSampleScene/LightScene_UniformColorOBJ.h"
#include "Audio/SoundPlayer.h"
#include "Audio/SoundCue.h"
#include "Audio/SoundObject.h"
#include "Audio/RandomWeightedCue.h"
#include "Audio/ShuffleAudioCue.h"
#include "Audio/SoundChannel.h"
#include "GameObjects/TweenObject.h"
#include "Game/TweenFuncs.h"
#include "BulletScene1/BulletScenePlayer.h"
#include "Game/SceneManager.h"
#include "BulletScene1/BulletScene_Telepoter.h"

LightSampleScene::LightSampleScene(Game* pGame, ResourceManager* pResources)
    : Scene(pGame, pResources)
    , m_Amplitude(0.0f)
    , m_Frequency(0.5f)

{
    m_pBulletManager = nullptr;
    m_pSoundPlayer = nullptr;
    m_pJumpCue = nullptr;
    m_pPunchCues = nullptr;
    m_pCollectionCue = nullptr;
    m_pGoalCue = nullptr;
    m_pShuffleCue = nullptr;
    m_pBGCue = nullptr;
    m_IsGreyScale = false;

    m_CanSelect = true;
    m_IsPause = false;
    m_Win = true;
}

LightSampleScene::~LightSampleScene()
{
    for (auto tween : m_pTweens)
    {
        delete tween;
    }
    m_pTweens.clear();
    delete m_pBGCue;
    delete m_pShuffleCue;
    delete m_pJumpCue;
    delete m_pCollectionCue;
    delete m_pPunchCues;
    delete m_pGoalCue;
    delete m_pSoundPlayer;
    delete m_pBulletManager;
}

void LightSampleScene::LoadContent()
{
    Scene::LoadContent();

    //Set the physics world
    m_pBulletManager = new BulletManager();






    //Some useful values
    float ground_width = 200.0f;
    float ground_height = 1.0f;
    float ground_length = 200.0f;
    vec3 ground_size = vec3(ground_width, ground_height, ground_length);
    float leftWall_width = 1.0f;
    float leftWall_height = 15.0f;
    float leftWall_length = 100.0f;
    vec3 leftWall_size = vec3(leftWall_width, leftWall_height, leftWall_length);
    float upWall_width = 100.0f;
    float upWall_height = 30.0f;
    float upWall_length = 1.0f;
    vec3 upWall_size = vec3(upWall_width, upWall_height, upWall_length);
    float upWall2_width = 100.0f;
    float upWall2_height = 10.0f;
    float upWall2_length = 1.0f;
    vec3 upWall2_size = vec3(upWall2_width, upWall2_height, upWall2_length);
    float sceneCube_width = 10.0f;
    float sceneCube_height = 10.0f;
    float sceneCube_length = 10.0f;
    vec3 sceneCube_size = vec3(sceneCube_width, sceneCube_height, sceneCube_length);
    float BulletScene_telepoter_width = 2.0f;
    float BulletScene_telepoter_height = 2.0f;
    float BulletScene_telepoter_length = 2.0f;
    vec3 BulletScene_telepoter_size = vec3(BulletScene_telepoter_width, BulletScene_telepoter_height, BulletScene_telepoter_length);



    // Create our GameObjects.
    {


        //fill 5 Light info 

        const int numOfLights = 5;

        for (int i = 0; i < numOfLights; i++)
        {
            vec3 offset = vec3(25, 0, 0);
            m_vLights.push_back(new LightInfo(vec3(0, 20, 0) + offset * i, 30.0f, "None", i % 2, vec3(1, 1, 1)));

        }



        SpawnP2PJoint(vec3(21.5f, 1.0f, -42), vec3(21.5f, 6.5f, -42));

        //skybox
        GameObject* pSkybox = new GameObject(this, "Skybox", vec3(0,0,0), vec3(0), vec3(600.0f), m_pResources->GetMesh("Sphere"), m_pResources->GetMaterial("Skybox"));
        AddGameObject(pSkybox);
        AddCurrentSceneObj(pSkybox);


        //Player
        BulletScenePlayer* pPlayer = new BulletScenePlayer(this, "LightPlayer", vec3(-5, 1.5f, 5), vec3(0), vec3(1), m_pResources->GetMesh("Sphere"), m_pResources->GetMaterial("Cubemap"));
        AddGameObject(pPlayer);
        AddCurrentSceneObj(pPlayer);
        pPlayer->CreateBody(m_pResources->GetCollisionShape("DefaultCollisionSphere"), 1.0f);
        pPlayer->SetPlayerController(m_pGame->GetController(0));
        //pPlayer->Get3DBody()->setGravity(btVector3(0, 0, 0));
        //add one light attaching to the player
        vec3 playerLightOff = vec3(0, 2, 0);
        LightInfo* light = new LightInfo(pPlayer->GetPosition() + playerLightOff, 10.0f, "playerLight1", 0, vec3(1, 1, 1));
        m_vLights.push_back(light);

        //Ground
        GameObject* pGround = new GameObject(this, "LightGround", vec3(0, 0, 0), vec3(0, 0, 0), ground_size, m_pResources->GetMesh("LightCube"), m_pResources->GetMaterial("GroundForest"));
        AddGameObject(pGround);
        AddCurrentSceneObj(pGround);
        pGround->CreateBody(m_pResources->GetCollisionShape("Light_GroundCollisionShape"));

        // uniformly colored object
        LightScene_UniformColorOBJ* pCube = new LightScene_UniformColorOBJ(this, "UniformColorCube", vec3(20, 2, 5), vec3(0, 0, 0), vec3(1, 1, 1), m_pResources->GetMesh("LightCube"), m_pResources->GetMaterial("UniformColor"));
        AddGameObject(pCube);
        AddCurrentSceneObj(pCube);


        // uniformly colored object
        LightScene_UniformColorOBJ* pCube1 = new LightScene_UniformColorOBJ(this, "UniformColorCube", vec3(6, 1.5f, -15), vec3(0, 0, 0), vec3(1, 1, 1), m_pResources->GetMesh("LightCube"), m_pResources->GetMaterial("UniformColor"));
        AddGameObject(pCube1);
        AddCurrentSceneObj(pCube1);


        // uniformly colored object
        LightScene_UniformColorOBJ* pCube2 = new LightScene_UniformColorOBJ(this, "UniformColorCube", vec3(1, 1.5f, -15), vec3(0, 0, 0), vec3(1, 1, 1), m_pResources->GetMesh("LightCube"), m_pResources->GetMaterial("UniformColor"));
        AddGameObject(pCube2);
        AddCurrentSceneObj(pCube2);


        // uniformly colored object
        LightScene_UniformColorOBJ* pCube3 = new LightScene_UniformColorOBJ(this, "UniformColorCube", vec3(3, 1.5f, -11), vec3(0, 0, 0), vec3(1, 1, 1), m_pResources->GetMesh("LightCube"), m_pResources->GetMaterial("UniformColor"));
        AddGameObject(pCube3);
        AddCurrentSceneObj(pCube3);


        //left wall
        GameObject* pLeftWall = new GameObject(this, "LightLeftWall", vec3(-10, 5, 0), vec3(0, 0, 0), leftWall_size, m_pResources->GetMesh("LightCube"), m_pResources->GetMaterial("Brick"));
        AddGameObject(pLeftWall);
        AddCurrentSceneObj(pLeftWall);
        pLeftWall->CreateBody(m_pResources->GetCollisionShape("Light_LeftWallCollisionShape"));

        //right wall
        GameObject* pRightWall = new GameObject(this, "LightRightWall", vec3(70, 5, 0), vec3(0, 0, 0), leftWall_size, m_pResources->GetMesh("LightCube"), m_pResources->GetMaterial("Brick"));
        AddGameObject(pRightWall);
        AddCurrentSceneObj(pRightWall);
        pRightWall->CreateBody(m_pResources->GetCollisionShape("Light_LeftWallCollisionShape"));

        //up wall 
        GameObject* pUpWall = new GameObject(this, "LightUpWall", vec3(40, 5, 35), vec3(0, 0, 0), upWall_size, m_pResources->GetMesh("LightCube"), m_pResources->GetMaterial("Brick"));
        AddGameObject(pUpWall);
        AddCurrentSceneObj(pUpWall);
        pUpWall->CreateBody(m_pResources->GetCollisionShape("Light_UpWallCollisionShape"));


        //up wall 2
        GameObject* pUpWall2 = new GameObject(this, "LightUpWall2", vec3(40, 5, 15), vec3(0, 0, 0), upWall2_size, m_pResources->GetMesh("LightCube"), m_pResources->GetMaterial("Brick"));
        AddGameObject(pUpWall2);
        AddCurrentSceneObj(pUpWall2);
        pUpWall2->CreateBody(m_pResources->GetCollisionShape("Light_UpWall2CollisionShape"));

        //up wall 3
        GameObject* pUpWall3 = new GameObject(this, "LightUpWall3", vec3(50, 5, -5), vec3(0, 0, 0), upWall_size, m_pResources->GetMesh("LightCube"), m_pResources->GetMaterial("Brick"));
        AddGameObject(pUpWall3);
        AddCurrentSceneObj(pUpWall3);
        pUpWall3->CreateBody(m_pResources->GetCollisionShape("Light_UpWallCollisionShape"));

        //up wall 4
        GameObject* pUpWall4 = new GameObject(this, "LightUpWall4", vec3(40, 5, -10), vec3(0, 0, 0), upWall_size, m_pResources->GetMesh("LightCube"), m_pResources->GetMaterial("Brick"));
        AddGameObject(pUpWall4);
        AddCurrentSceneObj(pUpWall4);
        pUpWall4->CreateBody(m_pResources->GetCollisionShape("Light_UpWallCollisionShape"));

        //up wall 5
        GameObject* pUpWall5 = new GameObject(this, "LightUpWall5", vec3(40, 5, -20), vec3(0, 0, 0), vec3(130.0f,15.0f,1.0f), m_pResources->GetMesh("LightCube"), m_pResources->GetMaterial("Brick"));
        AddGameObject(pUpWall5);
        AddCurrentSceneObj(pUpWall5);
        pUpWall5->CreateBody(m_pResources->GetCollisionShape("Light_UpWall5CollisionShape"));

        //up wall 6
        LightScene_UniformColorOBJ* pUpWall6 = new LightScene_UniformColorOBJ(this, "LightUpWall5", vec3(40, 5, -48), vec3(0, 0, 0), vec3(130.0f, 15.0f, 1.0f), m_pResources->GetMesh("LightCube"), m_pResources->GetMaterial("UniformColor"));
        AddGameObject(pUpWall6);
        AddCurrentSceneObj(pUpWall6);
        pUpWall6->CreateBody(m_pResources->GetCollisionShape("Light_UpWall5CollisionShape"));
        pUpWall6->IsRotator(false);

        //teleporter
        BulletScene_Telepoter* pTelepoter = new BulletScene_Telepoter(this, "Telepoter", vec3(6, 2, 4), vec3(0), BulletScene_telepoter_size, m_pResources->GetMesh("Teleporter"), m_pResources->GetMaterial("T1"));
        AddGameObject(pTelepoter);
        AddCurrentSceneObj(pTelepoter);
        pTelepoter->SetDestination(vec3(96, 4.5f, -7));

        //teleporter2
        BulletScene_Telepoter* pTelepoter2 = new BulletScene_Telepoter(this, "Telepoter", vec3(76, 1.5f, -15), vec3(0), BulletScene_telepoter_size, m_pResources->GetMesh("Teleporter"), m_pResources->GetMaterial("T1"));
        AddGameObject(pTelepoter2);
        AddCurrentSceneObj(pTelepoter2);
        pTelepoter2->SetDestination(vec3(60.0f, 1.5f, -15.0f));

        //teleporter3
        BulletScene_Telepoter* pTelepoter3 = new BulletScene_Telepoter(this, "Telepoter", vec3(-4.0f, 1.5f, -15.0f), vec3(0), BulletScene_telepoter_size, m_pResources->GetMesh("Teleporter"), m_pResources->GetMaterial("T1"));
        AddGameObject(pTelepoter3);
        AddCurrentSceneObj(pTelepoter3);
        pTelepoter3->SetDestination(vec3(18.0f, 1.5f, -31.0f));

        //teleporter4
        BulletScene_Telepoter* pTelepoter4 = new BulletScene_Telepoter(this, "Telepoter", vec3(60.0f, 1.5f, -26.0f), vec3(0), BulletScene_telepoter_size, m_pResources->GetMesh("Teleporter"), m_pResources->GetMaterial("T1"));
        AddGameObject(pTelepoter4);
        AddCurrentSceneObj(pTelepoter4);
        pTelepoter4->SetDestination(this->GetGameObjectByName("B")->GetPosition()+vec3(0,10,0));


        //Third person camera
        ThirdP_Camera* pThirdCam = new ThirdP_Camera(this, "Camera", vec3(0, 0, 0), vec3(0), vec3(1));
        pThirdCam->SetObjectToFollow(pPlayer, 5.0f);
        AddGameObject(pThirdCam);
        AddCurrentSceneObj(pThirdCam);

        //Sound 
        m_pSoundPlayer = new SoundPlayer();
        //punch
        SoundObject* pPunchSoundOBJ = new SoundObject(50);
        pPunchSoundOBJ = m_pSoundPlayer->LoadSound("Data/Sound/Punch.wav", pPunchSoundOBJ);
        SoundObject* pPunchSoundOBJ1 = new SoundObject(100);
        pPunchSoundOBJ1 = m_pSoundPlayer->LoadSound("Data/Sound/Punch1.wav", pPunchSoundOBJ1);
        SoundObject* pPunchSoundOBJ2 = new SoundObject(200);
        pPunchSoundOBJ2 = m_pSoundPlayer->LoadSound("Data/Sound/Punch2.wav", pPunchSoundOBJ2);
        //collective
        SoundObject* pGotItem = new SoundObject(50);
        pGotItem = m_pSoundPlayer->LoadSound("Data/Sound/GotItem.wav", pGotItem);
        SoundObject* pPowerup1 = new SoundObject(100);
        pPowerup1 = m_pSoundPlayer->LoadSound("Data/Sound/Powerup1.wav", pPowerup1);
        //goal
        SoundObject* pHelicopter = new SoundObject(50);
        pHelicopter = m_pSoundPlayer->LoadSound("Data/Sound/helicopter.wav", pHelicopter);
        //jump
        SoundObject* pJump1 = new SoundObject(50);
        pJump1 = m_pSoundPlayer->LoadSound("Data/Sound/Jump1.wav", pJump1);
        SoundObject* pJump2 = new SoundObject(100);
        pJump2 = m_pSoundPlayer->LoadSound("Data/Sound/Jump2.wav", pJump2);
        //BG
        SoundObject* pBGMusic = new SoundObject(50);
        pBGMusic = m_pSoundPlayer->LoadSound("Data/Sound/FeelingGood_BG.wav", pBGMusic);
        SoundObject* pBGMusic2 = new SoundObject(200);
        pBGMusic2 = m_pSoundPlayer->LoadSound("Data/Sound/BG2.wav", pBGMusic2);
        SoundObject* pBGMusic3 = new SoundObject(150);
        pBGMusic3 = m_pSoundPlayer->LoadSound("Data/Sound/BG3.wav", pBGMusic3);

        //add them to the resource manager
        m_pResources->AddSoundObject("Punch_Clip", pPunchSoundOBJ);
        m_pResources->AddSoundObject("Punch_Clip1", pPunchSoundOBJ1);
        m_pResources->AddSoundObject("Punch_Clip2", pPunchSoundOBJ2);
        m_pResources->AddSoundObject("GotItem", pGotItem);
        m_pResources->AddSoundObject("Helicopter", pHelicopter);
        m_pResources->AddSoundObject("Jump1", pJump1);
        m_pResources->AddSoundObject("Jump2", pJump2);
        m_pResources->AddSoundObject("Powerup1", pPowerup1);
        m_pResources->AddSoundObject("BGMusic", pBGMusic);
        m_pResources->AddSoundObject("BGMusic2", pBGMusic2);
        m_pResources->AddSoundObject("BGMusic3", pBGMusic3);

        // play BG music first, there's no magic on BG cue, just make it a normal SoundCue
        m_pBGCue = new SoundCue();
        m_pBGCue->AddSound(m_pResources->GetSoundObject("BGMusic"));
        m_pBGCue->AddSound(m_pResources->GetSoundObject("BGMusic2"));
        m_pBGCue->AddSound(m_pResources->GetSoundObject("BGMusic3"));
        m_pSoundPlayer->PlayBGCue(m_pBGCue);// play bg music randomly
        m_pSoundPlayer->AdjustVolumn(0.1f, 0);// lower our bg music


        // random cue for collision
        m_pPunchCues = new RandomWeightedCue();
        m_pPunchCues->AddSound(m_pResources->GetSoundObject("Punch_Clip"));
        m_pPunchCues->AddSound(m_pResources->GetSoundObject("Punch_Clip1"));
        m_pPunchCues->AddSound(m_pResources->GetSoundObject("Punch_Clip2"));
        // random cue for collection
        m_pCollectionCue = new RandomWeightedCue();
        m_pCollectionCue->AddSound(m_pResources->GetSoundObject("GotItem"));
        m_pCollectionCue->AddSound(m_pResources->GetSoundObject("Powerup1"));
        // random cue for goal, for now ,just one 
        m_pGoalCue = new RandomWeightedCue();
        m_pGoalCue->AddSound(m_pResources->GetSoundObject("Helicopter"));
        // random cue for jump
        m_pJumpCue = new RandomWeightedCue();
        m_pJumpCue->AddSound(m_pResources->GetSoundObject("Jump1"));
        m_pJumpCue->AddSound(m_pResources->GetSoundObject("Jump2"));

        //Shuffle cue
        m_pShuffleCue = new ShuffleAudioCue();
        //((ShuffleAudioCue*)m_pShuffleCue)->Shuffle();



        //Cubemap
        GameObject* pReflectionSphere = new GameObject(this, "ReflectionSphere", vec3(40, 30, 0), vec3(0, 0, 0), vec3(10), m_pResources->GetMesh("DefaultCube"), m_pResources->GetMaterial("Cubemap"));

        AddGameObject(pReflectionSphere);
        AddCurrentSceneObj(pReflectionSphere);
        pReflectionSphere->CreateBody(m_pResources->GetCollisionShape("DefaultCollisionSphere"), 1.0f);
        pReflectionSphere->Get3DBody()->setGravity(btVector3(0, 0, 0));


        
    }


    //after game objs setup the tween
    //setup tween
    {
        TweenObject* ptx_elasticEaseInOut = new TweenObject();
        ptx_elasticEaseInOut->Init(0, 1.0f, 0, 2.0f, &this->GetGameObjectByName("LightPlayer")->m_Scale.x, TweenFunc_ElasticEaseInOut, "ElasticEaseInOut_PlayerScaleX");

        TweenObject* pty_elasticEaseInOut = new TweenObject();
        pty_elasticEaseInOut->Init(0, 1.0f, 0, 5.0f, &this->GetGameObjectByName("LightPlayer")->m_Scale.y, TweenFunc_ElasticEaseInOut, "ElasticEaseInOut_PlayerScaleY");

        TweenObject* ptz_elasticEaseInOut = new TweenObject();
        ptz_elasticEaseInOut->Init(0, 1.0f, 0, 5.0f, &this->GetGameObjectByName("LightPlayer")->m_Scale.z, TweenFunc_ElasticEaseInOut, "ElasticEaseInOut_PlayerScaleZ");

        TweenObject* ptx_Linear = new TweenObject();
        ptx_Linear->Init(0, 1.0f, 0, 2.0f, &this->GetGameObjectByName("LightPlayer")->m_Scale.x, TweenFunc_Linear, "Linear_PlayerScaleX");

        TweenObject* pty_Linear = new TweenObject();
        pty_Linear->Init(0, 1.0f, 0, 5.0f, &this->GetGameObjectByName("LightPlayer")->m_Scale.y, TweenFunc_Linear, "Linear_PlayerScaleY");

        TweenObject* ptz_Linear = new TweenObject();
        ptz_Linear->Init(0, 1.0f, 0, 5.0f, &this->GetGameObjectByName("LightPlayer")->m_Scale.z, TweenFunc_Linear, "Linear_PlayerScaleZ");

        m_pTweens.push_back(ptx_elasticEaseInOut);
        m_pTweens.push_back(pty_elasticEaseInOut);
        m_pTweens.push_back(ptz_elasticEaseInOut);
        m_pTweens.push_back(ptx_Linear);
        m_pTweens.push_back(pty_Linear);
        m_pTweens.push_back(ptz_Linear);
    }




}

void LightSampleScene::OnEvent(Event* pEvent)
{
    Scene::OnEvent(pEvent);
    if (pEvent->GetEventType() == EventType_Input)
    {
        InputEvent* pInput = (InputEvent*)pEvent;


        if (pInput->GetInputDeviceType() == InputDeviceType_Mouse && pInput->GetID() == 0)      // left button id
        {
            int bp = 0;
        }
        if (pInput->GetInputDeviceType() == InputDeviceType_Mouse && pInput->GetID() == 1)      // right button id
        {
            int bp = 0;

        }
        if (pInput->GetInputDeviceType() == InputDeviceType_Mouse && pInput->GetID() == 2)      // scroll up
        {
            int bp = 0;

        }
        if (pInput->GetInputDeviceType() == InputDeviceType_Mouse && pInput->GetID() == 3)      // scroll down
        {
            int bp = 0;

            m_pSoundPlayer->PlayWeightedRandomCue((RandomWeightedCue*)m_pPunchCues);
        }
        if (pInput->GetInputDeviceType() == InputDeviceType_Keyboard && pInput->GetID() == 'P')
        {
            if (pInput->GetInputState() == InputState_Pressed && m_CanSelect)
            {
                m_pGame->GetSceneManager()->PushToActiveScenes("PauseScene");
                m_CanSelect = false;
                m_IsPause = true;
                for (auto obj : m_vCurrentSceneObjects)
                {
                    //store the properties when pause
                    obj->SetTempPos(obj->GetPosition());
                    obj->SetTempRot(obj->GetRotation());
                    obj->SetTempScale(obj->GetScale());
                }
            }
            else if (pInput->GetInputState() == InputState_Released)
                m_CanSelect = true; // when released, we can select again now
        }
    }
}

void LightSampleScene::Update(float deltaTime)
{
    Scene::Update(deltaTime);

    // update position for the light follow player
    if (GetLight("playerLight1") != nullptr)
    {
        vec3 playerLightOff = vec3(0, 2, 0);
        GetLight("playerLight1")->m_Pos = GetGameObjectByName("LightPlayer")->GetPosition() + playerLightOff;
        vec3 test = GetLight("playerLight1")->m_Pos;
        int bp = 0;
    }




    float yAngle_ReflectionSphere = this->GetGameObjectByName("ReflectionSphere")->GetRotation().y;
    yAngle_ReflectionSphere += 0.1f;
    this->GetGameObjectByName("ReflectionSphere")->SetRotation(vec3(yAngle_ReflectionSphere, yAngle_ReflectionSphere, yAngle_ReflectionSphere));


    if (m_pGame->GetImGuiFlag())
    {
        ImGui::Begin("Light Scene");


        static bool m_IsEnabled[6] = { 0,0,0,0,0,0 };
        static vec4 m_Color[6];
        static float m_Range[6] = { 10,10,10,10,10,10 };
        static bool isGrey = 0;

        for (int i = 0; i < 6; i++)
        {
            ImGui::PushID(i);
            char header[20];
            if (i < 5)
            {
                sprintf_s(header, 20, "Light%d", i);
            }
            if (i == 5)
            {
                sprintf_s(header, 20, "Light Follow Player");
            }
            if (ImGui::CollapsingHeader(header))
            {
                if (ImGui::Checkbox("IsEnabled", &m_IsEnabled[i]))
                {

                    m_vLights[i]->m_TurnOn = m_IsEnabled[i] ? 1 : 0;

                    int bp = 1;
                }
                //ImGui::Text("Color: %f, %f, %f", m_Color[i].x, m_Color[i].y, m_Color[i].z);
                //ImGui::SliderFloat("Red", &m_Color[i].x, 0, 100, "%0.3f");
                //ImGui::SliderFloat3("Color", &m_Color[i].x, 0, 100, "%0.3f");
                ImGui::DragFloat("Range", &m_Range[i], 1.0f, 0.0f, 100.f, "%.2f");
                m_vLights[i]->m_Range = m_Range[i];
                ImGui::ColorEdit3("Light Color", &m_Color[i].x);
                m_vLights[i]->m_Color = vec3(m_Color[i].x, m_Color[i].y, m_Color[i].z);

            }



            ImGui::PopID();


        }

        if (ImGui::CollapsingHeader("Grey Scale"))
        {
            if (ImGui::Checkbox("IsEnabled", &isGrey))
            {
                SetGreyScale(isGrey);
            }
        }

        // tweening the player
        const char* tweenTypes[] = { "Linear","ElasticEaseInOut" };
        static int selectedItem = 0;
        if (ImGui::Combo("Tween types for player", &selectedItem, tweenTypes, IM_ARRAYSIZE(tweenTypes)))
        {
            for (auto tween : m_pTweens)
            {
                // compare the name in imgui and part of the name in tween object
                std::string str(tweenTypes[selectedItem]);
                //if we find it, reset
                if (tween->GetName().compare(0, str.length(), str) == 0)
                {
                    tween->SetTweenFlag(true);
                    tween->Reset();
                }
                else
                {
                    tween->SetTweenFlag(false);
                }
            }
        }
        ImGui::End();
    }


    //repeat BG music
    if (m_pSoundPlayer->GetChannel(0)->IsBufferEnd() && m_pSoundPlayer->GetChannel(0)->GetState() == SoundChannel::SoundChannelState_Free)
    {
        m_pSoundPlayer->PlayBGCue(m_pBGCue);
    }



    for (auto tween : m_pTweens)
    {
        tween->Update(deltaTime);
    }



    //detect goal hit
    //Collision
    vec3 dir = this->GetGameObjectByName("B")->GetPosition() - this->GetGameObjectByName("LightPlayer")->GetPosition();
    float dist = dir.Length();
    //detect range of teleport
    if (dist <= 3.0f && m_Win)
    {
        m_IsPause = true;
        m_pSoundPlayer->StopAllSound();
        PlayVictoryCue();
        m_Win = false;
    }



}

void LightSampleScene::Draw()
{
  
    if (m_IsPause)
    {
        for (auto pObj : m_vCurrentSceneObjects)
        {
            pObj->SetScale(pObj->GetScale()*SCALE_ANI_SPEED_PER_FRAME);
        }
    }
    Scene::Draw();
}


TweenObject* LightSampleScene::GetTweenByName(std::string name)
{
    for (auto tween : m_pTweens)
    {
        if (tween->GetName() == name)
        {
            return tween;
        }
    }
    return nullptr;
}

void LightSampleScene::AddCurrentSceneObj(GameObject* pObj)
{
    m_vCurrentSceneObjects.push_back(pObj);
}

void LightSampleScene::Reset()
{
    for (auto obj : m_pGameObjects)
    {
        obj->Reset();
    }
    m_Win = true;
}

void LightSampleScene::BackToGame()
{
    for (auto pObj : m_vCurrentSceneObjects)
    {
        pObj->SetPosition(pObj->GetTempPos());
        pObj->SetRotation(pObj->GetTempRot());
        pObj->SetScale(pObj->GetTempScale());
        pObj->SyncPhysicsBodyToGraphic(pObj->GetPosition(), pObj->GetRotation());
    }
}

void LightSampleScene::PlayCollectCue()
{
      m_pSoundPlayer->PlayWeightedRandomCue((RandomWeightedCue*)m_pCollectionCue);
}

void LightSampleScene::PlayVictoryCue()
{
    m_pSoundPlayer->PlayWeightedRandomCue((RandomWeightedCue*)m_pGoalCue);
}

void LightSampleScene::SpawnHingeJoint(vec3 posA, vec3 posB)
{
    //two game objects for hinge constraint
    GameObject* pObjC = new GameObject(this, "C", posA, vec3(0), vec3(1), m_pResources->GetMesh("DefaultCube"), m_pResources->GetMaterial("Goal"));
    AddGameObject(pObjC);
    AddCurrentSceneObj(pObjC);
    pObjC->CreateBody(m_pResources->GetCollisionShape("DefaultCollisionCube"), 2.0f);//Default dynamic box
    //pObjC->CreateBody(m_pResources->GetCollisionShape("DefaultCollisionSphere"), 2.0f);//Default dynamic sphere


    GameObject* pObjD = new GameObject(this, "D", posB, vec3(0), vec3(1), m_pResources->GetMesh("DefaultCube"), m_pResources->GetMaterial("Goal"));
    AddGameObject(pObjD);
   
    pObjD->CreateBody(m_pResources->GetCollisionShape("DefaultCollisionCube"));//Default static box
    btVector3 commonPivot = pObjD->Get3DBody()->getWorldTransform().getOrigin();
    m_pBulletManager->hingeConstraint(pObjC->Get3DBody(), commonPivot, btVector3(0, 1, 0), pObjD->Get3DBody(), commonPivot, btVector3(0.0f, 1.0f, 0.0f));
}

void LightSampleScene::SpawnP2PJoint(vec3 posA, vec3 posB)
{
    //two game objects for p2p constraint
    GameObject* pObjA = new GameObject(this, "A", posA, vec3(0), vec3(1), m_pResources->GetMesh("DefaultCube"), m_pResources->GetMaterial("Goal"));
    AddGameObject(pObjA);
    AddCurrentSceneObj(pObjA);
    pObjA->CreateBody(m_pResources->GetCollisionShape("DefaultCollisionCube"), 1.0f);//Default dynamic box
    btVector3 offset = btVector3(btScalar(-1), 0, btScalar(-1));
    //btVector3 pivot = pObjA->Get3DBody()->getWorldTransform().getOrigin() + offset;

    GameObject* pObjB = new GameObject(this, "B", posB, vec3(0), vec3(1), m_pResources->GetMesh("DefaultCube"), m_pResources->GetMaterial("Goal"));
    AddGameObject(pObjB);
    AddCurrentSceneObj(pObjB);
    pObjB->CreateBody(m_pResources->GetCollisionShape("DefaultCollisionCube"));//Default static box
    btVector3 pivot = pObjB->Get3DBody()->getWorldTransform().getOrigin();
    // create point to point joints
    /*btPoint2PointConstraint* p2p = new btPoint2PointConstraint(*(pObjA->Get3DBody()), *(pObjB->Get3DBody()), btVector3(0,-1,0), btVector3(0, -1, 0));
    m_pBulletManager->GetBulletWorld()->addConstraint(p2p);*/

    m_pBulletManager->p2pConstraint(pObjA->Get3DBody(), pObjB->Get3DBody(), btVector3(0, -1, 0), btVector3(0, -1, 0));
}


void LightSampleScene::Spawn6FreeJoint(vec3 posA, vec3 posB)
{
    //two game objects for p2p constraint
    GameObject* pObjA = new GameObject(this, "E", posA, vec3(0), vec3(1), m_pResources->GetMesh("DefaultCube"), m_pResources->GetMaterial("Megaman"));
    AddGameObject(pObjA);
    pObjA->CreateBody(m_pResources->GetCollisionShape("DefaultCollisionCube"), 1.0f);//Default dynamic box


    GameObject* pObjB = new GameObject(this, "F", posB, vec3(0), vec3(1), m_pResources->GetMesh("DefaultCube"), m_pResources->GetMaterial("Megaman"));
    AddGameObject(pObjB);
    pObjB->CreateBody(m_pResources->GetCollisionShape("DefaultCollisionCube"));//Default static box
    btVector3 pivot = pObjB->Get3DBody()->getWorldTransform().getOrigin();
    // create joints
    btQuaternion* quat = new btQuaternion(btScalar(0), btScalar(0), btScalar(0));
    btTransform* trans = new btTransform(*quat, pivot);
    m_pBulletManager->dofConstraint(pObjA->Get3DBody(), pObjB->Get3DBody(), *trans, *trans);

    delete quat;
    delete trans;
}