#pragma once

#include "entityx/entityx.h"
#include "../Components/Sound.h"
#include <Bass\bass.h>

using namespace entityx;
class SoundSystem : public System<SoundSystem> {
    public:
        Sound *bgm;
        Sound *sound;
        void update(EntityManager& es, EventManager& events, TimeDelta dt) override {
            //update loop
            if (bgm == NULL || sound == NULL) {
                std::cout << "System Init" << std::endl;
                if (initSystem()) {
                    BASS_SetVolume(1);
                    bgm = new Sound("resource/Lizz Robinett - Hide and Seek.mp3", false);
                    bgm->setVolumn(0.1f);
                    sound = new Sound("resource/kick-trimmed.wav", true);
                    sound->setVolumn(1.0f);
                }
            }
            bgm->play();
            sound->play();
        }

        bool initSystem() {
            if (!BASS_Init(-1, 44100, 0, NULL, NULL)) {
                std::cout << "There is no device to use" << std::endl;
                return false;
            }
            else[
                return true;
            ]
        }

        void cleanup() {
            bgm->cleanUp();
            sound->cleanUp();
            BASS_Free();
        }
};