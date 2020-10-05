#pragma once

#include <Bass\bass.h>
struct Sound {
    Sound(const char* name, bool ifLoop = false) : name(name), ifLoop(ifLoop) {
        if (ifLoop == true) {
            sample = BASS_SampleLoad(false, name, 0, 0, 1, BASS_SAMPLE_LOOP);
        }
        else {
            sample = BASS_SampleLoad(false, name, 0, 0, 1, BASS_SAMPLE_MONO);
        }
        channel = BASS_SampleGetChannel(sample, FALSE);
        BASS_ChannelGetAttribute(channel, BASS_ATTRIB_VOL, &volume);
    }

    HCHANNEL channel;
    HSAMPLE sample;
    const char* name; //path of the file
    bool ifLoop; //set if loop the sound
    float volume; //volumn of the sound

    void play() {
        BASS_ChannelPlay(channel, FALSE);
    }

    void pause() {
        BASS_ChannelPause(channel);
    }

    void stop() {
        BASS_ChannelStop(channel);
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

    void setSpeed(float speed) {
        //BASS_ChannelSetAttribute(channel, BASS_ATTRIB_MUSIC_SPEED, speed);
    }

    void cleanUp() {
        BASS_SampleFree(sample);
        delete name;
    }
};