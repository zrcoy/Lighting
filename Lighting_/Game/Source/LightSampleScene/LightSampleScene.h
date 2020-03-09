#pragma once

#include "Game/Scene.h"

class Game;
class GameObject;
class ResourceManager;
class SoundPlayer;
class SoundObject;
class SoundCue;
class TweenObject;

class LightSampleScene : public Scene
{
    const float SCALE_ANI_SPEED_PER_FRAME = 0.9f;

    std::vector<GameObject*> m_vCurrentSceneObjects;
    float m_Amplitude;
    float m_Frequency;
    SoundPlayer* m_pSoundPlayer;
    //SoundObject* m_pPunchSoundOBJ;
    //SoundObject* m_pGotItemSoundOBJ;
    SoundCue* m_pPunchCues;
    SoundCue* m_pShuffleCue;
    SoundCue* m_pBGCue;
    SoundCue* m_pCollectionCue;
    SoundCue* m_pGoalCue;
    SoundCue* m_pJumpCue;
    bool m_IsGreyScale;
    std::vector<TweenObject*> m_pTweens;
    bool m_CanSelect;
    bool m_IsPause;
    vec3 m_TempPos;
    vec3 m_TempRot;
    vec3 m_TempScale;
    bool m_Win;
protected:
public:
    LightSampleScene(Game* pGame, ResourceManager* pResources);
    virtual ~LightSampleScene();

    virtual void LoadContent() override;

    virtual void OnEvent(Event* pEvent) override;
    virtual void Update(float deltaTime) override;
    virtual void Draw() override;
    void SetGreyScale(bool g) { m_IsGreyScale = g; }
    bool GetGreyScale() { return m_IsGreyScale; }
    virtual void Reset() override;
    void SetPause(bool b) { m_IsPause=b; }
    TweenObject* GetTweenByName(std::string name);
    void AddCurrentSceneObj(GameObject* pObj);
    void SpawnHingeJoint(vec3 posA, vec3 posB);
    void SpawnP2PJoint(vec3 posA, vec3 posB);
    void Spawn6FreeJoint(vec3 posA, vec3 posB);
    SoundPlayer* GetSoundPlayer() { return m_pSoundPlayer; }
    void BackToGame();
    void PlayCollectCue();
    void PlayVictoryCue();
};



