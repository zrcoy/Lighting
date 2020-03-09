#pragma once
#include"SoundCue.h"
class SoundObject;
class SoundPlayer;

class ShuffleAudioCue : public SoundCue
{
    bool m_ShuffleFlag = false;
public:
    ShuffleAudioCue();
    virtual ~ShuffleAudioCue();
    void Shuffle();
    bool GetShuffleFlag() { return m_ShuffleFlag; }
    void SetShuffleFlag(bool f) { m_ShuffleFlag = f; }
    void PlayClipsSequencially(SoundPlayer* soundPlayer);
};
