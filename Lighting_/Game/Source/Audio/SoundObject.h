//
// Copyright (c) 2017-2018 Jimmy Lord http://www.flatheadgames.com
//
// This software is provided 'as-is', without any express or implied warranty.  In no event will the authors be held liable for any damages arising from the use of this software.
// Permission is granted to anyone to use this software for any purpose, including commercial applications, and to alter it and redistribute it freely, subject to the following restrictions:
// 1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.

#ifndef __SoundObject_H__
#define __SoundObject_H__

#include <xaudio2.h>
#include "WaveLoader.h"

class SoundObject
{
protected:
    const char* m_pFileBuffer;
    MyWaveDescriptor m_WaveDesc; // Contains pointer to data buffer loaded from file
    XAUDIO2_BUFFER m_XAudioBuffer;
    int m_Weight;
    //int m_Min, m_Max;
public:
    SoundObject(int weight);
    ~SoundObject();

    void Init(const char* pFileBuffer, MyWaveDescriptor waveDescriptor);

    XAUDIO2_BUFFER* GetXAudioBuffer() { return &m_XAudioBuffer; }
    bool IsValid() { return m_WaveDesc.valid; }
    int GetWeight() { return m_Weight; }
    //void SetMinArea(int min) { m_Min = min; }
    //void SetMaxArea(int max) { m_Max = max; }
    //int GetMinArea() { return m_Min; }
    //int GetMaxArea() { return m_Max; }
    void SetWeight(int w);
};

#endif //__SoundObject_H__
