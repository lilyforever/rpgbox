#include "talk.h"

Talk::Talk() {

}

Talk::~Talk() {
	free();
}

bool Talk::loadbackFromFile(SDL_Renderer* renderer, std::string path) {
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
	backtexture = newTexture;
	return backtexture != NULL;
}

bool Talk::loadtalkFromFont(TTF_Font* font, SDL_Renderer* renderer, string talk, SDL_Color talkcolor) {
	SDL_Texture* newTexture = NULL;

	SDL_Surface* loadedSurface = TTF_RenderText_Solid(font, talk.c_str(), talkcolor);
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
	talktexture = newTexture;
	return talktexture != NULL;
}

void Talk::free() {
	if (backtexture != NULL) {
		SDL_DestroyTexture(backtexture);
		backtexture = NULL;
		SDL_DestroyTexture(talktexture);
		talktexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

int Talk::handleEvent(SDL_Event& e, int jump) {
	if (e.type == SDL_MOUSEBUTTONDOWN) {
		cout << "jump" << endl;
		jump = 100;
	}

	return jump;
}

void Talk::render(SDL_Renderer* renderer) {
	SDL_Rect rendertalkbox = { TALK_X, TALK_Y,TALK_WIDTH,TALK_HEIGHT };
	SDL_Rect talkbox = { 0,0,TALK_WIDTH,TALK_HEIGHT };
	SDL_Rect renderfacebox = { FACE_X, FACE_Y,FACE_WIDTH,FACE_HEIGHT };
	SDL_Rect facebox = { 0,0,FACE_WIDTH,FACE_HEIGHT };


	SDL_RenderCopy(renderer, backtexture, &talkbox, &rendertalkbox);
	SDL_RenderCopy(renderer, talktexture, &talkbox, &rendertalkbox);
}