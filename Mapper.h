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
#ifndef HUD
#include "HUD.h"
#endif
#ifndef Artist
#include "Artist.h"
#endif

class Mapper {
public:
	struct groundTile {
		SDL_Texture* tex;//make an array so we can have animation options
		std::string name;
		bool walkable;
	};
	struct wallTile {
		SDL_Texture* tex;
		std::string name;
		std::vector<std::vector<int>> microCollision;
		//maybe something to determing in combat walkability AND for pathfinding, maybe have it be generated on loading the tile 
	};
	struct combinedTile {
		groundTile* ground;
		wallTile* wall;
	};
	struct map {
		std::vector<std::vector<combinedTile>> tiles;
		//entities list
		//tile effects list
	};
	struct entity {
		std::vector<SDL_Texture*> tex;//add second layer for animations
		std::string name;
		float xPos, yPos, xVel, yVel;
		int size; //add maybe tile size aswell?
		HUD::resourceBar health;
		HUD::resourceBar stamina;
		std::vector< HUD::resourceBar> classResources;
		bool running;
		std::vector<HUD::ability> abilities;
		float rotation;
		bool (*AI)(int); //maybe make a vector
		Artist::pos destination;
		std::vector<std::vector<bool>> visitable; // where the ent knows it can go
		std::vector <std::vector<Artist::pos>> paths; //paths how ent can go there
		Artist::pos pathsMapPos; //where the path grid starts on the world
	};
	static map activeMap;
	static std::vector<groundTile> groundTileMasterList;
	static std::vector<wallTile> wallTileMasterList;
	static std::vector<entity> activeEntities;
	static Artist::pos cameraPos;

	
	

	void init();
	void draw();
	void controller();
	void update();
};