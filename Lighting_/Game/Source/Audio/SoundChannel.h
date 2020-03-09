//
// Copyright (c) 2017-2018 Jimmy Lord http://www.flatheadgames.com
//
// This software is provided 'as-is', without any express or implied warranty.  In no event will the authors be held liable for any damages arising from the use of this software.
// Permission is granted to anyone to use this software for any purpose, including commercial applications, and to alter it and redistribute it freely, subject to the following restrictions:
// 1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.

#ifndef __SoundChannel_H__
#define __SoundChannel_H__

#include <xaudio2.h>

class SoundObject;
class VoiceCallback;

class SoundChannel
{
public:
    enum SoundChannelStates
    {
        SoundChannelState_Free,
        SoundChannelState_Playing,
        SoundChannelState_Paused,
    };

protected:
    IXAudio2SourceVoice* m_pSourceVoice;
    VoiceCallback* m_pVoiceCallback;

    SoundChannelStates m_CurrentState;
    double m_TimePlaybackStarted;
    bool m_IsBufferEnd;
public:
    SoundChannel(IXAudio2* pEngine);
    ~SoundChannel();

    void PlaySound(SoundObject* pSoundObject);
    void StopSound();

    IXAudio2SourceVoice* GetSourceVoice() { return m_pSourceVoice; }
    void SetSourceVoice(IXAudio2SourceVoice* voice, VoiceCallback* pVoiceCallback) { m_pSourceVoice = voice; m_pVoiceCallback = pVoiceCallback; }

    SoundChannelStates GetState() { return m_CurrentState; }
    void SetState(SoundChannelStates state) { m_CurrentState = state; }

    double GetTimePlaybackStarted() { return m_TimePlaybackStarted; }

    void SetIsBufferEndFlag(bool isEnd) { m_IsBufferEnd = isEnd; }

    bool IsBufferEnd() { return m_IsBufferEnd; };

    void AdjustVolumn(float amplitudeRatio);
};

#endif //__SoundChannel_H__
