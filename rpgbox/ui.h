#ifndef _UI_H_
#define _UI_H_
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <iostream>
#include <cmath>
#include "loadimg.h"
#include "SDL_mixer.h"
using namespace std;

enum uistate {
	OUT = 0,
	IN = 1,
	DOWN = 2,
	UP = 3,
};

class Ui {
public:
	Ui();
	Ui(int x, int y, int w, int h);
	~Ui();
	bool loadpicFromFile(SDL_Renderer* renderer, string path);
	bool loadtextFromFont(TTF_Font* font, SDL_Renderer* renderer, string Ui, SDL_Color Uicolor);
	void free();
	bool handleEvent(SDL_Event& e, Mix_Chunk *inse, Mix_Chunk *downse);
	void renderbutton(SDL_Renderer* renderer);
	void renderpic(SDL_Renderer* renderer);
	void rendertext(SDL_Renderer* renderer);
	SDL_Rect* getcollision();
	int setpicAlpha(Uint8 alpha);
	int settextAlpha(Uint8 alpha);
	void setPos(int x, int y, int w, int h);
private:
	SDL_Texture * uipictexture;
	SDL_Texture* uitexttexture;
	std::string content;
	int mWidth;
	int mHeight;
	int posx;
	int posy;
	int width;
	int height;
	SDL_Rect mCollision;
	uistate state;
};
#endif