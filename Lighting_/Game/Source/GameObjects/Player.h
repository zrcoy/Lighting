#ifndef __Player_H__
#define __Player_H__

#include "GameObjects/GameObject.h"

class Mesh;
class PlayerController;

class Player : public GameObject
{
    const float PLAYER_SPEED = 4.5f;   // Units per second

protected:
    PlayerController* m_pPlayerController;

    float m_Speed;
    float m_TurningSpeed;

public:
    Player(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, Material* pMaterial);
    virtual ~Player();

    virtual void Update(float deltaTime) override;

    void SetPlayerController(PlayerController* controller) { m_pPlayerController = controller; }
    void SetSpeed(float speed) { m_Speed = speed; }
    void SetTurningSpeed(float speed) { m_TurningSpeed = speed; }
};

#endif //__Player_H__
