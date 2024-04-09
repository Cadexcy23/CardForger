#include "HUD.h"
#include "Artist.h"
#include "Controller.h"
#include "Mapper.h"
#include "Cards.h"



SDL_Texture* resourceBackBack;
SDL_Texture* hotBar;




//TEMP
int HUD::playerEntID = 0; //keeps track of what entity we are controlling
bool (*AIFuncSlot)(int); //slot to hold the old AI of a ent we are overtaking

bool nullFunc(int entID)
{
	return true;
}

HUD::resourceBar HUD::loadResourceBar(int classID, int max, int current)
{
	Artist artist;
	HUD::resourceBar tempBar;

	tempBar.barVisual = artist.loadTexture("Resource/HUD/resourceBar.png");
	tempBar.max = max;
	tempBar.current = current;

	if (classID == -2)//its the health bar
	{
		SDL_SetTextureColorMod(tempBar.barVisual, 179, 54, 54);
		tempBar.icon = artist.loadTexture("Resource/HUD/healthIcon.png");
		tempBar.name = "Health";
	}
	else if (classID == -1)//its the stamina bar
	{
		SDL_SetTextureColorMod(tempBar.barVisual, 194, 177, 48);
		tempBar.icon = artist.loadTexture("Resource/HUD/staminaIcon.png");
		tempBar.name = "stamina";
	}
	else
	{
		SDL_SetTextureColorMod(tempBar.barVisual, Cards::classColors[classID].r, Cards::classColors[classID].g, Cards::classColors[classID].b);
		tempBar.icon = Cards::classResourceIcons[classID];
		tempBar.name = Cards::classResourceNames[classID];
	}

	return tempBar;
}

void drawResourceBar(HUD::resourceBar bar, int x, int y, float scale)//make it center on x and sit on y so it can be scaled and moved
{
	Artist artist;

	int width = 368 * scale;
	int height = 8 * scale;
	int newX = x - width / 2;
	int newY = y - height;


	//draw back plate
	artist.drawImage(resourceBackBack, newX, newY, width, height);
	//draw resource scaled to how much we actauly have
	float currentScale = float(bar.max) / float(bar.current);
	int currentResourceWidth = (368 / currentScale) * scale;
	artist.drawImage(bar.barVisual, newX, newY, currentResourceWidth, height);
	//draw icon
	artist.drawImage(bar.icon, newX, newY, 8 * scale, 8 * scale);

}

void drawAbility(HUD::ability ability, int x, int y, float scale)
{
	Artist artist;

	int width = 64 * scale;
	int height = 64 * scale;
	int newX = x - width / 2;
	int newY = y - height;

	artist.drawImage(ability.icon, newX, newY);
}

void drawHotBar(int x, int y, float scale)//add animations for if it was used, add greying out if unusable, add flipping animation if the ability was swapped (mi9ght need done elsewhere)
{
	Artist artist;

	int width = 368 * scale;
	int height = 80 * scale;
	int newX = x - width / 2;
	int newY = y - height;

	artist.drawImage(hotBar, newX, newY);

	for (int i = 0; i < 5; i++)//only show first 5
	{
		drawAbility(Mapper::activeEntities[HUD::playerEntID].abilities[i], x + 72 * i - 144, y - 8, scale);
		//get name of key
		std::string keyName = SDL_GetScancodeName(Mapper::activeEntities[HUD::playerEntID].abilities[i].keyBind);
		artist.drawLetters(keyName, x + 72 * i - 175, y - 71, Artist::smallFont);
	}
}

void HUD::init()
{
	Artist artist;
	hotBar = artist.loadTexture("Resource/HUD/hotBar.png");
	resourceBackBack = artist.loadTexture("Resource/HUD/resourceBarBack.png");
	AIFuncSlot = nullFunc;
}

void HUD::draw()//need make it auto center on x and on top of y so it can be scaled and moved
{
	Artist artist;
	//draw hot bar
	drawHotBar(960, 1080, 1);//make variabls to we can move it around
	//draw resource bars
	//health
	drawResourceBar(Mapper::activeEntities[playerEntID].health, 960, 1000, 1);//make variabls to we can move it around
	//stamina
	drawResourceBar(Mapper::activeEntities[playerEntID].stamina, 960, 992, 1);//make variabls to we can move it around
	//class resources
	for (int i = 0; i < Mapper::activeEntities[playerEntID].classResources.size(); i++)
	{
		drawResourceBar(Mapper::activeEntities[playerEntID].classResources[i], 960, 984 -8 * i, 1);//make variabls to we can move it around
	}
}

void HUD::controller()
{
	if (Controller::FPSLock)
	{
		
	}
	

	//temp swap control
	if (Controller::keyboardStates[SDL_SCANCODE_P] == 1)
	{
		//go to next ent
		playerEntID++;
		if (playerEntID >= Mapper::activeEntities.size())//if entID is over and needs to loop
		{
			playerEntID = 0;
		}
		int lastEntID = playerEntID - 1;//get ent we just moved from
		if (lastEntID < 0)//if entID is under and needs to be set to the last of them all
		{
			lastEntID = Mapper::activeEntities.size() - 1;
		}
		//AI slot for moving around AIs, fill it with the AI of last ent to pass it on
		bool (*tempAI)(int) = Mapper::activeEntities[lastEntID].AI;
		//set the AI of the ent we were last controlling to what it used to be/the dummy func if its the first time
		Mapper::activeEntities[lastEntID].AI = AIFuncSlot;
		//set this ents AI aside so we can return it later
		AIFuncSlot = Mapper::activeEntities[playerEntID].AI;
		//overwrite the AI of the ent we are taking control of
		Mapper::activeEntities[playerEntID].AI = tempAI;
	}

	//temp adjust health
	if (Controller::keyboardStates[SDL_SCANCODE_UP] == 2)
	{
		Mapper::activeEntities[playerEntID].health.current += 1;
	}
	if (Controller::keyboardStates[SDL_SCANCODE_DOWN] == 2)
	{
		Mapper::activeEntities[playerEntID].health.current -= 1;
	}
}
