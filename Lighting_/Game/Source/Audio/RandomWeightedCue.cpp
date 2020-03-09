#include "GamePCH.h"

#include "RandomWeightedCue.h"
#include "Audio/SoundObject.h"

RandomWeightedCue::RandomWeightedCue()
{

}


RandomWeightedCue::~RandomWeightedCue()
{

}

SoundObject* RandomWeightedCue::GetWeightedRandomClip()
{
    int total = GetTotalWeight();

    int randArea = rand() % total;
    // logic for which random area are you in 
    for (auto sound : m_pCue)
    {
        if (randArea<=sound->GetWeight())
        {
            //found the random one we need
            return sound;
        }
        randArea -= sound->GetWeight();
    }
    assert(0 > 1);//there's no sound's random weight in the whole random area, which is impossible
    return nullptr;
}

int RandomWeightedCue::GetTotalWeight()
{
    int result = 0;
    for (auto sound : m_pCue)
    {
        result += sound->GetWeight();
    }
    return result;
}


