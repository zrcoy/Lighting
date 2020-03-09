#pragma once

#include "Game/Scene.h"

class PauseScene :public Scene
{
    //const int ITEMS_NUM = 3;// play, option, quit
protected:
    std::vector<GameObject*> m_pItems;
    int m_SelectedItemIdx;
    bool m_CanSelect;
public:
    PauseScene(Game* pGame, ResourceManager* pResource);
    virtual ~PauseScene();
    virtual void LoadContent() override;
    virtual void OnEvent(Event* pEvent) override;
    virtual void Update(float delta) override;
    virtual void Draw() override;
    virtual void Reset() override;
};
