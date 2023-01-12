//---------------------------------------------------------------------------\\
//
//	file	audio.c
//	author	Justin Chambers, Andy Ellinger
//			Course: GAM100/GAM150
//			Copyright © 2021 DigiPen (USA) Corporation.
//	brief	This is a simple example of how to properly setup and use FMOD
//
//---------------------------------------------------------------------------\\

#pragma warning ( disable : 4201 )

#include "audio.h"
#include "fmod.h"
#include "fmod_errors.h"
#include <stdio.h>		// printf()
#include <stdbool.h>	// FALSE

FMOD_SYSTEM *soundSystem;
FMOD_SOUND *sound;
FMOD_CHANNEL *channel = 0;
FMOD_RESULT result;

// Helper function to check for errors
void ERRCHECK(FMOD_RESULT checkResult)
{
    if (checkResult != FMOD_OK)
    {
        printf("There was an error in the audio system: (%d) %s\n", checkResult, FMOD_ErrorString(result));
    }
}

// Initialize the Audio System
void AudioInit()
{
    // Create and Initialize the FMOD System
    result = FMOD_System_Create(&soundSystem, FMOD_VERSION);
    ERRCHECK(result);

    result = FMOD_System_Init(soundSystem, 32, FMOD_INIT_NORMAL, 0);
    ERRCHECK(result);

    // Create and Play the sound
    // Note: this should be generalized for multiple sounds and
    //       be placed in a function to be used outside of init.
    result = FMOD_System_CreateSound(soundSystem, "sample_beep.wav", FMOD_LOOP_NORMAL | FMOD_2D, 0, &sound);
    ERRCHECK(result);

    result = FMOD_System_PlaySound(soundSystem, sound, 0, false, &channel);
    ERRCHECK(result);
}

// Update the Audio System
// Note: this should be called frequently such as every game loop or
//       every time a user enters a command depending on the engine
void AudioUpdate()
{
    result = FMOD_System_Update(soundSystem);
    ERRCHECK(result);
}

// Cleanup the Audio System
void AudioCleanup()
{
    // Release all sounds that have been created
    result = FMOD_Sound_Release(sound);
    ERRCHECK(result);

    // Close and Release the FMOD system
    result = FMOD_System_Close(soundSystem);
    ERRCHECK(result);
    result = FMOD_System_Release(soundSystem);
    ERRCHECK(result);
}