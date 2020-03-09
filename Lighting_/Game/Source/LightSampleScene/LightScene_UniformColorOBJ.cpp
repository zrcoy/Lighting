#include "GamePCH.h"

#include "Game/Game.h"
#include "Mesh/Mesh.h"
#include "Game/Scene.h"
#include "GameObjects/GameObject.h"
#include "LightScene_UniformColorOBJ.h"
#include "LightSampleScene/LightSampleScene.h"
#include "Game/ResourceManager.h"

LightScene_UniformColorOBJ::LightScene_UniformColorOBJ(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, Material* pMaterial, bool loop)
    : GameObject(pScene, name, pos, rot, scale, pMesh, pMaterial)
    , m_uColor(vec3(1, 1, 1))
    , m_Amplitude(0)
   
    , m_maxRed(0)
    , m_maxGreen(0)
    , m_maxBlue(0)
    , m_isColorLoop(loop)
    , m_timer(0)
    , m_IsRotator(1)
{
    int randR = rand() % 256;
    int randG = rand() % 256;
    int randB = rand() % 256;
    setMaxColor(randR, randG, randB);
    setFrequency(rand() % 10);
    CreateBody(m_pScene->GetResourceManager()->GetCollisionShape("DefaultCollisionCube"), 1.0f);
    Get3DBody()->setGravity(btVector3(0, 0, 0));
}

LightScene_UniformColorOBJ::~LightScene_UniformColorOBJ()
{
}

void LightScene_UniformColorOBJ::Reset()
{
    GameObject::Reset();
    m_CloseEnough = false;
}

void LightScene_UniformColorOBJ::Update(float deltaTime)
{
    GameObject::Update(deltaTime);

    static bool flag = true;

    float step = 255.0f / (LOOP_COLOR_TIME * (1 / deltaTime));// changing color amount per frame

    if (m_isColorLoop && flag)
    {
        m_timer = LOOP_COLOR_TIME;
        flag = false;
    }
    static int count = 0;
    if (m_isColorLoop)
    {
        if (m_timer > 0)
            m_timer -= deltaTime;
        else
        {
            flag = true;//reset the timer
            count++;//start cycle next color
        }

        
        
        //count = 0
        switch (count%7)
        {
            //red
        case(0):
            CycleColor(m_maxRed,step);
            m_maxBlue = 0;
            m_maxGreen = 0;
            break;

            //green
        case(1):
            CycleColor(m_maxGreen, step);
            m_maxRed = 0;
            m_maxBlue = 0;
            break;

            //blue
        case(2):
            CycleColor(m_maxBlue, step);
            m_maxRed = 0;
            m_maxGreen = 0;
            break;

            //yellow
        case(3):
            CycleColor(m_maxRed, step);
            CycleColor(m_maxGreen, step);
            m_maxBlue = 0;
            break;

            //purple
        case(4):
            CycleColor(m_maxRed, step);
            CycleColor(m_maxBlue, step);
            m_maxGreen = 0;
            break;

            //purple
        case(5):
            CycleColor(m_maxBlue, step);
            CycleColor(m_maxGreen, step);
            m_maxRed = 0;
            break;

        
        default:
            break;
        }
        
        
    }

    //logic for flicker
    m_Amplitude = abs(sinf(GetSystemTimeSinceGameStart() * m_Frequency));
    // logic for color switching
    float colorChangePerSecond = 255.0f / LOOP_COLOR_TIME;
    float colorChangePerFrame = colorChangePerSecond * deltaTime;
    //m_maxRed
    m_uColor = vec3(m_maxRed, m_maxGreen, m_maxBlue) * m_Amplitude / 255.0f;
    

    //Collision
    vec3 dir = m_Position - m_pScene->GetGameObjectByName("LightPlayer")->GetPosition();
    float dist = dir.Length();
    //detect range of teleport
    if (dist <= 3.0f)
    {
        m_CloseEnough = true;
        m_Position = vec3(-10000, -10000, -10000);
        SyncPhysicsBodyToGraphic(m_Position, vec3(0));
        ((LightSampleScene*)m_pScene)->PlayCollectCue();

        //m_pScene->GetGameObjectByName("LightPlayer")->SetScore(m_pScene->GetGameObjectByName("LightPlayer")->GetScore()++);
    }
    else {
        m_CloseEnough = false;
    }

    //rotate
    if (m_IsRotator)
    {

        m_Rotation.x++;
        m_Rotation.y++;
        m_Rotation.z++;
    }

}

void LightScene_UniformColorOBJ::Draw(CameraObject* pCam)
{
    if (m_pMesh != nullptr)
    {
        m_pMesh->SetupAttributes(m_pMaterial);

        // Create world matrix.
        MyMatrix worldMat, rotateMat;
        worldMat.CreateSRT(m_Scale, m_Rotation, m_Position);
        rotateMat.CreateRotation(m_Rotation);

        {
            m_pMesh->SetupUniforms(m_pMaterial, &worldMat, pCam, m_UVScale, m_UVOffset, &rotateMat, m_pScene->m_vLights, m_uColor);
        }

        m_pMesh->Draw(m_pMaterial);
    }


}

void LightScene_UniformColorOBJ::setMaxColor(int MaxR, int MaxG, int MaxB)
{
    m_maxRed = MaxR;
    m_maxGreen = MaxG;
    m_maxBlue = MaxB;
}

void LightScene_UniformColorOBJ::CycleColor(float& color, float step)
{
 
    if (color <= 255)
    {
        color += step;
    } 
    else 
    {
        color -= step;
    }
    
}


