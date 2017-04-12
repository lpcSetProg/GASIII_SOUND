/*
* Filename:         Audio.cpp
* Project:          PROG2215 - G.A.S. - Assignment - 03 - SET Trek III
* Programmer:       Lev Cocarell
* Date:             2017-13-03
* Description:
* This source file contains the definition for the Audi class object.
* It used to render the audio sound and effects in the game. background bitmap to the screen.
https://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.xaudio2.xaudio2create(v=vs.85).aspx
https://msdn.microsoft.com/en-us/library/windows/desktop/hh405048(v=vs.85).aspx
https://msdn.microsoft.com/en-us/library/windows/desktop/ee415779(v=vs.85).aspx

https://msdn.microsoft.com/en-us/library/windows/desktop/ee415787(v=vs.85).aspx
http://stackoverflow.com/questions/8804880/use-playsound-in-c-opengl-to-play-sound-in-background
*/


#include "Audio.h"
#include <windows.h>


//=============================================================================
// Audio Default Constructor
//=============================================================================
/*
* Default Constructor: Audio
* Description: No immediate value are set in constructor.
*/
Audio::Audio()
{
}



//=============================================================================
// create Audio
//=============================================================================
/*
* Method: createAudio
* Description:
* This method 
* Parameters: N/A
* Returns: N/A http://stackoverflow.com/questions/19895468/background-music-in-c
*/
void Audio::createAudio()
{
	PlaySound("theOcean.wav", NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
	//waveOutSetVolume(NULL, 0);
	//waveOutSetVolume(NULL, 0xFFFF);
}

DWORD Audio::VolumeValue(const int percentage)
{
	// Clamp percentage value
	int p = min(100, max(0, percentage));
	// Calculate scaled value for one channel
	const WORD wVol = static_cast<WORD>(::MulDiv(65535, p, 100));
	// Construct return value for both channels
	const DWORD retVal = ((wVol << 16) | wVol);
	return retVal;
}



//=============================================================================
// Audio Destructor
//=============================================================================
Audio::~Audio()
{
}
