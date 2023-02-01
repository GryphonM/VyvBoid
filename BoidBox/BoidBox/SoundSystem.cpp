////!!!!Note!!!! change otherwise this is plagarisng (not my work just yet)
////!!!!Note!!!! i just need to learn the funtions
//
//
//#include "SoundSystem.h"
//#include "fmod.h"
//#include "fmod_errors.h"
//#include <stdio.h>		// printf()
//
//FMOD_SYSTEM* soundSystem;
//FMOD_SOUND* sound;
//FMOD_CHANNEL* channel = 0;
//FMOD_RESULT result;
//
//FMOD_BOOL TRUE = 1;
//FMOD_BOOL FALSE = 0;
//
//// Helper function to check for errors
//void ERRCHECK(FMOD_RESULT checkResult)
//{
//    if (checkResult != FMOD_OK)
//    {
//        printf("There was an error in the audio system: (%d) %s\n", checkResult, FMOD_ErrorString(result));
//    }
//}
//
//// Initialize the Audio System
//void AudioInit(void)
//{
//    // Create the FMOD System
//    result = FMOD_System_Create(&soundSystem, FMOD_VERSION);
//    ERRCHECK(result);
//
//    // Initialize the FMOD System
//    result = FMOD_System_Init(soundSystem, 32, FMOD_INIT_NORMAL, 0);
//    ERRCHECK(result);
//
//    // Create the sound
//    // Note: this should be generalized for multiple sounds 
//    result = FMOD_System_CreateSound(soundSystem, "sample_beep.wav", FMOD_2D, 0, &sound);
//    ERRCHECK(result);
//
//    // Example of loading a sound to be looping
//    // result = FMOD_System_CreateSound(soundSystem, "sample_beep.wav", FMOD_LOOP_NORMAL | FMOD_2D, 0, &sound);
//}
//
//// Update the Audio System
//// Note: this should be called during every game loop
//void AudioUpdate(void)
//{
//    result = FMOD_System_Update(soundSystem);
//    ERRCHECK(result);
//}
//
//// Cleanup the Audio System
//void AudioCleanup(void)
//{
//    // Release all sounds that have been created
//    result = FMOD_Sound_Release(sound);
//    ERRCHECK(result);
//
//    // Close and Release the FMOD system
//    result = FMOD_System_Close(soundSystem);
//    ERRCHECK(result);
//    result = FMOD_System_Release(soundSystem);
//    ERRCHECK(result);
//}
//
//// Play the loaded sound
//void PlaySound(void)
//{
//    // Play the sound
//    // Note: this should be generalized for multiple sounds 
//    result = FMOD_System_PlaySound(soundSystem, sound, 0, FALSE, &channel);
//    ERRCHECK(result);
//
//    printf("Played a sound\n\n");
//}