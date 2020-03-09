//
// Copyright (c) 2017-2018 Jimmy Lord http://www.flatheadgames.com
//
// This software is provided 'as-is', without any express or implied warranty.  In no event will the authors be held liable for any damages arising from the use of this software.
// Permission is granted to anyone to use this software for any purpose, including commercial applications, and to alter it and redistribute it freely, subject to the following restrictions:
// 1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.

#include "GamePCH.h"
#include <tuple>

#include "SoundPlayer.h"
#include "SoundChannel.h"
#include "SoundObject.h"
#include "SoundCue.h"
#include "Audio/RandomWeightedCue.h"
#include "Audio/ShuffleAudioCue.h"

//====================================================================================================
// SoundPlayer
//====================================================================================================
SoundPlayer::SoundPlayer()
{
    CoInitializeEx(NULL, COINIT_MULTITHREADED);

    HRESULT result = XAudio2Create(&m_pEngine);

    if (result == S_OK)
    {
        result = m_pEngine->CreateMasteringVoice(&m_pMasteringVoice);

    }

    if (result != S_OK)
    {
        OutputMessage("Error initializing XAudio\n");
        exit(1);
    }


    for (int i = 0; i < MAX_CHANNELS; i++)
    {
        m_vChannels.push_back(new SoundChannel(m_pEngine));
    }

    
}

SoundPlayer::~SoundPlayer()
{
    //delete m_pSound;

    for (auto pChannel : m_vChannels)
    {
        delete pChannel;
    }
    m_vChannels.clear();

    m_pEngine->Release();
    CoUninitialize();
}

SoundObject* SoundPlayer::LoadSound(const char* fullpath,SoundObject* pSound)
{
    //SoundObject* pSound = new SoundObject(weight);
    

    long len;
    const char* fileBuffer = LoadCompleteFile(fullpath, &len);
    assert(fileBuffer);
    if (fileBuffer)
    {
        MyWaveDescriptor waveDescriptor = WaveLoader::ParseWaveBuffer(fileBuffer, len);

        if (waveDescriptor.valid == false)
        {
            OutputMessage("WAV file parsing failed (%s)\n", fullpath);
            delete[] fileBuffer;
        }
        else
        {
            pSound->Init(fileBuffer, waveDescriptor);
        }
    }
    //omg, stupid me
    //delete[] fileBuffer;
    return pSound;
}

SoundChannel* SoundPlayer::FindValidChannel()
{
    for (int i = 0; i < MAX_CHANNELS; i++)
    {
        if (m_vChannels[i]->IsBufferEnd() == true && m_vChannels[i]->GetState() == SoundChannel::SoundChannelState_Free && i!=0)//[0]channel is for BG
        {
            return m_vChannels[i];
        }
    }
    return nullptr;
}



int SoundPlayer::PlaySound(SoundObject* pSoundObject)
{
    if (pSoundObject->IsValid() == false)
        return -1; // Sound didn't play.

    //make sure there's empty channel to play with, if isn't , cut off the olddest channel which is the first channel
    CutOff();

    //find empty channel
    if (FindValidChannel() != nullptr)
        FindValidChannel()->PlaySound(pSoundObject);




    return 0;
}

//void SoundPlayer::PlayCue(SoundCue* cue)
//{
//    //make sure there's empty channel to play with, if isn't , cut off the olddest channel which is the first channel
//    CutOff();
//
//    //find empty channel
//    if (FindValidChannel() != nullptr)
//        FindValidChannel()->PlaySound(cue->GetLastClipInCue());
//
//    
//
//}


void SoundPlayer::StopSound(int channelIndex)
{
    m_vChannels[channelIndex]->StopSound();
    m_vChannels[channelIndex]->SetIsBufferEndFlag(true);
}


SoundChannel* SoundPlayer::GetChannel(int index)
{
    return m_vChannels[index];

}

int SoundPlayer::CountChannelsPlayingSound()
{
    int result = 0;
    for (auto channel : m_vChannels)
    {
        if (channel->GetState() == SoundChannel::SoundChannelState_Playing)
            result++;
    }
    return result;
}

void SoundPlayer::CutOff()
{
    if (CountChannelsPlayingSound() >= MAX_CHANNELS)
    {
        //[0]is bg music and not stop always, so cut off the second one
        m_vChannels[1]->StopSound();
        m_vChannels[1]->SetIsBufferEndFlag(true);
    }
        
    
}

void SoundPlayer::StopAllSound()
{
    for (auto channel : m_vChannels)
    {
        channel->StopSound();
    }
}


void SoundPlayer::PlayBGCue(SoundCue* cue)
{
    //stick the bg music on and always on the first channel
    m_vChannels[0]->PlaySound(cue->GetRandomClipInCue());
}


void SoundPlayer::PlayWeightedRandomCue(RandomWeightedCue* cue)
{
    //make sure there's empty channel to play with, if isn't , cut off the olddest channel which is the first channel
    CutOff();

    
    //find empty channel
    if (FindValidChannel() != nullptr)
        FindValidChannel()->PlaySound(cue->GetWeightedRandomClip());
}


void SoundPlayer::PlayShuffleCue(ShuffleAudioCue* cue)
{
    //make sure there's empty channel to play with, if isn't , cut off the olddest channel which is the first channel
    CutOff();

    //find empty channel
    /*if (FindValidChannel() != nullptr)
        FindValidChannel()->PlaySound(cue->PlayClipsSequencially(this));*/
}


void SoundPlayer::AdjustVolumn(float ratio, int channelIdx)
{
    m_vChannels[channelIdx]->AdjustVolumn(ratio);
}
