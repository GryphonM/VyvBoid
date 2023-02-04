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
#ifndef PLACEBLOCK_H
#define PLACEBLOCK_H

#include "fmod.h"
#include "fmod_errors.h"
#include <stdio.h>		// printf()

typedef struct PlaceBlock PlaceBlock;

#if 0
typedef struct Sound
{
	
};
#endif

void AudioInit(void);
void AudioUpdate(void);
void AudioCleanup(void);
void PlaySound(void);

#endif