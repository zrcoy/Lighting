#pragma once

class btDefaultCollisionConfiguration;
class btCollisionDispatcher;
class btBroadphaseInterface;
class btSequentialImpulseConstraintSolver;
class btDiscreteDynamicsWorld;

class BulletManager
{
private:
    btDefaultCollisionConfiguration * m_collisionConfiguration;
    btCollisionDispatcher* m_dispatcher;
    btBroadphaseInterface* m_overlappingPairCache;
    btSequentialImpulseConstraintSolver* m_solver;
    btDiscreteDynamicsWorld* m_dynamicsWorld;



public:
    BulletManager();
    ~BulletManager();

    void Update(float delta);
    //void Draw(Camera* pCamera, Material* pMaterial);

    btDiscreteDynamicsWorld* GetBulletWorld() { return m_dynamicsWorld; }
    void sliderConstraint(btRigidBody *body, btTransform trans);
    void sliderConstraint(btRigidBody *body1, btRigidBody *body2, btTransform trans1, btTransform trans2);
    void p2pConstraint(btRigidBody *body, btVector3 trans);
    void p2pConstraint(btRigidBody *body1, btRigidBody *body2, btVector3 trans1, btVector3 trans2);
    void hingeConstraint(btRigidBody* body, btVector3 pivot, btVector3 axis);
    void hingeConstraint(btRigidBody* body1, btVector3 pivot1, btVector3 axis1, btRigidBody* body2, btVector3 pivot2, btVector3 axis2);
    void dofConstraint(btRigidBody* body, btTransform trans);
    void dofConstraint(btRigidBody* body1, btRigidBody* body2, btTransform trans1, btTransform trans2);
    
};
