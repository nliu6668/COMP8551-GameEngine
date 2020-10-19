#pragma once
#include "entityx/entityx.h"
#include "../Components/Sound.h"
#include <Bass\bass.h>

using namespace entityx;

class AudioMixer : public System<AudioMixer> {

public:

	//echo variables
	float echowet = 50;
	float echofeed = 50;
	float echoleft = 500;
	float echoright = 500;
	bool echodelay = false;
	//bool echo_on = false;

	//distortion variables
	float dgain = -18;
	float dedge = 15;
	float dEQcenter = 2400;
	float dEQbandwidth = 2400;
	float dcutoff = 8000;
	//bool distort_on = false;

	//chorus variables
	float cwetdry = 50;
	float cdepth = 10;
	float cfeedback = 25;
	float cfrequency = 10;
	DWORD cwave = 1;
	float cdelay = 16;
	DWORD cphase = BASS_DX8_PHASE_90;
	//bool chorus_on = false;

	//flanger variables
	float fwetdry;
	float fdepth;
	float ffeed;
	float ffrequency;
	DWORD fwave;
	float fdelay;
	DWORD fphase;

	//gargle variables
	DWORD grate;
	DWORD gwaveshape;

	//compress variables
	float comgain;
	float comatk;
	float comrelease;
	float comthreshold;
	float comratio;
	float comdelay;

	//channel volume 0 - 1
    void adjustvolume(int stream, float volume)
    {
		BASS_ChannelSetAttribute(stream, BASS_ATTRIB_VOL, volume);
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
		dgain = gain;
		dedge = edge;
		dEQcenter = EQCenterFrequency;
		dEQbandwidth = EQBandwidth;
		dcutoff = cutoff;
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
		float echowet = wetdrymix;
		float echofeed = feedback;
		float echoleft = leftdelay;
		float echoright = rightdelay;
		bool echodelay = pandelay;

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
		
		cwetdry = wetdrymix;
		cdepth = depth;
		cfeedback = feedback;
		cfrequency = frequency;
		cwave = waveform;
		cdelay = delay;
		cphase = phase;

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

		fwetdry = wetdrymix;
		fdepth = depth;
		ffeed = feedback;
		ffrequency = frequency;
		fwave = waveform;
		fdelay = delay;
		fphase = phase;

	}

	//FLANGER
	void Setgargle(DWORD stream, bool on) {
		if (on == true)
		{
			BASS_ChannelSetFX(stream, BASS_FX_DX8_GARGLE, 1);
		}
		else if (on == false) {
			BASS_ChannelRemoveFX(stream, BASS_FX_DX8_GARGLE);
		}
	}

	void gargleproperties(DWORD rate, DWORD wave)
	{
		grate = rate;
		gwaveshape = wave;
	}

	//Set compression effect
	void Setcompression(DWORD stream, bool on) {
		
		if (on == true)
		{
			BASS_ChannelSetFX(stream, BASS_FX_DX8_COMPRESSOR, 1);
		}
		else if (on == false) {
			BASS_ChannelRemoveFX(stream, BASS_FX_DX8_COMPRESSOR);
		}
	}

	//set compression properties
	void compressionproperties(float gain, float attack, float release, float threshold, float ratio, float delay)
	{
		comgain = gain;
			comatk = attack;
			comrelease = release;
			comthreshold = threshold;
			comratio = ratio;
			comdelay = delay;
	}


};