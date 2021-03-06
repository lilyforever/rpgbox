#ifndef _FIGHT_H_
#define _FIGHT_H_
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "character.h"
#include "monster.h"
#include <string>
#include <iostream>

using namespace std;

class Fight {
public:
	static const int FIGHT_WIDTH = 480;
	static const int FIGHT_HEIGHT = 320;
	Fight();
	~Fight();
	bool loadFromFile(SDL_Renderer* renderer, std::string path);
	void free();
	void handleEvent(SDL_Event& e);
	bool fightprocess(Character* cha, Monster* mon, bool handle, bool over);
	void render(SDL_Renderer* renderer);
private:
	int mWidth;
	int mHeight;
	SDL_Texture* mTexture;
};
#endif
