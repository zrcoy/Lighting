#include "GamePCH.h"


#include "BulletManager.h"


#undef new

bool MyContactAddedCallback(btManifoldPoint& cp, const btCollisionObjectWrapper* colObj0Wrap, int partId0, int index0, const btCollisionObjectWrapper* colObj1Wrap, int partId1, int index1) 
{ 
    int bp = 0;
    return false; 
}
void MyContactStartedCallback(btPersistentManifold* const &manifold) 
{
    
    int bp = 0;
}
void MyContactEndedCallback(btPersistentManifold* const &manifold) 
{
    
}


BulletManager::BulletManager()
{
    ///collision configuration contains default setup for memory, collision setup. Advanced users can create their own configuration.
    m_collisionConfiguration = new btDefaultCollisionConfiguration();

    ///use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded)
    m_dispatcher = new btCollisionDispatcher(m_collisionConfiguration);

    ///btDbvtBroadphase is a good general purpose broadphase. You can also try out btAxis3Sweep.
    m_overlappingPairCache = new btDbvtBroadphase();

    ///the default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded)
    m_solver = new btSequentialImpulseConstraintSolver;

    m_dynamicsWorld = new btDiscreteDynamicsWorld(m_dispatcher, m_overlappingPairCache, m_solver, m_collisionConfiguration);

    m_dynamicsWorld->setGravity(btVector3(0, -100, 0));

    // assign them to the global contact hooks
    gContactAddedCallback =MyContactAddedCallback;
    gContactStartedCallback = MyContactStartedCallback;
    gContactEndedCallback = MyContactEndedCallback;
}

BulletManager::~BulletManager()
{
    

    //delete dynamics world
    delete m_dynamicsWorld;

    //delete solver
    delete m_solver;

    //delete broadphase
    delete m_overlappingPairCache;

    //delete dispatcher
    delete m_dispatcher;

    delete m_collisionConfiguration;

}


void BulletManager::Update(float delta)
{
    m_dynamicsWorld->stepSimulation(delta, 10);
    
}


void BulletManager::sliderConstraint(btRigidBody *body, btTransform trans)
{
    btSliderConstraint* slider = new btSliderConstraint(*body, trans, false);
    m_dynamicsWorld->addConstraint(slider);
}

void BulletManager::sliderConstraint(btRigidBody *body1, btRigidBody *body2, btTransform trans1, btTransform trans2)
{
    btSliderConstraint* slider = new btSliderConstraint(*body1, *body2, trans1, trans2, false);
    m_dynamicsWorld->addConstraint(slider);
}

void BulletManager::p2pConstraint(btRigidBody *body, btVector3 trans)
{
    btPoint2PointConstraint* p2p = new btPoint2PointConstraint(*body, trans);
    m_dynamicsWorld->addConstraint(p2p);
}

void BulletManager::p2pConstraint(btRigidBody *body1, btRigidBody *body2, btVector3 trans1, btVector3 trans2)
{
    btPoint2PointConstraint* p2p = new btPoint2PointConstraint(*body1, *body2, trans1, trans2);
    m_dynamicsWorld->addConstraint(p2p);
}

void BulletManager::hingeConstraint(btRigidBody* body, btVector3 pivot, btVector3 axis)
{
    btHingeConstraint* hinge = new btHingeConstraint(*body, pivot, axis, true);
    m_dynamicsWorld->addConstraint(hinge);
}

void BulletManager::hingeConstraint(btRigidBody* body1, btVector3 pivot1, btVector3 axis1, btRigidBody* body2, btVector3 pivot2, btVector3 axis2)
{
    btHingeConstraint* hinge = new btHingeConstraint(*body1, *body2, pivot1, pivot2, axis1, axis2, true);
    //hinge->enableMotor(true);
    //hinge->enableAngularMotor(true, btScalar(7.0f), btScalar(7.0f));
    m_dynamicsWorld->addConstraint(hinge);
}

void BulletManager::dofConstraint(btRigidBody* body, btTransform trans)
{
    btGeneric6DofConstraint* dof = new btGeneric6DofConstraint(*body, trans, false);

    m_dynamicsWorld->addConstraint(dof);
}

void BulletManager::dofConstraint(btRigidBody* body1, btRigidBody* body2, btTransform trans1, btTransform trans2)
{
    btGeneric6DofConstraint* dof = new btGeneric6DofConstraint(*body1, *body2, trans1, trans2, false);
    m_dynamicsWorld->addConstraint(dof);
}