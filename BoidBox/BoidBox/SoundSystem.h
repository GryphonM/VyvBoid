//------------------------------------------------------------------------------
//
// File Name:	PlaceBlock.cpp
// Author(s):	Michael Howard (michael.howard)
// Project:		GAM 150 Game Project
// Course:		GAM 150
//
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//
// File Name:	PlaceBlock.h
// Author(s):	Michael Howard (michael.howard)
// Project:		GAM 150 Game Project
// Course:		GAM 150
//
//------------------------------------------------------------------------------
#ifndef SOUNDSYSTEM_H
#define SOUNDSYSTEM_H

typedef struct Sound Sound;

#if 0
typedef struct Sound
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
#endif
Sound* SoundCreate(const char* soundName, const char* filePath);
void AudioInit(Sound* sound);
void AudioUpdate(Sound* sound);
void AudioCleanup(Sound* sound);
void PlaySound(Sound* sound);

#endif