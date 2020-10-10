#pragma once

#include "entityx/entityx.h"
#include "../Components/Sound.h"
#include "../Components/AudioSource.h"
#include <Bass\bass.h>

using namespace entityx;
class SoundSystem : public System<SoundSystem> {
    public:
        Sound *bgm;
        Sound *sound;
        void update(EntityManager& es, EventManager& events, TimeDelta dt) override {
            //update loop
            auto entities = es.entities_with_components<AudioSource>();
            if (!initialized) {
                initSystem();
                for (Entity e : entities) {
                    ComponentHandle<AudioSource> handle = e.component<AudioSource>();
                    handle->sound->setUpSound();
                    if (handle->sound->name == "resource/Lizz Robinett - Hide and Seek.mp3") {
                        handle->setVolume(0.1f);
                    }
                    handle->sound->play();
                }
            }

            for (Entity e : entities) {
                ComponentHandle<AudioSource> handle = e.component<AudioSource>();
                handle->sound->setVolumn(handle->volume);
            }
        }

        void initSystem() {
            if (!BASS_Init(-1, 44100, 0, NULL, NULL)) {
                Logger::getInstance() << "There is no device to use" << "\n\r";
            }
            else{
                initialized = true;
            }
        }

        void cleanup(EntityManager& es) {
            auto entities = es.entities_with_components<AudioSource>();
            for (Entity e : entities) {
                ComponentHandle<AudioSource> handle = e.component<AudioSource>();
                handle->cleanUp();
            }
            BASS_Free();
        }

    private:
        bool initialized = false;
};
