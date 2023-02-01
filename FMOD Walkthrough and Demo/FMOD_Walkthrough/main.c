//---------------------------------------------------------------------------\\
//
//	file	audio.c
//	author	Justin Chambers, Andy Ellinger
//			Course: GAM100/GAM150
//			Copyright © 2023 DigiPen (USA) Corporation.
//	brief	This is a simple example of how to properly setup and use FMOD
//
//---------------------------------------------------------------------------\\

#include <stdio.h>	// printf()
#include <conio.h>	// kbhit()
#include "audio.h"


int main(void)
{
	// Initialize FMOD
	printf("Audio System - Initialize\n\n");
	AudioInit();

	printf("Enter P to play a single sound or X to exit\n\n");

	int running = 1;
	while (running)
	{
		// Update FMOD
		AudioUpdate();

		// Check if there is input
		if (_kbhit())
		{
			// Get the character
			char input = getchar();

			// Check for things we need to do
			if (input == 'x')
				running = 0;
			else if (input == 'p')
				PlaySound();
		}
	}

	// Shut down FMOD
	printf("Audio System - Cleanup\n\n");
	AudioCleanup();
}