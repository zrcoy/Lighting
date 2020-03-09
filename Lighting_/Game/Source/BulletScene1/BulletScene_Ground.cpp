#include "GamePCH.h"

#include "Game/Game.h"
#include "Mesh/Mesh.h"
#include "GameObjects/GameObject.h"
#include "BulletScene_Ground.h"


BulletScene_Ground::BulletScene_Ground(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, Material* pMaterial)
    : GameObject(pScene, name, pos, rot, scale, pMesh, pMaterial)

{
}

BulletScene_Ground::~BulletScene_Ground()
{
}

void BulletScene_Ground::Update(float deltaTime)
{
    GameObject::Update(deltaTime);


}

void BulletScene_Ground::Draw(CameraObject* pCam)
{
    GameObject::Draw(pCam);


}
