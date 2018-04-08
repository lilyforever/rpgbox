#ifndef _TALK_H_
#define _TALK_H_
#include "SDL.h"
#include "loadimg.h"

class Talk {
public:
	static const int FACE_X = 0;
	static const int FACE_Y = 160;
	static const int NAME_X = 80;
	static const int NAME_Y = 192;
	static const int TALK_X = 80;
	static const int TALK_Y = 200;
	static const int FACE_WIDTH = 80;
	static const int FACE_HEIGHT = 160;
	static const int NAME_WIDTH = 80;
	static const int NAME_HEIGHT = 32;
	static const int TALK_WIDTH = 400;
	static const int TALK_HEIGHT = 120;
	
	Talk();
	~Talk();
	bool loadfaceFromFile(SDL_Renderer* renderer, std::string path);
	bool loadtalkFromFile(SDL_Renderer* renderer, std::string path);
	void render(SDL_Renderer* renderer);
	void show();
private:
	SDL_Texture* facetexture;
	SDL_Texture* talktexture;
	std::string name;
	std::string content;
	int mWidth;
	int mHeight;
};
#endif