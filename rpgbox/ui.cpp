#include "Ui.h"

Ui::Ui() {

}

Ui::Ui(int x, int y, int w, int h) {
	posx = x;
	posy = y;
	width = w;
	height = h;
	mCollision = { x,y,w,h };
	state = OUT;
}

Ui::~Ui() {
	free();
}

SDL_Rect* Ui::getcollision() {
	return &mCollision;
}

bool Ui::loadpicFromFile(SDL_Renderer* renderer, std::string path) {
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
	uipictexture = newTexture;
	return uipictexture != NULL;
}

bool Ui::loadtextFromFont(TTF_Font* font, SDL_Renderer* renderer, string Ui, SDL_Color Uicolor) {
	SDL_Texture* newTexture = NULL;

	SDL_Surface* loadedSurface = TTF_RenderText_Solid(font, Ui.c_str(), Uicolor);
	if (loadedSurface == NULL) {
		cout << "载入对话失败" << endl;
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
	uitexttexture = newTexture;
	return uitexttexture != NULL;
}

void Ui::free() {
	if (uipictexture != NULL) {
		SDL_DestroyTexture(uipictexture);
		uipictexture = NULL;
	}
	if (uitexttexture != NULL) {
		SDL_DestroyTexture(uitexttexture);
		uitexttexture = NULL;
	}
		mWidth = 0;
		mHeight = 0;
}

bool Ui::handleEvent(SDL_Event& e) {
	bool success = false;
	if (e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP) {
		int x, y;
		SDL_GetMouseState(&x, &y);
		bool inside = true;
		if (x<posx || x>posx + width || y<posy || y>posy + height) {
			inside = false;
		}
		if (!inside) {
			state = OUT;
		}
		else {
			switch (e.type) {
			case SDL_MOUSEMOTION:
				state = IN;
				break;
			case SDL_MOUSEBUTTONDOWN:
				state = DOWN;
				success = true;
				cout << "success is true" << endl;
				break;
			case SDL_MOUSEBUTTONUP:
				state = UP;
				break;
			}
		}
	}
	return success;
}

void Ui::renderpic(SDL_Renderer* renderer) {
	SDL_Rect renderUibox = {posx, posy, width, height };
	SDL_Rect uiclips[4];
	for (int i = 0; i < 3; i++) {
		uiclips[i].x = 0;
		uiclips[i].y = i * 32;
		uiclips[i].w = 80;
		uiclips[i].h = 32;
	}
	uiclips[3].x = 0;
	uiclips[3].y = 32;
	uiclips[3].w = 80;
	uiclips[3].h = 32;

	SDL_RenderCopy(renderer, uipictexture, &uiclips[state], &renderUibox);
}

void Ui::rendertext(SDL_Renderer* renderer) {
	SDL_Rect renderUibox = { posx, posy, width, height };
	SDL_Rect Uibox = { 0,0,mWidth,mHeight };

	SDL_RenderCopy(renderer, uitexttexture, &Uibox, &renderUibox);
}

int Ui::setAlpha(Uint8 alpha) {
	SDL_SetTextureAlphaMod(uipictexture, alpha);
	SDL_SetTextureAlphaMod(uitexttexture, alpha);
	return 0;
}

void Ui::setPos(int x, int y, int w, int h) {
	posx = x;
	posy = y;
	width = w;
	height = h;
}