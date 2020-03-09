#include "GamePCH.h"
#include <algorithm>
#include <vector>
#include <random>
#include <chrono>
#include "ShuffleAudioCue.h"
#include "Audio/SoundObject.h"
#include "SoundPlayer.h"
#include "SoundChannel.h"

ShuffleAudioCue::ShuffleAudioCue()
{

}


ShuffleAudioCue::~ShuffleAudioCue()
{

}

void ShuffleAudioCue::Shuffle()
{
    // obtain a time-based seed:
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    shuffle(m_pCue.begin(), m_pCue.end(), std::default_random_engine(seed));
}

void ShuffleAudioCue::PlayClipsSequencially(SoundPlayer* player)
{
    int amountOfSoundPlayed = 0;
    for (int i = 0; i < m_pCue.size(); i++)
    {
        player->FindValidChannel()->PlaySound(m_pCue[i]);
    }
}