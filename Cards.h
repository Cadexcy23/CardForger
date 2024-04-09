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
#ifndef Artist
#include "Artist.h"
#endif

class Cards {
public:
	struct card {
		std::string name;
		int classID;
		SDL_Texture* cardBase;

	};

	enum classes {
		CLASS_BASIC,
		CLASS_WARRIOR,
		CLASS_RANGER,
		CLASS_SPELLSWORD,
		CLASS_WIZARD,
		CLASS_PALADIN,
		CLASS_PRIEST
	};

	static std::vector<Artist::RGB> classColors;
	static std::vector<SDL_Texture*> classResourceIcons;
	static std::vector<std::string> classResourceNames;

	void TEMPloadCard();
	void init();
	void draw();
};