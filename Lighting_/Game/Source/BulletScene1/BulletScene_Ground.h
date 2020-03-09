#pragma once


#include "GameObjects/GameObject.h"

class Mesh;


class BulletScene_Ground : public GameObject
{


protected:

public:
    BulletScene_Ground(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, Material* pMaterial);
    virtual ~BulletScene_Ground();

    virtual void Update(float deltaTime) override;

    virtual void Draw(CameraObject* pCamera) override;

};


