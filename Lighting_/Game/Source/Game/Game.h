#ifndef __Game_H__
#define __Game_H__

class ImGuiManager;
class ResourceManager;
class Texture;
class Scene;
class Mesh;
class GameObject;
class Player;
class PlayerController;
class FBODefinition;
class SceneManager;

class Game : public GameCore
{
protected:
    ImGuiManager* m_pImGuiManager;

    ResourceManager* m_pResources;
    bool m_ShowImGui;
    /*Scene* m_pActiveScene;
    Scene* m_pLoadedScene1;
    Scene* m_pLoadedLightingScene;*/


    PlayerController* m_pControllers[4];

    FBODefinition* m_pFBO_Scene;

    FBODefinition* m_pFBO_GreyScale;

    SceneManager* m_pSceneManager;
    bool m_CanSelect = true;
public:
    Game(Framework* pFramework);
    virtual ~Game();

    virtual void OnSurfaceChanged(unsigned int width, unsigned int height) override;
    virtual void LoadContent() override;

    virtual void OnEvent(Event* pEvent) override;
    virtual void Update(float deltaTime) override;
    virtual void Draw() override;

    PlayerController* GetController(int index) { return m_pControllers[index]; }

    FBODefinition* GetFBO(){ return m_pFBO_Scene; }

    SceneManager* GetSceneManager() { return m_pSceneManager; }
    bool GetImGuiFlag() { return m_ShowImGui; }
};

#endif //__Game_H__
