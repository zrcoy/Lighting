#pragma once
#include "GamePCH.h"

class LightInfo
{
public:
    vec3 m_Pos;
    float m_Range;
    float m_InitialRange;
    std::string m_Name;
    int m_TurnOn;
    vec3 m_Color;



    LightInfo(){
        m_Pos = vec3(0);
        m_Range = 0; 
        m_Name = "None";
        m_TurnOn = 0;
        m_InitialRange = m_Range;
        m_Color = vec3(0, 0, 0);
    }

    LightInfo(vec3 pos , float range, std::string name , int turnOn,vec3 color=vec3(0,0,0))
    {
        m_Pos = pos;
        m_Range = range;
        m_Name = name;
        m_TurnOn = turnOn;
        m_InitialRange = range;
        m_Color = color;
    }
};
