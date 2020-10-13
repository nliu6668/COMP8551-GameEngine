#pragma once
#include "entityx/entityx.h"
#include "../Components/Sound.h"
#include <Bass\bass.h>



class AudioMixer : public System<AudioMixer> {
public:



	//channel volume 0 - 1
    void adjustvolume(int stream, float volume)
    {
		BASS_ChannelSetAttribute(stream, BASS_ATTRIB_VOL, volume);
    }

	//music speed
	void soundspeed(DWORD stream, float speed) 
	{
		BASS_ChannelSetAttribute(stream, BASS_ATTRIB_MUSIC_SPEED, speed);
	}


	//distortion

	//Set distortion effect
	void Setdistortion(DWORD stream, bool on) {
		if (on == true)
		{
			BASS_ChannelSetFX(stream, BASS_FX_DX8_DISTORTION, 1);
		}
		else if (on == false) {
			BASS_ChannelRemoveFX(stream, BASS_FX_DX8_DISTORTION);
		}
	}

	//set distortion properties
	void distortionproperties(float gain, float edge, float EQCenterFrequency, float EQBandwidth, float cutoff) 
	{
		BASS_DX8_DISTORTION distort;
		distort.fGain = gain;
		distort.fEdge = edge;
		distort.fPostEQCenterFrequency = EQCenterFrequency;
		distort.fPostEQBandwidth = EQBandwidth;
		distort.fPreLowpassCutoff = cutoff;
	}

	//Set echo effect
	void Setecho(DWORD stream, bool on) {
		if (on == true)
		{
			BASS_ChannelSetFX(stream, BASS_FX_DX8_ECHO, 1);
		}
		else if (on == false) {
			BASS_ChannelRemoveFX(stream, BASS_FX_DX8_ECHO);
		}
	}

	void echoproperties(float wetdrymix, float feedback, float leftdelay, float rightdelay, bool pandelay)
	{
		BASS_DX8_ECHO echo;
		echo.fWetDryMix = wetdrymix;
		echo.fFeedback = feedback;
		echo.fLeftDelay = leftdelay;
		echo.fRightDelay = rightdelay;
		echo.lPanDelay = pandelay;
	}

	//chours

	void Setchorus(DWORD stream, bool on) {
		if (on == true)
		{
			BASS_ChannelSetFX(stream, BASS_FX_DX8_CHORUS, 1);
		}
		else if (on == false) {
			BASS_ChannelRemoveFX(stream, BASS_FX_DX8_CHORUS);
		}
	}

	void chorusproperties(float wetdrymix, float depth, float feedback, float frequency, DWORD waveform, float delay, DWORD phase)
	{
		BASS_DX8_CHORUS chorus;
		chorus.fWetDryMix = wetdrymix;
		chorus.fDepth = depth;
		chorus.fFeedback = feedback;
		chorus.fFrequency = frequency;
		chorus.lWaveform = waveform;
		chorus.fDelay = delay;
		chorus.lPhase = phase;
	}

	//FLANGER
	void Setflanger(DWORD stream, bool on) {
		if (on == true)
		{
			BASS_ChannelSetFX(stream, BASS_FX_DX8_FLANGER, 1);
		}
		else if (on == false) {
			BASS_ChannelRemoveFX(stream, BASS_FX_DX8_FLANGER);
		}
	}

	void flangerproperties(float wetdrymix, float depth, float feedback, float frequency, DWORD waveform, float delay, DWORD phase)
	{
		BASS_DX8_FLANGER flanger;
		flanger.fWetDryMix = wetdrymix;
		flanger.fDepth = depth;
		flanger.fFeedback = feedback;
		flanger.fFrequency = frequency;
		flanger.lWaveform = waveform;
		flanger.fDelay = delay;
		flanger.lPhase = phase;
	}

};