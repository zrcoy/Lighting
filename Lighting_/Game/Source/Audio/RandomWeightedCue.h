#pragma once
#include"SoundCue.h"
class SoundObject;

class RandomWeightedCue : public SoundCue
{
public:
    RandomWeightedCue();
    virtual ~RandomWeightedCue();
    SoundObject* GetWeightedRandomClip();
    int GetTotalWeight();
    void SetWeightArea();
};
