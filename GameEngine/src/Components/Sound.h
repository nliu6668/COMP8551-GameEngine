#pragma once

#include <Bass\bass.h>
#include "../logger.h"
struct Sound {
    Sound(const char* name, bool ifLoop = false) : name(name), ifLoop(ifLoop) {}

    HSTREAM sound;
    const char* name; //path of the file
    char path[20] = "src/res/sounds/";    //path to store the sound
    bool ifLoop; //set if loop the sound
    bool ifReverb = false; //set if reverb the sound
    float volume = -1; //volumn of the sound

    void setUpSound() {
        char fullpath[100];
        sprintf(fullpath, "%s/%s", path, name);
        if (!(sound = BASS_StreamCreateFile(false, fullpath, 0, 0, BASS_SAMPLE_MONO))) {
            Logger::getInstance() << "Load error: " << BASS_ErrorGetCode() << " \t";
        }
        if (ifLoop == true) {
            setIfLoop(ifLoop);
        }
        BASS_ChannelGetAttribute(sound, BASS_ATTRIB_VOL, &volume);
    }

    void play() {
        if (!BASS_ChannelPlay(sound, FALSE)) {
            Logger::getInstance() << "Play error: " << BASS_ErrorGetCode() << " \t";
        }
    }

    void pause() {
        if (!BASS_ChannelPause(sound)) {
            Logger::getInstance() << "Play error: " << BASS_ErrorGetCode() << " \t";
        }
    }

    void stop() {
        if (!BASS_ChannelStop(sound)) {
            Logger::getInstance() << "Play error: " << BASS_ErrorGetCode() << " \t";
        }
    }

    void setIfLoop(bool loop) {
        ifLoop = loop;
        if (BASS_ChannelFlags(sound, BASS_SAMPLE_LOOP, BASS_SAMPLE_LOOP) == -1) {
            Logger::getInstance() << "Play error: " << BASS_ErrorGetCode() << " \t";
        }
    }

    void setVolumn(float vol) {
        volume = vol;
        BASS_ChannelSetAttribute(sound, BASS_ATTRIB_VOL, volume);
    }

    void cleanUp() {
        BASS_StreamFree(sound);
        delete name;
        free(path);
    }
};