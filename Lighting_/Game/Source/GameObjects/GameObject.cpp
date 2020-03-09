#include "GamePCH.h"

#include "Mesh/Material.h"
#include "Mesh/Mesh.h"
#include "GameObjects/CameraObject.h"
#include "GameObjects/GameObject.h"
#include "Game/Scene.h"
#include "Physics/BulletManager.h"
#include "Physics/MyMotionState.h"
#include "Mesh/LightInfo.h"


GameObject::GameObject(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, Material* pMaterial)
    : m_Name(name)
    , m_pScene(pScene)
    , m_pMesh(pMesh)
    , m_pMaterial(pMaterial)
    , m_InitialPosition(pos)
    , m_InitialRotation(rot)
    , m_Position(pos)
    , m_Rotation(rot)
    , m_InitialScale(scale)
    , m_Scale(scale)
    , m_Radius(1.0f)
    , m_p3DBody(nullptr)
    , m_TempPos(0)
    , m_TempRot(0)
    , m_TempScale(0)

{
    m_UVScale.Set(1.0f, 1.0f);
    m_UVOffset.Set(0.0f, 0.0f);

    m_p3DBody = nullptr;
    m_pMotionState = nullptr;

}

GameObject::~GameObject()
{
    delete m_pMotionState;
    delete m_p3DBody;
}

void GameObject::Reset()
{
    m_Position = m_InitialPosition;

    m_Rotation = m_InitialRotation;
    m_Scale = m_InitialScale;
    SyncPhysicsBodyToGraphic(m_Position, m_Rotation);
}

void GameObject::OnEvent(Event* pEvent)
{
}

void GameObject::SyncPhysicsBodyToGraphic(vec3 position, vec3 rotation)
{
    if (m_p3DBody != nullptr)
    {
        //ImGui::Text("initial graphics X : %f, physic X : %f, physic Z : %f,", position.x, position.y, position.z); // print the body's y position
        btTransform initialTransform;

        btVector3 btPosition = btVector3(btScalar(position[0]), btScalar(position[1]), btScalar(position[2]));
        btQuaternion quaternion = btQuaternion(btScalar(rotation.y), btScalar(rotation.x), btScalar(rotation.z));


        initialTransform.setOrigin(btPosition);
        initialTransform.setRotation(quaternion);

        m_p3DBody->setWorldTransform(initialTransform);
        //m_pMotionState->setWorldTransform(initialTransform);


        //ImGui::Text("physic X : %f, physic X : %f, physic Z : %f,", initialTransform.getOrigin().getX(), initialTransform.getOrigin().getY(), initialTransform.getOrigin().getZ()); // print the body's y position
    }

}

void GameObject::Update(float deltaTime)
{


}

void GameObject::Draw(CameraObject* pCamera)
{
    if (m_pMesh != nullptr)
    {
        m_pMesh->SetupAttributes(m_pMaterial);

        // Create world matrix.
        MyMatrix worldMat, rotateMat;
        worldMat.CreateSRT(m_Scale, m_Rotation, m_Position);
        rotateMat.CreateRotation(m_Rotation);


        m_pMesh->SetupUniforms(m_pMaterial, &worldMat, pCamera, m_UVScale, m_UVOffset, &rotateMat, m_pScene->m_vLights);


        m_pMesh->Draw(m_pMaterial);
    }
}

void GameObject::SetPosition(vec3 pos)
{
    m_Position = pos;
}

void GameObject::SetRotation(vec3 rot)
{
    m_Rotation = rot;
}

void GameObject::SetScale(vec3 scale)
{
    m_Scale = scale;
}

void GameObject::SetUVScaleAndOffset(vec2 uvScale, vec2 uvOffset)
{
    m_UVScale = uvScale;
    m_UVOffset = uvOffset;
}

void GameObject::ReturnToPool()
{
}

void GameObject::RemoveFromScene()
{
    m_pScene->RemoveGameObject(this);
}

void GameObject::CreateBody(btCollisionShape* shape, btScalar mass, btScalar sphereRadius)
{
    //create a dynamic rigidbody
#undef new

    btCollisionShape* colShape = shape;
    /*if(isBox)colShape = new btBoxShape(boxSize/2.0f);
    else colShape = new btSphereShape(sphereRadius);*/
    // collisionShapes.push_back(colShape);

     /// Create Dynamic Objects
    btTransform startTransform;
    startTransform.setIdentity();



    //rigidbody is dynamic if and only if mass is non zero, otherwise static
    bool isDynamic = (mass != 0.f);

    btVector3 localInertia(0, 0, 0);
    if (isDynamic)
        colShape->calculateLocalInertia(mass, localInertia);

    //startTransform.setOrigin(btVector3(2, 10, 0));

    //using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
   // btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);

    m_pMotionState = new MyMotionState(this);
    btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, m_pMotionState, colShape, localInertia);
    m_p3DBody = new btRigidBody(rbInfo);

    m_pScene->GetBulletManager()->GetBulletWorld()->addRigidBody(m_p3DBody);



}