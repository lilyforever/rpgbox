#include "loadimg.h"
#include <iostream>
using namespace std;
bool loadtexture(SDL_Texture* mTexture, SDL_Renderer* renderer, std::string path) {
	SDL_Texture* newTexture = NULL;

	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL) {
		cout << "ÔØÈëÍ¼Æ¬Ê§°Ü" << endl;
	}
	else {
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (newTexture == NULL) {
			cout << "½«surface¸³¸øtextureÊ§°Ü" << endl;
		}
		SDL_FreeSurface(loadedSurface);
	}
	mTexture = newTexture;
	return mTexture != NULL;
}