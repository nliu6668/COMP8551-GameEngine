#pragma once

#include <Bass\bass.h>
#include "../logger.h"
struct Sound {
    Sound(const char* name, bool ifLoop = false) : name(name), ifLoop(ifLoop) {}

    HCHANNEL channel;
    HSAMPLE sample;
    const char* name; //path of the file
    bool ifLoop; //set if loop the sound
    float volume = -1; //volumn of the sound

    void setUpSound() {
        if (ifLoop == true) {
            sample = BASS_SampleLoad(false, name, 0, 0, 1, BASS_SAMPLE_LOOP);
        }
        else {
            sample = BASS_SampleLoad(false, name, 0, 0, 1, BASS_SAMPLE_MONO);
        }
        channel = BASS_SampleGetChannel(sample, FALSE);
        BASS_ChannelGetAttribute(channel, BASS_ATTRIB_VOL, &volume);
    }

    void play() {
        if (!BASS_ChannelPlay(channel, FALSE)) {
            Logger::getInstance() << "Play error: " << BASS_ErrorGetCode() << " \n\r";
        }
    }

    void pause() {
        if (!BASS_ChannelPause(channel)) {
            Logger::getInstance() << "Play error: " << BASS_ErrorGetCode() << " \n\r";
        }
    }

    void stop() {
        if (!BASS_ChannelStop(channel)) {
            Logger::getInstance() << "Play error: " << BASS_ErrorGetCode() << " \n\r";
        }
    }

    void setIfLoop(bool loop) {
        ifLoop = loop;
        if (ifLoop == true) {
            sample = BASS_SampleLoad(false, name, 0, 0, 1, BASS_SAMPLE_LOOP);
        }
        else {
            sample = BASS_SampleLoad(false, name, 0, 0, 1, BASS_SAMPLE_MONO);
        }
        channel = BASS_SampleGetChannel(sample, FALSE);
    }

    void setVolumn(float vol) {
        volume = vol;
        BASS_ChannelSetAttribute(channel, BASS_ATTRIB_VOL, volume);
    }

    void cleanUp() {
        BASS_SampleFree(sample);
        delete name;
    }
};