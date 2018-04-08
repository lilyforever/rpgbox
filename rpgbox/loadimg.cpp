#include "loadimg.h"
#include <iostream>
using namespace std;
bool loadtexture(int w, int h, SDL_Texture* mTexture, SDL_Renderer* renderer, std::string path) {
	SDL_Texture* newTexture = NULL;

	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL) {
		cout << "载入图片失败" << endl;
	}
	else {
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (newTexture == NULL) {
			cout << "将surface赋给texture失败" << endl;
		}
		else {
			//从surface中读取到宽和高
			w = loadedSurface->w;
			h = loadedSurface->h;
		}
		SDL_FreeSurface(loadedSurface);
	}
	mTexture = newTexture;
	return mTexture != NULL;
}