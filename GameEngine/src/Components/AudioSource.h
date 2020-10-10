#pragma once

#include <Bass\bass.h>
#include "Sound.h"

struct AudioSource {
	AudioSource(Sound* sound) : sound(sound) {}

	Sound* sound;
	float volume = 1;

	void setVolume(float vol) {
		volume = vol;
	}

	void cleanUp() {
		sound->cleanUp();
		delete sound;
	}
};