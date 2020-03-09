#pragma once



class GameObject;
 
class MyMotionState : public btMotionState
{
    GameObject* m_pGameObject;
public:
    MyMotionState(GameObject* pGameObject);
    virtual ~MyMotionState();

    virtual void getWorldTransform(btTransform& worldTrans) const override;
    virtual void setWorldTransform(const btTransform& worldTrans) override;
};
