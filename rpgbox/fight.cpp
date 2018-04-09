#include "fight.h"

Fight::Fight() {

}

Fight::~Fight() {
	free();
}
void Fight::free() {
	if (mTexture != NULL) {
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

bool Fight::loadFromFile(SDL_Renderer* renderer, string path) {
	SDL_Texture* newTexture = NULL;

	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL) {
		cout << "����ͼƬʧ��" << endl;
	}
	else {
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (newTexture == NULL) {
			cout << "��surface����textureʧ��" << endl;
		}
		else {
			//��surface�ж�ȡ����͸�
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

bool Fight::fightprocess(Character* cha, Monster* mon, bool handle, bool over) {
	if (handle) {
		cout << "handle is true" << endl;
		cha->sethp(cha->gethp() - mon->getatk());
		mon->sethp(mon->gethp() - cha->getatk());
	}
	if (cha->gethp() <= 0 || mon->gethp() <= 0) {
		over = true;
		cout << "now over is true" << endl;
		cout << mon->gethp() << endl;
	}

	return over;
}

void Fight::handleEvent(SDL_Event& e) {
	/*if (e.type == SDL_MOUSEBUTTONDOWN) {
		int x, y;
		SDL_GetMouseState(&x, &y);
		bool atksuc = true;
		
	}*/
}
