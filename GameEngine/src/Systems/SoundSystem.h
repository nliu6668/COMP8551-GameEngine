#pragma once
 
#include "entityx/entityx.h"
#include "../Components/Sound.h"

#include "AudioMixer.h"
#include <Windows.h>
#include "../Components/AudioSource.h"
#include <Bass\bass.h>

using namespace entityx;

class SoundSystem : public System<SoundSystem> {
    public:
 

        Sound *bgm;
        Sound *sound;
        AudioMixer *audiomix;
        void update(EntityManager& es, EventManager& events, TimeDelta dt) override {
            //update loop

            auto entities = es.entities_with_components<AudioSource>();
            if (!initialized) {
                initSystem();
                for (Entity e : entities) {
                    ComponentHandle<AudioSource> handle = e.component<AudioSource>();
                    handle->sound->setUpSound();
                    if (handle->name == "Red Dead Redemption 2 - See the Fire in Your Eyes.mp3") {
                        handle->tag = "bgm";
                    }
                    if (handle->tag == "bgm") {
                        //handle->setVolume(0.2f);
                        Logger::getInstance() << handle->tag << "'s name is " << handle->name << "\t";
                    }
                    handle->sound->play();

                   
                    //change volume
                    //handle->sound->setVolumn(2);
                    //causes echo effect
                    //audiomix->Setecho(handle->sound->sound, true);
                    //audiomix->echoproperties(0, 100, 2000, 2000, TRUE);
             
                    //causes distortion effect
                    //audiomix->Setdistortion(handle->sound->sound, true);
                    //audiomix->distortionproperties(-60, 100, 8000, 8000, 8000);
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
            else {
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
