// Copyright (c) 2017-2018 Jimmy Lord http://www.flatheadgames.com
//
// This software is provided 'as-is', without any express or implied warranty.  In no event will the authors be held liable for any damages arising from the use of this software.
// Permission is granted to anyone to use this software for any purpose, including commercial applications, and to alter it and redistribute it freely, subject to the following restrictions:
// 1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.

#ifndef __SoundPlayer_H__
#define __SoundPlayer_H__

#include <xaudio2.h>

class SoundObject;
class SoundChannel;
class SoundCue;
class ShuffleAudioCue;
class RandomWeightedCue;

class SoundPlayer
{
   
protected:
    

    IXAudio2* m_pEngine;
    IXAudio2MasteringVoice* m_pMasteringVoice;
    //int m_CurrentNumChannels;

    

    std::vector<SoundChannel*> m_vChannels;

public:
    static const int MAX_CHANNELS = 10;
    SoundPlayer();
    ~SoundPlayer();

    SoundObject* LoadSound(const char* fullpath, SoundObject* pSound);

    int PlaySound(SoundObject* pSoundObject);
    
    void StopSound(int channelIndex);
    SoundChannel* GetChannel(int index);
    int CountChannelsPlayingSound();
    SoundChannel* FindValidChannel();
    void CutOff();
    void PlayBGCue(SoundCue* pBGMusic);
    //void PlayCue(SoundCue* cue);
    void AdjustVolumn(float ratio, int channelIdx);
    void PlayWeightedRandomCue(RandomWeightedCue* cue);
    void PlayShuffleCue(ShuffleAudioCue* cue);
    void StopAllSound();
};

#endif //__SoundPlayerXAudio_H__
