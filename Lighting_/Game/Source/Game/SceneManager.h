#pragma once
class Scene;

class SceneManager
{
protected:
    std::map<std::string, Scene*> m_pScenes;
    std::vector<Scene*> m_pActiveScenes;

public:
    SceneManager();
    virtual ~SceneManager();

    void AddScene(std::string name, Scene* pScene);

    Scene* GetScene(const std::string name) { return m_pScenes[name]; }

    Scene* GetMostActiveScene() { return m_pActiveScenes.back(); }

    Scene* PushToActiveScenes(std::string name);

    int GetSizeOfActiveScenes() { return m_pActiveScenes.size(); }

    std::string GetActiveSceneName(Scene* pScene);

    void PopScene();
    void PopAllScenes();
    void LoadContent();
    void OnEvent(Event* pEvent);
    void Update(float deltaTime);
    void Draw();
};