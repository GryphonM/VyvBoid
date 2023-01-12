//---------------------------------------------------------------------------\\
//
//	file	audio.c
//	author	Justin Chambers
//			Course: GAM100/GAM150
//			Copyright © 2021 DigiPen (USA) Corporation.
//	brief	This is a simple example of how to properly setup and use FMOD
//
//---------------------------------------------------------------------------\\

#include <stdio.h>	// printf()
#include <stdlib.h>	// system()
#include "audio.h"


int main(void)
{
	printf("Audio System - Initialize\n\n");
	AudioInit();

	printf("Audio System - Update\n\n");
	AudioUpdate();

	// pause to listen to the beautiful beeps
	system("pause");

	printf("Audio System - Cleanup\n\n");
	AudioCleanup();
}