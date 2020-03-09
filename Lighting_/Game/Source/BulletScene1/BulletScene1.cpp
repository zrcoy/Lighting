#include "GamePCH.h"

#include "BulletScene1.h"
#include "Game/Game.h"
#include "Game/ResourceManager.h"
#include "Game/Scene.h"
#include "Game/ObjectPool.h"
#include "GameObjects/CameraObject.h"
#include "GameObjects/GameObject.h"
#include "BulletScenePlayer.h"
#include "Physics/BulletManager.h"
#include "BulletScene_Ground.h"
#include "ThirdP_Camera.h"
#include "BulletScene1/BulletScene_Telepoter.h"
#include "Game/SceneManager.h"


BulletScene1::BulletScene1(Game* pGame, ResourceManager* pResources)
    : Scene(pGame, pResources)
{
    m_pBulletManager = nullptr;
}

BulletScene1::~BulletScene1()
{
    delete m_pBulletManager;
}

void BulletScene1::LoadContent()
{
    Scene::LoadContent();


    //Some useful values
    float BulletScene_ground_width = 50.0f;
    float BulletScene_ground_height = 1.0f;
    float BulletScene_ground_length = 20.0f;
    vec3 BulletScene_ground_size = vec3(BulletScene_ground_width, BulletScene_ground_height, BulletScene_ground_length);
    float BulletScene_telepoter_width = 2.0f;
    float BulletScene_telepoter_height = 2.0f;
    float BulletScene_telepoter_length = 2.0f;
    vec3 BulletScene_telepoter_size = vec3(BulletScene_telepoter_width, BulletScene_telepoter_height, BulletScene_telepoter_length);
    float BulletScene_sceneCube_width = 5.0f;
    float BulletScene_sceneCube_height = 5.0f;
    float BulletScene_sceneCube_length = 5.0f;
    vec3 BulletScene_sceneCube_size = vec3(BulletScene_sceneCube_width, BulletScene_sceneCube_height, BulletScene_sceneCube_length);







    //Set the physics world
    m_pBulletManager = new BulletManager();





    // Create our GameObjects.
    {

        //Player
        BulletScenePlayer* pPlayer = new BulletScenePlayer(this, "LightPlayer", vec3(2, 0, -5), vec3(0, 0, 0), vec3(1, 1, 1), m_pResources->GetMesh("DefaultCube"), m_pResources->GetMaterial("Megaman"));
        AddGameObject(pPlayer);
        pPlayer->CreateBody(m_pResources->GetCollisionShape("DefaultCollisionCube"), 1.0f); // create box body with default (1,1,1) scale
        // Assign our controllers.
        pPlayer->SetPlayerController(m_pGame->GetController(0));



        SpawnHingeJoint(vec3(15, -1, 0), vec3(5, -1, 0));

        SpawnP2PJoint(vec3(-8, -1, 0), vec3(-8, 8, 0));

        Spawn6FreeJoint(vec3(-10, 8, 10), vec3(-10, 8, 20));

        //Ground
        BulletScene_Ground* pGround = new BulletScene_Ground(this, "BulletSceneGround", vec3(0, -2, 0), vec3(0, 0, 0), BulletScene_ground_size, m_pResources->GetMesh("DefaultCube"), m_pResources->GetMaterial("Megaman"));
        AddGameObject(pGround);
        pGround->CreateBody(m_pResources->GetCollisionShape("Bullet_GroundCollisionShape"), 0.0f);



        //Third person camera
        ThirdP_Camera* pThirdCam = new ThirdP_Camera(this, "Camera", vec3(0, 0, 0), vec3(0), vec3(1));
        pThirdCam->SetObjectToFollow(pPlayer, 20);
        AddGameObject(pThirdCam);

        //Telepoter
        BulletScene_Telepoter* pTelepoter = new BulletScene_Telepoter(this, "Telepoter", vec3(-3, 0, 0), vec3(0), BulletScene_telepoter_size, m_pResources->GetMesh("Teleporter"), m_pResources->GetMaterial("T1"));
        AddGameObject(pTelepoter);
        //pTelepoter->CreateBody(m_pResources->GetCollisionShape("TelepoterCollisionShape"), 0.0f);



    }


}

void BulletScene1::OnEvent(Event* pEvent)
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
            btVector3 v = this->GetGameObjectByName("C")->Get3DBody()->getLinearVelocity();

            this->GetGameObjectByName("C")->Get3DBody()->applyForce(v * 100, btVector3(0, 0, 0));
        }
        

        if (pInput->GetInputDeviceType() == InputDeviceType_Keyboard && pInput->GetID() == 'P')
        {
            if (pInput->GetInputState() == InputState_Pressed && m_CanSelect)
            {
                m_pGame->GetSceneManager()->PopAllScenes();

                m_pGame->GetSceneManager()->PushToActiveScenes("MainMenuScene");
                m_CanSelect = false;
            }
            else if (pInput->GetInputState() == InputState_Released)
                m_CanSelect = true; // when released, we can select again now
        }


    }

}

void BulletScene1::Update(float deltaTime)
{
    Scene::Update(deltaTime);
    //static bool flag = false;
    this->GetGameObjectByName("C")->Get3DBody()->activate(true);
    //if (flag)
    //{
    //    btVector3 v = this->GetGameObjectByName("C")->Get3DBody()->getLinearVelocity();
    //    v.getX() >= 5.0f ? v.setX(5.0f) : v.setX(v.getX());
    //    v.getZ() >= 5.0f ? v.setX(5.0f) : v.setX(v.getZ());
    //    v.setY(btScalar(0));
    //    this->GetGameObjectByName("C")->Get3DBody()->applyImpulse(v,btVector3(0,0,0));
    //}
    //this->GetGameObjectByName("A")->Get3DBody()->applyTorqueImpulse(btVector3(10, 10, 10));
}

void BulletScene1::Draw()
{
    Scene::Draw();
}

void BulletScene1::SpawnHingeJoint(vec3 posA, vec3 posB)
{
    //two game objects for hinge constraint
    GameObject* pObjC = new GameObject(this, "C", posA, vec3(0), vec3(1), m_pResources->GetMesh("DefaultCube"), m_pResources->GetMaterial("Megaman"));
    AddGameObject(pObjC);
    pObjC->CreateBody(m_pResources->GetCollisionShape("DefaultCollisionCube"), 2.0f);//Default dynamic box
    //pObjC->CreateBody(m_pResources->GetCollisionShape("DefaultCollisionSphere"), 2.0f);//Default dynamic sphere


    GameObject* pObjD = new GameObject(this, "D", posB, vec3(0), vec3(1), m_pResources->GetMesh("DefaultCube"), m_pResources->GetMaterial("Megaman"));
    AddGameObject(pObjD);
    pObjD->CreateBody(m_pResources->GetCollisionShape("DefaultCollisionCube"));//Default static box
    btVector3 commonPivot = pObjD->Get3DBody()->getWorldTransform().getOrigin();
    m_pBulletManager->hingeConstraint(pObjC->Get3DBody(), commonPivot, btVector3(0, 1, 0), pObjD->Get3DBody(), commonPivot, btVector3(0.0f, 1.0f, 0.0f));
}

void BulletScene1::SpawnP2PJoint(vec3 posA, vec3 posB)
{
    //two game objects for p2p constraint
    GameObject* pObjA = new GameObject(this, "A", posA, vec3(0), vec3(1), m_pResources->GetMesh("DefaultCube"), m_pResources->GetMaterial("Megaman"));
    AddGameObject(pObjA);
    pObjA->CreateBody(m_pResources->GetCollisionShape("DefaultCollisionCube"), 1.0f);//Default dynamic box
    btVector3 offset = btVector3(btScalar(-1), 0, btScalar(-1));
    //btVector3 pivot = pObjA->Get3DBody()->getWorldTransform().getOrigin() + offset;

    GameObject* pObjB = new GameObject(this, "B", posB, vec3(0), vec3(1), m_pResources->GetMesh("DefaultCube"), m_pResources->GetMaterial("Megaman"));
    AddGameObject(pObjB);
    pObjB->CreateBody(m_pResources->GetCollisionShape("DefaultCollisionCube"));//Default static box
    btVector3 pivot = pObjB->Get3DBody()->getWorldTransform().getOrigin();
    // create point to point joints
    /*btPoint2PointConstraint* p2p = new btPoint2PointConstraint(*(pObjA->Get3DBody()), *(pObjB->Get3DBody()), btVector3(0,-1,0), btVector3(0, -1, 0));
    m_pBulletManager->GetBulletWorld()->addConstraint(p2p);*/

    m_pBulletManager->p2pConstraint(pObjA->Get3DBody(), pObjB->Get3DBody(), btVector3(0, -1, 0), btVector3(0, -1, 0));
}


void BulletScene1::Spawn6FreeJoint(vec3 posA, vec3 posB)
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

void BulletScene1::Reset()
{
    
}