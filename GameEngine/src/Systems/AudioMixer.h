#pragma once
#include "entityx/entityx.h"
#include "../Components/Sound.h"
#include "SoundSystem.h"
#include <Bass\bass.h>

class AudioMixer : public System<AudioMixer> {
public:
    Sound* bgm;
    Sound* sound;

    void adjustvolume(float volume)
    {
        BASS_SetVolume(volume);
    }


};