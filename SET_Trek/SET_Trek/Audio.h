/*
* Filename:         Audio.h
* Project:          PROG2215 - G.A.S. - Assignment - 03 - SET Trek III
* Programmer:       Lev Cocarell
* Date:             2017-13-03
* Description:
* This source file contains the definition for the Audi class object.
* It used to render the audio sound and effects in the game. background bitmap to the screen.
*/


#pragma once
#include "Grid.h"

class Audio
{
public:

	Audio();

	void createAudio();
	DWORD VolumeValue(const int percentage);


	~Audio();
};

