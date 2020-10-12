#pragma once
#include "entityx/entityx.h"
#include "../Components/Sound.h"
#include "SoundSystem.h"
#include <Bass\bass.h>

class AudioMixer : public System<AudioMixer> {
public:
    Sound* bgm;
    Sound* sound;

	void update() {
		BASS_DX8_DISTORTION distort;
		distort.fGain = -18;
		distort.fEdge = 15;
		distort.fPostEQCenterFrequency = 2400;
		distort.fPostEQBandwidth = 2400;
		distort.fPreLowpassCutoff = 8000;
	}
	//channel volume 0 - 1
    void adjustvolume(int stream, float volume)
    {
		BASS_ChannelSetAttribute(stream, BASS_ATTRIB_VOL, volume);
    }

	//channel freq   100 min - 0 normal - 100000 max 
	void adjustfreq(int stream, float freq)
	{
		BASS_ChannelSetAttribute(stream, BASS_ATTRIB_FREQ, freq);
	}

	//distortion

	//Set distortion effect
	void setdistortion(DWORD handle) {
		BASS_ChannelSetFX(handle, BASS_FX_DX8_DISTORTION, 1);
	}

	//set distortion properties
	void distortionproperties() 
	{
		BASS_DX8_DISTORTION distort;
		distort.fGain = -18;
		distort.fEdge = 15;
		distort.fPostEQCenterFrequency = 2400;
		distort.fPostEQBandwidth = 2400;
		distort.fPreLowpassCutoff = 8000;
	}


};