#include "GamePCH.h"

#include "SoundCue.h"
#include "SoundObject.h"


SoundCue::SoundCue()
{
    currentBGIdx = -1;
}


SoundCue::~SoundCue()
{
    for (auto sound : m_pCue)
    {
        delete sound;
    }
    m_pCue.clear();
}



void SoundCue::AddSound(SoundObject* sound)
{
    m_pCue.push_back(sound);
}


SoundObject* SoundCue::GetRandomClipInCue()
{
    int size = m_pCue.size();
    currentBGIdx = rand() % size;
    return m_pCue[currentBGIdx];
}


