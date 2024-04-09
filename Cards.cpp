#include "Cards.h"
#include "Artist.h"



std::vector<SDL_Texture*> Cards::classResourceIcons;

std::vector<Artist::RGB> Cards::classColors = {
	{125, 109, 77},
	{255, 0, 0},
	{0, 255, 0},
	{0, 125, 125},
	{0, 0, 255},
	{255, 255, 0},
	{200, 0, 200}
};

std::vector<std::string> Cards::classResourceNames = {
	{"Energy"},
	{"Might"},
	{"Focus"},
	{"Force"},
	{"Insight"},
	{"Judgment"},
	{"Faith"}
};

//TEMP
Cards::card tempCard;
void Cards::TEMPloadCard()
{
	Artist artist;

	tempCard.cardBase = artist.loadTexture("Resource/cards/base.png");
	tempCard.classID = CLASS_BASIC;
	tempCard.name = "Test Name";
	SDL_SetTextureColorMod(tempCard.cardBase, classColors[tempCard.classID].r, classColors[tempCard.classID].g, classColors[tempCard.classID].b);
	
}

//card will be cented on the x possition, and sit on top of the y given
void drawCard(Cards::card cardToDraw, int xPos, int yPos, float scale, float rotation = 0)
{
	Artist artist;

	int width = 250 * scale;
	int height = 375 * scale;
	int newX = xPos - width / 2;
	int newY = yPos - height;
	artist.drawImage(cardToDraw.cardBase, newX, newY, width, height, rotation);
}

void Cards::init()
{
	Artist artist;

	TEMPloadCard();

	//load the icons for each classes resources
	Cards::classResourceIcons.push_back(artist.loadTexture("Resource/HUD/basicIcon.png"));
	Cards::classResourceIcons.push_back(artist.loadTexture("Resource/HUD/basicIcon.png"));
	Cards::classResourceIcons.push_back(artist.loadTexture("Resource/HUD/basicIcon.png"));
	Cards::classResourceIcons.push_back(artist.loadTexture("Resource/HUD/basicIcon.png"));
	Cards::classResourceIcons.push_back(artist.loadTexture("Resource/HUD/basicIcon.png"));
	Cards::classResourceIcons.push_back(artist.loadTexture("Resource/HUD/basicIcon.png"));
	Cards::classResourceIcons.push_back(artist.loadTexture("Resource/HUD/basicIcon.png"));
}

void Cards::draw()//DONT NEED?
{
	//drawCard(tempCard, 960, 1080, .5);
}