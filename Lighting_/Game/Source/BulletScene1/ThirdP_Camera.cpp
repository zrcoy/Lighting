#include "GamePCH.h"

#include "ThirdP_Camera.h"
#include "GameObjects/CameraObject.h"
#include "Game/Game.h"
#include "Game/Scene.h"

ThirdP_Camera::ThirdP_Camera(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale)
    : CameraObject(pScene, name, pos, rot, scale)
{
    m_ObjectFollowing = nullptr;
    m_Distance = 0;

    m_MouseLocked = false;
    m_MouseChangeSinceLastFrame.Set(0, 0);
    m_LastMousePosition.Set(0, 0);
}

ThirdP_Camera::~ThirdP_Camera()
{
}

void ThirdP_Camera::OnEvent(Event* pEvent)
{
    if (pEvent->GetEventType() == EventType_Input)
    {
#if WIN32
        InputEvent* pInput = static_cast<InputEvent*>(pEvent);

        if (pInput->GetInputDeviceType() == InputDeviceType_Keyboard)
        {
            int keyID = pInput->GetID();

            if (pInput->GetInputState() == InputState_Pressed)
            {
                if (keyID == 'C')
                {
                    if (m_MouseLocked)
                    {
                        m_MouseLocked = false;
                        m_MouseChangeSinceLastFrame.Set(0, 0);
                        m_LastMousePosition.Set(300, 300);
                    }
                    else
                    {
                        m_MouseLocked = true;
                        m_LastMousePosition.Set(300, 300);

                        SetCursorPos((int)m_LastMousePosition.x, (int)m_LastMousePosition.y);
                    }
                }
            }
        }

        if (pInput->GetInputDeviceType() == InputDeviceType_Mouse)
        {
            if (m_MouseLocked)
            {
                m_MouseLocked = true;
                m_MouseChangeSinceLastFrame = m_LastMousePosition - pInput->GetPosition();
                m_Rotation.x += m_MouseChangeSinceLastFrame.y;
                m_Rotation.y += m_MouseChangeSinceLastFrame.x;

                m_LastMousePosition.Set(300, 300);
                m_pScene->GetGame()->GetFramework()->SetMousePosition(ivec2((int)m_LastMousePosition.x, (int)m_LastMousePosition.y));
                //m_pScene->GetGame()->GetFramework()->SetMousePosition(ivec2(0, 0));

            }
        }
#endif
    }
}

void ThirdP_Camera::Update(float deltaTime)
{
    CameraObject::Update(deltaTime);

    //// Holding F or G will show a top-down view of the planets.
    //if (m_pScene->GetGame()->GetFramework()->IsKeyDown('F') ||
    //    m_pScene->GetGame()->GetFramework()->IsKeyDown('G'))
    //{
    //    vec3 cameraPos = m_pScene->GetGameObjectByName("Sun")->GetPosition() + vec3(0, 30, 0);

    //    m_ViewMatrix.CreateSRT(vec3(1, 1, 1), vec3(-90, 0, 0), cameraPos);
    //    m_ViewMatrix.Inverse();
    //    return;
    //}

    static float speed = 100;//every seconds increase how many degree
    static float angle = 0;

    if (m_ObjectFollowing == 0)
    {
        m_ViewMatrix.CreateSRT(m_Scale, m_Rotation, m_Position);
        m_ViewMatrix.Inverse();
    }
    else
    {

        //TODO_GnomeScene6a: Make the 3rd person camera follow the player from the desired distance.
        //       Use IsKeyDown('I'), J, K and L to rotate the camera.
        //       The camera should be looking at the player.
        //       The player should move relative to the camera.




        if (m_pScene->GetGame()->GetFramework()->IsKeyDown('I'))
        {
            /*angle += deltaTime * speed;
            m_Position.z = sin(m_Distance);
            int bp = 1;*/

            m_Rotation.x += -speed * deltaTime;


        }

        if (m_pScene->GetGame()->GetFramework()->IsKeyDown('K'))
        {
            m_Rotation.x += speed * deltaTime;
        }

        if (m_pScene->GetGame()->GetFramework()->IsKeyDown('J'))
        {
            m_Rotation.y += speed * deltaTime;
        }


        if (m_pScene->GetGame()->GetFramework()->IsKeyDown('L'))
        {
            m_Rotation.y += -speed * deltaTime;
        }




        if (m_pScene->GetGame()->GetFramework()->IsKeyDown('U'))
            m_Distance -= 10 * deltaTime;
        if (m_pScene->GetGame()->GetFramework()->IsKeyDown('M'))
            m_Distance += 10 * deltaTime;

        MyClamp(m_Distance, 0.1f, 20.0f);
        MyClamp(m_Rotation.x, -89.9f, 89.9f);

        vec3 followedObjectPosition = m_ObjectFollowing->GetPosition() + vec3(0, 1, 0);

        m_ViewMatrix.SetIdentity();
        m_ViewMatrix.Translate(0, 0, -m_Distance);
        m_ViewMatrix.Rotate(m_Rotation.x, 1, 0, 0);
        m_ViewMatrix.Rotate(m_Rotation.y, 0, 1, 0);
        m_ViewMatrix.Translate(followedObjectPosition);
        m_Position.Set(m_ViewMatrix.m41, m_ViewMatrix.m42, m_ViewMatrix.m43);
        m_ViewMatrix.Inverse();
        //float sx = sin( m_Rotation.x / 180 * PI );//0
        //float sy = sin( m_Rotation.y / 180 * PI );//0
        //float cx = cos( m_Rotation.x / 180 * PI );//1
        //float cy = cos( m_Rotation.y / 180 * PI );//1

        //m_Position = followedObjectPosition + vec3( cx * sy * m_Distance, -sx * m_Distance, -1 * cx * cy * m_Distance );
        //m_ViewMatrix.CreateLookAtView( m_Position, vec3(0,1,0), followedObjectPosition );
    }
}
