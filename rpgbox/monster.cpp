#include "monster.h"

Monster::Monster() {
	m_posx = 332;
	m_posy = 164;
}

Monster::Monster(int h, int a, string n) {
	hp = h;
	atk = a;
	name = n;
	m_posx = 416;
	m_posy = 180;
}

Monster::~Monster() {
	free();
}

void Monster::free() {
	if (mTexture != NULL) {
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
	}
	mWidth = 0;
	mHeight = 0;
}

bool Monster::loadFromFile(SDL_Renderer* renderer, string path) {
	free();
	SDL_Texture* newTexture = NULL;

	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL) {
		cout << "载入图片失败" << endl;
	}
	else {
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0xFF, 0xFF, 0xFF));
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

void Monster::render(SDL_Renderer* renderer) {
	SDL_Rect renderbox = { m_posx, m_posy, MON_WIDTH, MON_HEIGHT };
	SDL_Rect monbox = { 0,0,MON_WIDTH,MON_HEIGHT };

	SDL_RenderCopy(renderer, mTexture, &monbox, &renderbox);
}

int Monster::gethp() {
	return hp;
}

int Monster::getatk() {
	return atk;
}

void Monster::sethp(int i) {
	hp = i;
}

void Monster::setatk(int i) {
	atk = i;
}

string* Monster::getname() {
	return &name;
}