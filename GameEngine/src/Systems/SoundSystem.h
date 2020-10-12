#pragma once
 
#include "entityx/entityx.h"
#include "../Components/Sound.h"
#include <Bass\bass.h>
#include "AudioMixer.h"
#include <Windows.h>

using namespace entityx;

class SoundSystem : public System<SoundSystem> {
    public:
 

        Sound *bgm;
        Sound *sound;
        AudioMixer *audiomix;
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
				//bgm->play();
				sound->play();

                HSTREAM stream = BASS_StreamCreateFile(false, "resource/Lizz Robinett - Hide and Seek.mp3", 0, 0, 0);
                
                BASS_ChannelPlay(stream, true);

				BASS_DX8_DISTORTION distort;
				distort.fGain = -60;
				distort.fEdge = 100;
				distort.fPostEQCenterFrequency = 8000;
				distort.fPostEQBandwidth = 8000;
				distort.fPreLowpassCutoff = 8000;
                
                
                //audiomix->setdistortion(stream);

//                BASS_ChannelSetFX(stream, BASS_FX_DX8_DISTORTION, 1);
		
            //    BASS_ChannelSetAttribute(sound->channel, BASS_ATTRIB_MUSIC_BPM, 255);
			
        }

        bool initSystem() {
            if (!BASS_Init(-1, 44100, 0, NULL, NULL)) {
                std::cout << "There is no device to use" << std::endl;
                return false;
            }
            else{
                return true;
            }
        }

        void cleanup() {
            bgm->cleanUp();
            sound->cleanUp();
            BASS_Free();
        }
};
