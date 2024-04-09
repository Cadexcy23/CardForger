#pragma once
#ifndef vector
#include <vector>
#endif
#ifndef SDL
#include <SDL.h>
#endif // !SDL
#ifndef string
#include <string>
#endif

class HUD {
public:

	struct resourceBar {
		std::string name;
		int max;
		int current;
		SDL_Texture* icon;
		SDL_Texture* barVisual;
	};

	struct ability {
		std::string name;
		SDL_Texture* icon;
		bool (*function)(int);//bool so we can track if we used the abilitie or not maybe for sound feedback
		SDL_Scancode keyBind;
		int scanType;
		
	};

	static int playerEntID;

	HUD::resourceBar loadResourceBar(int classID, int max, int current);

	void init();
	void controller();
	void draw();
};