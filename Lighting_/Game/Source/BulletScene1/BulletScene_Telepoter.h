#pragma once


#include "GameObjects/GameObject.h"

class Mesh;


class BulletScene_Telepoter : public GameObject
{
    const float ANIMATION_TELEPORT = 3.0f;
    const float ANIMATION_CHANGE_SPRITE = 0.1f;
protected:
    bool m_CloseEnough;
    float m_AnimationCounter;
    float m_ChangeCounter;
    vec3 m_Destnation;
public:
    BulletScene_Telepoter(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, Material* pMaterial);
    virtual ~BulletScene_Telepoter();

    virtual void Update(float deltaTime) override;

    virtual void Draw(CameraObject* pCamera) override;
    void Teleport(float delta);
    void AnimateTeleport(float delta);
    void ChangeSprite(int index);
    void SetDestination(vec3 target);
};


