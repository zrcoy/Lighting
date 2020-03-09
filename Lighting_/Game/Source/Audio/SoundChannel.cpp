//
// Copyright (c) 2017-2018 Jimmy Lord http://www.flatheadgames.com
//
// This software is provided 'as-is', without any express or implied warranty.  In no event will the authors be held liable for any damages arising from the use of this software.
// Permission is granted to anyone to use this software for any purpose, including commercial applications, and to alter it and redistribute it freely, subject to the following restrictions:
// 1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.

#include "GamePCH.h"
#define XAUDIO2_HELPER_FUNCTIONS
#include "SoundChannel.h"
#include "SoundObject.h"
#include "VoiceCallback.h"

SoundChannel::SoundChannel(IXAudio2* pEngine)
{
    m_pSourceVoice = 0;
    m_pVoiceCallback = 0;

    m_CurrentState = SoundChannelState_Free;
    m_TimePlaybackStarted = 0;

    // Hardcoded for now, all wav's must be this format
    WAVEFORMATEX waveformat;
    waveformat.wFormatTag = 1;
    waveformat.nChannels = 1;
    waveformat.nSamplesPerSec = 44100;
    waveformat.nAvgBytesPerSec = 88200;
    waveformat.nBlockAlign = 2;
    waveformat.wBitsPerSample = 16;
    waveformat.cbSize = 0;

    m_pVoiceCallback = new VoiceCallback( this );
    int result = pEngine->CreateSourceVoice( &m_pSourceVoice, &waveformat, 0, XAUDIO2_DEFAULT_FREQ_RATIO, m_pVoiceCallback );

    if( result != S_OK )
    {
        delete m_pVoiceCallback;
        m_pVoiceCallback = 0;
        OutputMessage( "Unable to create source voice\n" );
    }

    m_IsBufferEnd = true;
}

SoundChannel::~SoundChannel()
{
    delete m_pVoiceCallback;
}

void SoundChannel::PlaySound(SoundObject* pSoundObject)
{
    m_CurrentState = SoundChannelState_Playing;

    m_pSourceVoice->Stop();
	m_pSourceVoice->FlushSourceBuffers();
    m_pSourceVoice->Start();
    m_pSourceVoice->SubmitSourceBuffer( pSoundObject->GetXAudioBuffer() );

    m_TimePlaybackStarted = GetSystemTimeSinceGameStart();
}

void SoundChannel::StopSound()
{
    m_CurrentState = SoundChannelState_Free;

    m_pSourceVoice->Stop();
	m_pSourceVoice->FlushSourceBuffers();

    m_TimePlaybackStarted = 0;
}


void SoundChannel::AdjustVolumn(float amplitudeRatio)
{
    //float dbs = XAudio2AmplitudeRatioToDecibels(amplitudeRatio);      //transfer ratio to decibel
    m_pSourceVoice->SetVolume(amplitudeRatio);
}
