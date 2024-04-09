#include <stdio.h>
#include "Artist.h"
#include "Controller.h"
#include "Mixer.h"
#include "Mapper.h"
#include "Cards.h"
#include "HUD.h"


int main(int argc, char* args[])
{
	//Declare Artist and controller
	Artist Artist;
	Controller controller;
	Mixer mixer;
	Mapper mapper;
	Cards cards;
	HUD hud;

	//Start up SDL and create window
	if (!Artist.init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		//Load media
		if (!Artist.loadMedia())
		{
			printf("Failed to load media!\n");
		}
		if (!mixer.loadSoundMedia())
		{
			printf("Failed to load media!\n");
		}
		
		
		//loading setting ect
		controller.loadController();
		cards.init();
		mapper.init();
		
		hud.init();


		//While application is running
		while (!Controller::quit)
		{
			//Clear screen
			Artist.clearScreen();


			//Checks for user input
			controller.controller();

			//Updates game world
			mapper.update();

			//Draw everything
			Artist.draw();

			




			//Update screen
			Artist.updateScreen();
		}
		
	}

	//Free resources and close SDL
	Artist.close();

	return 0;
}