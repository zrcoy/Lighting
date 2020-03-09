//
// Copyright (c) 2017-2018 Jimmy Lord http://www.flatheadgames.com
//
// This software is provided 'as-is', without any express or implied warranty.  In no event will the authors be held liable for any damages arising from the use of this software.
// Permission is granted to anyone to use this software for any purpose, including commercial applications, and to alter it and redistribute it freely, subject to the following restrictions:
// 1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.

#include "GamePCH.h"

#include "SoundObject.h"

SoundObject::SoundObject(int weight)
{
    m_pFileBuffer = 0;
    m_WaveDesc.valid = false;
    m_Weight = weight;
    //m_Min = 0;
    //m_Max = 0;
}

SoundObject::~SoundObject()
{
    delete[] m_pFileBuffer;
}

void SoundObject::Init(const char* pFileBuffer, MyWaveDescriptor waveDescriptor)
{
    m_pFileBuffer = pFileBuffer;
    m_WaveDesc = waveDescriptor;

    m_XAudioBuffer.Flags = XAUDIO2_END_OF_STREAM;
    m_XAudioBuffer.AudioBytes = m_WaveDesc.datasize;
    m_XAudioBuffer.pAudioData = (const BYTE*)m_WaveDesc.data;
    m_XAudioBuffer.PlayBegin = 0;
    m_XAudioBuffer.PlayLength = 0;
    m_XAudioBuffer.LoopBegin = 0;
    m_XAudioBuffer.LoopLength = 0;
    m_XAudioBuffer.LoopCount = 0;
    m_XAudioBuffer.pContext = 0;


    //randomize the weight, comment it for testing
    //m_Weight = rand() % 100 + 1;  //each sound weight range from 1 - 100

}

void SoundObject::SetWeight(int w)
{
    m_Weight = w;
}