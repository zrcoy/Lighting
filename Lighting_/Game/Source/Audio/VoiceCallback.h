//
// Copyright (c) 2017-2018 Jimmy Lord http://www.flatheadgames.com
//
// This software is provided 'as-is', without any express or implied warranty.  In no event will the authors be held liable for any damages arising from the use of this software.
// Permission is granted to anyone to use this software for any purpose, including commercial applications, and to alter it and redistribute it freely, subject to the following restrictions:
// 1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.

#ifndef __VoiceCallback_H__
#define __VoiceCallback_H__

#include <xaudio2.h>
#include "WaveLoader.h"
#include "SoundChannel.h"

class VoiceCallback : public IXAudio2VoiceCallback
{
public:
    SoundChannel* m_pChannel;

    VoiceCallback(SoundChannel* pChannel)
    {
        m_pChannel = pChannel;
    }

    virtual ~VoiceCallback() {}

    // Called when the voice has just finished playing a contiguous audio stream.
    void __stdcall OnStreamEnd()
    {
        m_pChannel->SetState( SoundChannel::SoundChannelState_Free );
    }

    // Unused methods are stubs.
    void __stdcall OnVoiceProcessingPassEnd() 
    {
        int bp = 0;
    }
    void __stdcall OnVoiceProcessingPassStart(UINT32 SamplesRequired) 
    {
        int bp = 0;
    }
    void __stdcall OnBufferEnd(void* pBufferContext) 
    {
        int bp = 0;
        m_pChannel->SetIsBufferEndFlag(true);
    }
    void __stdcall OnBufferStart(void* pBufferContext)
    {
        int bp = 0;
        m_pChannel->SetIsBufferEndFlag(false);
    }
    void __stdcall OnLoopEnd(void* pBufferContext) 
    {
        int bp = 0;
    }
    void __stdcall OnVoiceError(void* pBufferContext, HRESULT Error) 
    {
        int bp = 0;
    }
};

#endif //__VoiceCallback_H__
