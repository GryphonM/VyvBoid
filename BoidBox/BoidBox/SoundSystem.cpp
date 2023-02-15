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

FMOD_RESULT result;
FMOD_SYSTEM* soundSystem;
FMOD_BOOL TRUE = 1;
FMOD_BOOL FALSE = 0;

struct Sound
{
    const char* soundPath; // file path
    const char* name;      // sound name to be used a future reference
  //  FMOD_SOUND* fmodSound; // FMOD struct managing FMOD stuff
    FMOD_SOUND* sound;
    FMOD_CHANNEL* channel; // another FMOD struct managing FMOD stuff
};


Sound* SoundCreate(const char* soundName, const char* filePath)
{
    Sound* sound = new Sound;
    if (sound)
    {
        sound->soundPath = filePath;
        sound->name = soundName;
        result = FMOD_System_CreateSound(soundSystem, filePath, FMOD_2D, 0, &sound->sound);
        
        return sound;
    }
    else
        return NULL;
}

// Helper function to check for errors
void ERRCHECK(FMOD_RESULT checkResult)
{
    if (checkResult != FMOD_OK)
    {
        printf("There was an error in the audio system: (%d) %s\n", checkResult, FMOD_ErrorString(checkResult));
    }
}

// Initialize the Audio System
void AudioInit(void)
{
    // Create the FMOD System
    result = FMOD_System_Create(&soundSystem, FMOD_VERSION);
    ERRCHECK(result);

    // Initialize the FMOD System
    result = FMOD_System_Init(soundSystem, 32, FMOD_INIT_NORMAL, 0);
    ERRCHECK(result);

    // Create the sound
    // Note: this should be generalized for multiple sounds 
    ERRCHECK(result);
    
    // Example of loading a sound to be looping
    // result = FMOD_System_CreateSound(soundSystem, sound_name, FMOD_LOOP_NORMAL | FMOD_2D, 0, &sound);
}

// Update the Audio System
// Note: this should be called during every game loop
void AudioUpdate(void)
{
    result = FMOD_System_Update(soundSystem);
    ERRCHECK(result);
}
void SoundCleanup(Sound* sound)
{
    // Release all sounds that have been created
    result = FMOD_Sound_Release(sound->sound);
    ERRCHECK(result);
}
// Cleanup the Audio System
void AudioCleanup(void)
{
    // Close and Release the FMOD system
    result = FMOD_System_Close(soundSystem);
    ERRCHECK(result);
    result = FMOD_System_Release(soundSystem);
    ERRCHECK(result);
}

// Play the loaded sound
void PlaySound(Sound* sound)
{
    // Play the sound
    // Note: this should be generalized for multiple sounds 
    result = FMOD_System_PlaySound(soundSystem, sound->sound, 0, FALSE, &sound->channel);
    ERRCHECK(result);

    printf("Played a sound\n\n");
}
