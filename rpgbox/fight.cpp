#include "fight.h"

Fight::Fight() {
}

Fight::~Fight() {
}

bool Fight::loadFromFile(SDL_Renderer* renderer, string path) {
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
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}
		SDL_FreeSurface(loadedSurface);
	}
	mTexture = newTexture;
	return mTexture != NULL;
}

void Fight::render(SDL_Renderer* renderer) {
	SDL_Rect box = { 0,0,FIGHT_WIDTH,FIGHT_HEIGHT };
	SDL_RenderCopy(renderer, mTexture, &box, &box);
}