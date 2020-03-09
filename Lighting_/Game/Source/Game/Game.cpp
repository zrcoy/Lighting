#include "GamePCH.h"

#include "Events/GameEventTypes.h"
#include "Events/RemoveFromSceneEvent.h"
#include "Game/Game.h"
#include "Game/ImguiManager.h"
#include "Game/ResourceManager.h"
#include "Game/Scene.h"
#include "GameObjects/GameObject.h"
#include "GameObjects/PlayerController.h"
#include "Mesh/Mesh.h"
#include "Mesh/Texture.h"
#include "SceneSample/SceneSample.h"
#include "BulletScene1/BulletScene1.h"
#include "LightSampleScene/LightSampleScene.h"
#include "FBODefinition/FBODefinition.h"
#include "Game/SceneManager.h"
#include "MainMenuScene/MainMenuScene.h"
#include "LevelChoiceScene/LevelChoiceScene.h"
#include "PauseScene/PauseScene.h"
#include "OptionScene/OptionScene.h"

Game::Game(Framework* pFramework)
    : GameCore(pFramework, new EventManager())
{
    m_pImGuiManager = nullptr;

    m_pResources = nullptr;

    for (int i = 0; i < 4; i++)
    {
        m_pControllers[i] = nullptr;
    }

    m_pFBO_Scene = nullptr;
    m_pFBO_GreyScale = nullptr;
    m_ShowImGui = false;
    m_pSceneManager = 0;
}

Game::~Game()
{
    for (int i = 0; i < 4; i++)
    {
        delete m_pControllers[i];
    }
    delete m_pFBO_Scene;
    delete m_pFBO_GreyScale;
    delete m_pResources;
    delete m_pSceneManager;
    delete m_pImGuiManager;


}

void Game::OnSurfaceChanged(unsigned int width, unsigned int height)
{
    // Set OpenGL to draw to the entire window.
    glViewport(0, 0, width, height);
}

void Game::LoadContent()
{
#if WIN32
    // Turn on V-Sync.
    wglSwapInterval(1);
#endif

    // Turn on depth buffer testing.
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    // Turn on alpha blending.
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Enable back-face culling.
    //glEnable( GL_CULL_FACE );
    glCullFace(GL_BACK);
    glFrontFace(GL_CW);

    // Create our resource manager.
    m_pResources = new ResourceManager();

    // Create our meshes.
    {
        m_pResources->AddMesh("Box", new Mesh())->CreateBox(vec2(1, 1), vec2(0, 0));
        m_pResources->AddMesh("DefaultCube", new Mesh())->CreateCube(vec3(1));
        m_pResources->AddMesh("LightCube", new Mesh())->CreateCube(vec3(1));
        m_pResources->AddMesh("Sphere", new Mesh())->CreateOBJ("Data/OBJs/sphere.obj", vec3(1));
        m_pResources->AddMesh("Teleporter", new Mesh())->CreateTeleporter(vec3(1));
    }

    // Create our shaders.
    {
        m_pResources->AddShader("Texture", new ShaderProgram("Data/Shaders/Texture.vert", "Data/Shaders/Texture.frag"));
        m_pResources->AddShader("Lighting", new ShaderProgram("Data/Lighting/Lighting.vert", "Data/Lighting/Lighting.frag"));
        m_pResources->AddShader("UniformColor", new ShaderProgram("Data/Lighting/UniformColor.vert", "Data/Lighting/UniformColor.frag"));
        m_pResources->AddShader("GreyScale", new ShaderProgram("Data/Shaders/GreyScale.vert", "Data/Shaders/GreyScale.frag"));
        m_pResources->AddShader("CubemapShader", new ShaderProgram("Data/Lighting/Cubemap.vert", "Data/Lighting/Cubemap.frag"));
        m_pResources->AddShader("Skybox", new ShaderProgram("Data/Shaders/Skybox.vert", "Data/Shaders/Skybox.frag"));
    }

    // Load some textures.
    {
        m_pResources->AddTexture("Megaman", new Texture("Data/Textures/Megaman.png"));
        m_pResources->AddTexture("Moon", new Texture("Data/Textures/Moon.png"));
        m_pResources->AddTexture("GroundForest", new Texture("Data/Textures/GroundForest.png"));
        m_pResources->AddTexture("T1", new Texture("Data/Textures/t1.png"));
        m_pResources->AddTexture("T2", new Texture("Data/Textures/t2.png"));
        m_pResources->AddTexture("T3", new Texture("Data/Textures/t3.png"));
        m_pResources->AddTexture("T4", new Texture("Data/Textures/t4.png"));
        m_pResources->AddTexture("T5", new Texture("Data/Textures/t5.png"));
        m_pResources->AddTexture("T6", new Texture("Data/Textures/t6.png"));
        m_pResources->AddTexture("T7", new Texture("Data/Textures/t7.png"));
        m_pResources->AddTexture("T8", new Texture("Data/Textures/t8.png"));
        m_pResources->AddTexture("Play_Item", new Texture("Data/Textures/Play_Item.png"));
        m_pResources->AddTexture("HighLight_Item", new Texture("Data/Textures/HighLight.png"));
        m_pResources->AddTexture("Option_Item", new Texture("Data/Textures/Option_Item.png"));
        m_pResources->AddTexture("Quit_Item", new Texture("Data/Textures/Quit_Item.png"));
        m_pResources->AddTexture("BulletScene_Item", new Texture("Data/Textures/BulletTestScene_Item.png"));
        m_pResources->AddTexture("LightScene_Item", new Texture("Data/Textures/LightTestScene_Item.png"));
        m_pResources->AddTexture("Back_Item", new Texture("Data/Textures/Back_Item.png"));
        m_pResources->AddTexture("MainMenu_Item", new Texture("Data/Textures/MainMenu_Item.png"));
        m_pResources->AddTexture("Exit_Item", new Texture("Data/Textures/Exit_Item.png"));
        m_pResources->AddTexture("Volumn_Item", new Texture("Data/Textures/Volumn.png"));
        m_pResources->AddTexture("Brick", new Texture("Data/Textures/brick.png"));
        m_pResources->AddTexture("Num0", new Texture("Data/Textures/Num0.png"));
        m_pResources->AddTexture("Num1", new Texture("Data/Textures/Num1.png"));
        m_pResources->AddTexture("Num2", new Texture("Data/Textures/Num2.png"));
        m_pResources->AddTexture("Num3", new Texture("Data/Textures/Num3.png"));
        m_pResources->AddTexture("Num4", new Texture("Data/Textures/Num4.png"));
        m_pResources->AddTexture("Num5", new Texture("Data/Textures/Num5.png"));
        m_pResources->AddTexture("Num6", new Texture("Data/Textures/Num6.png"));
        m_pResources->AddTexture("Num7", new Texture("Data/Textures/Num7.png"));
        m_pResources->AddTexture("Num8", new Texture("Data/Textures/Num8.png"));
        m_pResources->AddTexture("Num9", new Texture("Data/Textures/Num9.png"));
        m_pResources->AddTexture("Goal", new Texture("Data/Textures/EndGoalGround.png"));


        const char* skyboxFilenames[6] = {
            "Data/Cubemaps/Skybox/PosX.png",
            "Data/Cubemaps/Skybox/NegX.png",
            "Data/Cubemaps/Skybox/PosY.png",
            "Data/Cubemaps/Skybox/NegY.png",
            "Data/Cubemaps/Skybox/PosZ.png",
            "Data/Cubemaps/Skybox/NegZ.png",

        };

        m_pResources->AddTexture("Cubemap", new Texture(skyboxFilenames));
        m_pResources->AddTexture("Skybox", new Texture(skyboxFilenames));
    }

    // Create some materials.
    {
        m_pResources->AddMaterial("Megaman", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("Megaman")));
        m_pResources->AddMaterial("Lighting", new Material(m_pResources->GetShader("Lighting"), nullptr));
        m_pResources->AddMaterial("Moon", new Material(m_pResources->GetShader("Lighting"), m_pResources->GetTexture("Moon")));
        m_pResources->AddMaterial("GroundForest", new Material(m_pResources->GetShader("Lighting"), m_pResources->GetTexture("GroundForest")));
        m_pResources->AddMaterial("UniformColor", new Material(m_pResources->GetShader("UniformColor"), nullptr));//material without texture, color is from uniform passing
        m_pResources->AddMaterial("T1", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("T1")));
        m_pResources->AddMaterial("T2", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("T2")));
        m_pResources->AddMaterial("T3", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("T3")));
        m_pResources->AddMaterial("T4", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("T4")));
        m_pResources->AddMaterial("T5", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("T5")));
        m_pResources->AddMaterial("T6", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("T6")));
        m_pResources->AddMaterial("T7", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("T7")));
        m_pResources->AddMaterial("T8", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("T8")));
        m_pResources->AddMaterial("Play_Item", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("Play_Item")));
        m_pResources->AddMaterial("HighLight_Item", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("HighLight_Item")));
        m_pResources->AddMaterial("Option_Item", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("Option_Item")));
        m_pResources->AddMaterial("Quit_Item", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("Quit_Item")));
        m_pResources->AddMaterial("BulletScene_Item", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("BulletScene_Item")));
        m_pResources->AddMaterial("LightScene_Item", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("LightScene_Item")));
        m_pResources->AddMaterial("Back_Item", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("Back_Item")));
        m_pResources->AddMaterial("MainMenu_Item", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("MainMenu_Item")));
        m_pResources->AddMaterial("Exit_Item", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("Exit_Item")));
        m_pResources->AddMaterial("Volumn_Item", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("Volumn_Item")));
        m_pResources->AddMaterial("Brick", new Material(m_pResources->GetShader("Lighting"), m_pResources->GetTexture("Brick")));
        m_pResources->AddMaterial("Num0", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("Num0")));
        m_pResources->AddMaterial("Num1", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("Num1")));
        m_pResources->AddMaterial("Num2", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("Num2")));
        m_pResources->AddMaterial("Num3", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("Num3")));
        m_pResources->AddMaterial("Num4", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("Num4")));
        m_pResources->AddMaterial("Num5", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("Num5")));
        m_pResources->AddMaterial("Num6", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("Num6")));
        m_pResources->AddMaterial("Num7", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("Num7")));
        m_pResources->AddMaterial("Num8", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("Num8")));
        m_pResources->AddMaterial("Num9", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("Num9")));
        m_pResources->AddMaterial("Goal", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("Goal")));
#
        //create FBO
#undef new
        m_pFBO_Scene = new FBODefinition(GetFramework()->GetWindowWidth(), GetFramework()->GetWindowHeight(), GL_LINEAR, GL_LINEAR, true);
        m_pFBO_GreyScale = new FBODefinition(GetFramework()->GetWindowWidth(), GetFramework()->GetWindowHeight(), GL_LINEAR, GL_LINEAR, true);


        m_pResources->AddMaterial("SceneMaterial", new Material(m_pResources->GetShader("Texture"), new Texture(m_pFBO_Scene->GetColorTextureHandle())));
        m_pResources->AddMaterial("GreyScale", new Material(m_pResources->GetShader("GreyScale"), new Texture(m_pFBO_GreyScale->GetColorTextureHandle())));

        //cubemap material
        m_pResources->AddMaterial("Cubemap", new Material(m_pResources->GetShader("CubemapShader"), m_pResources->GetTexture("Megaman"), m_pResources->GetTexture("Cubemap")));
        //skybox material
        m_pResources->AddMaterial("Skybox", new Material(m_pResources->GetShader("Skybox"), m_pResources->GetTexture("Megaman"), m_pResources->GetTexture("Skybox")));
    }

    // Create some default collision shapes

    {
        //Some useful values
        float LightScene_ground_width = 200.0f;
        float LightScene_ground_height = 1.0f;
        float LightScene_ground_length = 200.0f;
        vec3 LightScene_ground_size = vec3(LightScene_ground_width, LightScene_ground_height, LightScene_ground_length);
        float LightScene_leftWall_width = 1.0f;
        float LightScene_leftWall_height = 30.0f;
        float LightScene_leftWall_length = 100.0f;
        vec3 LightScene_leftWall_size = vec3(LightScene_leftWall_width, LightScene_leftWall_height, LightScene_leftWall_length);
        float LightScene_upWall_width = 100.0f;
        float LightScene_upWall_height = 30.0f;
        float LightScene_upWall_length = 1.0f;
        vec3 LightScene_upWall_size = vec3(LightScene_upWall_width, LightScene_upWall_height, LightScene_upWall_length);
        float LightScene_upWall2_width = 100.0f;
        float LightScene_upWall2_height = 10.0f;
        float LightScene_upWall2_length = 1.0f;
        vec3 LightScene_upWall2_size = vec3(LightScene_upWall2_width, LightScene_upWall2_height, LightScene_upWall2_length);
        float LightScene_sceneCube_width = 10.0f;
        float LightScene_sceneCube_height = 10.0f;
        float LightScene_sceneCube_length = 10.0f;
        vec3 LightScene_sceneCube_size = vec3(LightScene_sceneCube_width, LightScene_sceneCube_height, LightScene_sceneCube_length);
        float BulletScene_ground_width = 50.0f;
        float BulletScene_ground_height = 1.0f;
        float BulletScene_ground_length = 20.0f;
        vec3 BulletScene_ground_size = vec3(BulletScene_ground_width, BulletScene_ground_height, BulletScene_ground_length);
        float BulletScene_telepoter_width = 2.0f;
        float BulletScene_telepoter_height = 2.0f;
        float BulletScene_telepoter_length = 2.0f;
        vec3 BulletScene_telepoter_size = vec3(BulletScene_telepoter_width, BulletScene_telepoter_height, BulletScene_telepoter_length);
        float BulletScene_sceneCube_width = 20.0f;
        float BulletScene_sceneCube_height = 20.0f;
        float BulletScene_sceneCube_length = 20.0f;
        vec3 BulletScene_sceneCube_size = vec3(BulletScene_sceneCube_width, BulletScene_sceneCube_height, BulletScene_sceneCube_length);


#undef new
        btCollisionShape* pDefaultSphere = new btSphereShape(btScalar(1.0f));
        m_pResources->AddCollisionShapes("DefaultCollisionSphere", pDefaultSphere);

        btCollisionShape* pDefaultCone = new btConeShape(btScalar(1.0f), btScalar(1.0f));
        m_pResources->AddCollisionShapes("DefaultCollisionCone", pDefaultCone);

        btCollisionShape* pDefaultBox = new btBoxShape(btVector3(1 / 2.0f, 1 / 2.0f, 1 / 2.0f));
        m_pResources->AddCollisionShapes("DefaultCollisionCube", pDefaultBox);

        // some collision shapes 
        //ground
        m_pResources->AddCollisionShapes("Light_GroundCollisionShape", new btBoxShape(btVector3(LightScene_ground_width / 2.0f, LightScene_ground_height / 2.0f, LightScene_ground_length / 2.0f)));
        //left wall
        m_pResources->AddCollisionShapes("Light_LeftWallCollisionShape", new btBoxShape(btVector3(LightScene_leftWall_width / 2.0f, LightScene_leftWall_height / 2.0f, LightScene_leftWall_length / 2.0f)));
        //Up wall
        m_pResources->AddCollisionShapes("Light_UpWallCollisionShape", new btBoxShape(btVector3(LightScene_upWall_width / 2.0f, LightScene_upWall_height / 2.0f, LightScene_upWall_length / 2.0f)));
        //Up wall
        m_pResources->AddCollisionShapes("Light_UpWall2CollisionShape", new btBoxShape(btVector3(LightScene_upWall2_width / 2.0f, LightScene_upWall2_height / 2.0f, LightScene_upWall2_length / 2.0f)));
        //Up wall5
        m_pResources->AddCollisionShapes("Light_UpWall5CollisionShape", new btBoxShape(btVector3(130.0f/ 2.0f, 15.0f / 2.0f, 1.0f / 2.0f)));
        //Scene Cube
        m_pResources->AddCollisionShapes("Light_SceneCubeCollisionShape", new btBoxShape(btVector3(LightScene_sceneCube_width / 2.0f, LightScene_sceneCube_height / 2.0f, LightScene_sceneCube_length / 2.0f)));
        m_pResources->AddCollisionShapes("Bullet_GroundCollisionShape", new btBoxShape(btVector3(BulletScene_ground_width / 2.0f, BulletScene_ground_height / 2.0f, BulletScene_ground_length / 2.0f)));
        m_pResources->AddCollisionShapes("TelepoterCollisionShape", new btBoxShape(btVector3(BulletScene_telepoter_width / 2.0f, BulletScene_telepoter_height / 2.0f, BulletScene_telepoter_length / 2.0f)));
        m_pResources->AddCollisionShapes("Skybox", new btSphereShape(btScalar(500.0f)));
    }

    // Create our controllers.
    for (int i = 0; i < 4; i++)
    {
        m_pControllers[i] = new PlayerController();
    }


    // Create an ImGui object.
    m_pImGuiManager = new ImGuiManager();
    m_pImGuiManager->Init();

    //Create our scene manager
    m_pSceneManager = new SceneManager();


    //Add Scene
    m_pSceneManager->AddScene("BulletTestScene", new BulletScene1(this, m_pResources));
    m_pSceneManager->AddScene("LightTestScene", new LightSampleScene(this, m_pResources));
    m_pSceneManager->AddScene("MainMenuScene", new MainMenuScene(this, m_pResources));
    m_pSceneManager->AddScene("LevelChoiceScene", new LevelChoiceScene(this, m_pResources));
    m_pSceneManager->AddScene("PauseScene", new PauseScene(this, m_pResources));
    m_pSceneManager->AddScene("OptionScene", new OptionScene(this, m_pResources));
    //Load content in all scene on the stack
    m_pSceneManager->LoadContent();
    //the first scene is main menu scene
    m_pSceneManager->PushToActiveScenes("MainMenuScene");




    CheckForGLErrors();
}

void Game::OnEvent(Event* pEvent)
{
    m_pImGuiManager->OnEvent(pEvent);

    m_pControllers[0]->OnEvent(pEvent);

    if (pEvent->GetEventType() == GameEventType_RemoveFromScene)
    {
        RemoveFromSceneEvent* pRemoveFromSceneEvent = static_cast<RemoveFromSceneEvent*>(pEvent);

        Scene* pScene = pRemoveFromSceneEvent->GetScene();
        GameObject* pGameObject = pRemoveFromSceneEvent->GetGameObject();

        if (pScene->IsGameObjectInScene(pGameObject))
        {
            pGameObject->RemoveFromScene();
        }
    }

    //m_pActiveScene->OnEvent( pEvent );

#if WIN32
    // Enable/Disable V-Sync with F1 and F2.
    if (pEvent->GetEventType() == EventType_Input)
    {
        InputEvent* pInput = static_cast<InputEvent*>(pEvent);

        // Enable V-Sync.
        if (pInput->GetInputDeviceType() == InputDeviceType_Keyboard && pInput->GetID() == VK_F1)
            wglSwapInterval(1);

        // Disable V-Sync.
        if (pInput->GetInputDeviceType() == InputDeviceType_Keyboard && pInput->GetID() == VK_F2)
            wglSwapInterval(0);



        //Escape
        if (pInput->GetInputDeviceType() == InputDeviceType_Keyboard && pInput->GetID() == VK_ESCAPE)
        {
            GetFramework()->SetCloseRequestBool(true);
        }

        m_pSceneManager->OnEvent(pEvent);

        if (pInput->GetInputDeviceType() == InputDeviceType_Keyboard && pInput->GetID() == VK_F9)
        {
            if (pInput->GetInputState() == InputState_Pressed && m_CanSelect)
            {
                static int counter;
                m_ShowImGui = (++counter) % 2 == 0 ? false : true;
                m_CanSelect = false;
            }
           
            else if (pInput->GetInputState() == InputState_Released)
                m_CanSelect = true;
        }
        if (pInput->GetInputDeviceType() == InputDeviceType_Keyboard && pInput->GetID() == 'R')
        {
            if (pInput->GetInputState() == InputState_Pressed && m_CanSelect)
            {
                m_pSceneManager->GetMostActiveScene()->Reset();
            }

            else if (pInput->GetInputState() == InputState_Released)
                m_CanSelect = true;
        }
    }
#endif //WIN32
}

void Game::Update(float deltaTime)
{
    // Once our events are processed, tell ImGui we're starting a new frame.
    m_pImGuiManager->StartFrame((float)m_pFramework->GetWindowWidth(), (float)m_pFramework->GetWindowHeight(), deltaTime);

    //m_pActiveScene->Update( deltaTime );
    m_pSceneManager->Update(deltaTime);
}

void Game::Draw()
{
    // Setup the values we will clear to, then actually clear the color and depth buffers.
    glClearColor(0.0f, 0.0f, 0.4f, 1.0f); // (red, green, blue, alpha) - dark blue.
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

#if WIN32
    glClearDepth(1); // 1 is maximum depth.
#endif



    //FBO Bind
    m_pFBO_GreyScale->Bind();
    glViewport(0, 0, GetFramework()->GetWindowWidth(), GetFramework()->GetWindowHeight());
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    m_pSceneManager->GetMostActiveScene()->Draw();
    m_pFBO_GreyScale->Unbind();

    //draw scenes
    glViewport(0, 0, GetFramework()->GetWindowWidth(), GetFramework()->GetWindowHeight());
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Draw our scene.
    m_pSceneManager->Draw();

    //grey effect
    if (m_pSceneManager->GetActiveSceneName(m_pSceneManager->GetMostActiveScene()) == "LightTestScene")
    {
        if (((LightSampleScene*)m_pSceneManager->GetMostActiveScene())->GetGreyScale())
        {
            Mesh* postEffectmesh = m_pResources->GetMesh("Box");
            postEffectmesh->SetupAttributes(m_pResources->GetMaterial("GreyScale"));
            postEffectmesh->SetupPostEffectUniforms(m_pResources->GetMaterial("GreyScale"));
            postEffectmesh->Draw(m_pResources->GetMaterial("GreyScale"));

        }
    }




    // Tell imgui we're at the end of our frame, so it will draw all queued objects.
    m_pImGuiManager->EndFrame();



    CheckForGLErrors();
}
