//------------------------------------------------------------------------------
//
// File Name:	SoundSystem.cpp
// Author(s):	Michael Howard (michael.howard)
// Project:		GAM 150 Game Project
// Course:		GAM 150
//
//------------------------------------------------------------------------------
#include "SoundSystem.h"
#include "fmod.h"
#include "fmod_errors.h"
#include "fmod_common.h"
#include "fmod_dsp.h"
#include "fmod_dsp_effects.h"
#include "fmod_output.h"
#include "fmod_codec.h"
#include <stdio.h>		// printf()

struct Sound
{
    const char* soundPath; // file path
    const char* name;      // sound name to be used a future reference
    FMOD_SOUND* fmodSound; // FMOD struct managing FMOD stuff
    FMOD_CHANNEL* channel = 0; // another FMOD struct managing FMOD stuff
    FMOD_SYSTEM* soundSystem;
    FMOD_SOUND* sound;
    FMOD_RESULT result;

    FMOD_BOOL TRUE = 1;
    FMOD_BOOL FALSE = 0;
};

// Helper function to check for errors
void ERRCHECK(Sound* sound, FMOD_RESULT checkResult)
{
    if (checkResult != FMOD_OK)
    {
        printf("There was an error in the audio system: (%d) %s\n", checkResult, FMOD_ErrorString(sound->result));
    }
}

// Initialize the Audio System
void AudioInit(Sound* sound)
{
    // Create the FMOD System
    sound->result = FMOD_System_Create(&sound->soundSystem, FMOD_VERSION);
    ERRCHECK(sound, sound->result);

    // Initialize the FMOD System
    sound->result = FMOD_System_Init(sound->soundSystem, 32, FMOD_INIT_NORMAL, 0);
    ERRCHECK(sound, sound->result);

    // Create the sound
    // Note: this should be generalized for multiple sounds 
    sound->result = FMOD_System_CreateSound(sound->soundSystem, "sample_beep.wav", FMOD_2D, 0, &sound->sound);
    ERRCHECK(sound, sound->result);

    // Example of loading a sound to be looping
    // result = FMOD_System_CreateSound(soundSystem, "sample_beep.wav", FMOD_LOOP_NORMAL | FMOD_2D, 0, &sound);
}

// Update the Audio System
// Note: this should be called during every game loop
void AudioUpdate(Sound* sound)
{
    sound->result = FMOD_System_Update(sound->soundSystem);
    ERRCHECK(sound, sound->result);
}

// Cleanup the Audio System
void AudioCleanup(Sound* sound)
{
    // Release all sounds that have been created
    sound->result = FMOD_Sound_Release(sound->sound);
    ERRCHECK(sound, sound->result);

    // Close and Release the FMOD system
    sound->result = FMOD_System_Close(sound->soundSystem);
    ERRCHECK(sound, sound->result);
    sound->result = FMOD_System_Release(sound->soundSystem);
    ERRCHECK(sound, sound->result);
}

// Play the loaded sound
void PlaySound(Sound* sound)
{
    // Play the sound
    // Note: this should be generalized for multiple sounds 
    sound->result = FMOD_System_PlaySound(sound->soundSystem, sound->sound, 0, sound->FALSE, &sound->channel);
    ERRCHECK(sound, sound->result);

    printf("Played a sound\n\n");
}
