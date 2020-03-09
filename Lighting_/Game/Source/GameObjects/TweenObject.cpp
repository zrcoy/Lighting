#include "GamePCH.h"
#include "TweenObject.h"

TweenObject::TweenObject() :
    m_StartValue(0)
    , m_EndValue(0)
    , m_TimeElapsed(0)
    , m_TotalTime(0)
    , m_ModifyingValue(0)
    , m_pTweenFunction(nullptr)
    , m_TweenFlag(false)
    , m_InitStartValue(0)
    , m_InitEndValue(0)
    , m_InitTimeElapsed(0)
    , m_InitTotalTime(0)
{

}


TweenObject::~TweenObject()
{

}


void TweenObject::Init(float start, float end, double timeEplapsed, double time, float* modifyingVal, TweenFunction tweenFunc , std::string name)
{
    m_StartValue = start;
    m_InitStartValue = start;
    m_EndValue = end;
    m_InitEndValue = end;
    m_TimeElapsed = timeEplapsed;
    m_InitTimeElapsed = timeEplapsed;
    m_TotalTime = time;
    m_InitTotalTime = time;
    m_ModifyingValue = modifyingVal;
    m_pTweenFunction = tweenFunc;
    m_name = name;
}


void TweenObject::Update(float delta)
{
    if (m_TweenFlag)
    {
        m_TimeElapsed += (double)delta;
        *m_ModifyingValue = m_pTweenFunction(m_StartValue, m_EndValue - m_StartValue, m_TimeElapsed, m_TotalTime);

    }

}

// need to be reset when change type of tween in imgui
void TweenObject::Reset()
{
    m_StartValue = m_InitStartValue;
    m_EndValue = m_InitEndValue;
    m_TimeElapsed = m_InitTimeElapsed;
    m_TotalTime = m_InitTotalTime;
}