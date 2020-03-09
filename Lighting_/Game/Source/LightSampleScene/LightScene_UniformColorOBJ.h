#pragma once



#include "GameObjects/GameObject.h"

class Mesh;


class LightScene_UniformColorOBJ : public GameObject
{
    const float LOOP_COLOR_TIME = 5.0f;

    vec3 m_uColor;
    float m_Amplitude;
    float m_Frequency;
    float m_maxRed, m_maxGreen, m_maxBlue;
    bool m_isColorLoop;
    float m_timer;
    bool m_CloseEnough = false;
    bool m_IsRotator;
protected:

public:
    LightScene_UniformColorOBJ(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, Material* pMaterial, bool loop=false);
    virtual ~LightScene_UniformColorOBJ();

    virtual void Update(float deltaTime) override;

    virtual void Draw(CameraObject* pCamera) override;
    virtual void Reset() override;
    void setUniformColor(vec3 color) { m_uColor = color; }
    void setAmplitude(float amp) { m_Amplitude = amp; }
    void setFrequency(float freq) { m_Frequency = freq; }
    void setMaxColor(int MaxR, int MaxG, int MaxB);
    void CycleColor(float& colorCounter, float step);
    void IsRotator(bool b) { m_IsRotator = b; }
};


