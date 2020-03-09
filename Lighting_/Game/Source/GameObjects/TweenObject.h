#pragma once

typedef float(*TweenFunction)(float startvalue, float valuerange, double timepassed, double totaltime);

#include <string>

class TweenObject
{
    float* m_ModifyingValue;
    float m_StartValue;
    float m_EndValue;
    double m_TimeElapsed;
    double m_TotalTime;
    TweenFunction m_pTweenFunction;
    std::string m_name;
    bool m_TweenFlag;
    float m_InitStartValue;
    float m_InitEndValue;
    double m_InitTimeElapsed;
    double m_InitTotalTime;
public:
    
    TweenObject();
    ~TweenObject();
    void Init(float start, float end, double timeEplapsed, double time, float* modifyingVal, TweenFunction tweenFunc, std::string name);
    void Update(float delta);
    std::string GetName() { return m_name; }
    void SetTweenFlag(bool b) { m_TweenFlag = b; }
    bool GetTweenFlag() { return m_TweenFlag; }
    void Reset();
};
