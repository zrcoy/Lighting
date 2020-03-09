#pragma once

#include "GameObjects/GameObject.h"

class Mesh;
class PlayerController;

class BulletScenePlayer : public GameObject
{

protected:
    PlayerController * m_pPlayerController;

    float m_Speed;
    float m_TurningSpeed;
    int m_Score;
public:
    BulletScenePlayer(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, Material* pMaterial);
    virtual ~BulletScenePlayer();

    virtual void Update(float deltaTime) override;

    void SetPlayerController(PlayerController* controller) { m_pPlayerController = controller; }
    void SetSpeed(float speed) { m_Speed = speed; }
    void SetTurningSpeed(float speed) { m_TurningSpeed = speed; }

};


