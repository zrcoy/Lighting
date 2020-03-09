#ifndef __GameObject_H__
#define __GameObject_H__

class Game;
class Material;
class Scene;
class Mesh;
class b2Body;
class CameraObject;
class MyMotionState;
class LightInfo;

class GameObject
{
    friend class MyMotionState;
protected:
    std::string m_Name;

    Scene* m_pScene;
    
    float m_Radius;

    Mesh* m_pMesh;
    Material* m_pMaterial;

    vec3 m_InitialPosition;
    vec3 m_InitialRotation;
    vec3 m_InitialScale;
    vec3 m_Position;
    vec3 m_Rotation;
    vec3 m_TempPos;
    vec3 m_TempRot;
    vec3 m_TempScale;

    vec2 m_UVScale;
    vec2 m_UVOffset;

    btRigidBody* m_p3DBody;

    MyMotionState * m_pMotionState;

public:
    vec3 m_Scale;

    GameObject(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, Material* pMaterial);
    virtual ~GameObject();

    virtual void Reset();

    virtual void OnEvent(Event* pEvent);
    virtual void Update(float deltaTime);
    virtual void Draw(CameraObject* pCamera);

    // Getters.
    std::string GetName() { return m_Name; }
    vec3 GetPosition() { return m_Position; }
    vec3 GetRotation() { return m_Rotation; }
    vec3 GetScale() { return m_Scale; }

    // Setters.
    void SetPosition(vec3 pos);
    void SetRotation(vec3 rot);
    void SetScale(vec3 scale);
    void SetUVScaleAndOffset(vec2 uvScale, vec2 uvOffset);
    void SetTempPos(vec3 p) { m_TempPos = p; }
    void SetTempRot(vec3 r) { m_TempRot = r; }
    void SetTempScale(vec3 s) { m_TempScale = s; }
    vec3 GetTempPos() { return m_TempPos; }
    vec3 GetTempRot() { return m_TempRot; }
    vec3 GetTempScale() { return m_TempScale; }


    // Other helpers.
    virtual void ReturnToPool();
    virtual void RemoveFromScene();

    void CreateBody(btCollisionShape* shape, btScalar mass= btScalar(0.0f), btScalar sphereRadius = btScalar(1.f));
    void SyncPhysicsBodyToGraphic(vec3 position, vec3 orientation);
    btRigidBody* Get3DBody() { return m_p3DBody; }
};

#endif //__GameObject_H__
