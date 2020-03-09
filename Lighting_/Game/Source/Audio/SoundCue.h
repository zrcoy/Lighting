#pragma once
#include <vector>

class SoundObject;

class SoundCue
{
protected:

    std::vector<SoundObject*> m_pCue;
    int currentBGIdx;
public:
    SoundCue();
    virtual ~SoundCue();
    void AddSound(SoundObject* sound);
    SoundObject* GetLastClipInCue() { return m_pCue.back(); }
    SoundObject* GetRandomClipInCue();
    SoundObject* GetCurrentBG() { return m_pCue[currentBGIdx]; }
    
};