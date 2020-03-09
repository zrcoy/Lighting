#include "GamePCH.h"

#include "MyMotionState.h"
#include "GameObjects/GameObject.h"

MyMotionState::MyMotionState(GameObject* pGameObject)
{
    m_pGameObject = pGameObject;
}

MyMotionState::~MyMotionState()
{

}

void MyMotionState::getWorldTransform(btTransform& worldTrans) const
{
    MyMatrix localmat;
    localmat.CreateSRT(vec3(1), m_pGameObject->m_Rotation, m_pGameObject->m_Position);
    worldTrans.setFromOpenGLMatrix(&localmat.m11);
}

void MyMotionState::setWorldTransform(const btTransform& worldTrans)
{
    MyMatrix matBulletGL;
    worldTrans.getOpenGLMatrix(&matBulletGL.m11);

    m_pGameObject->m_Position = matBulletGL.GetTranslation();
    m_pGameObject->m_Rotation = matBulletGL.GetEulerAngles();
}