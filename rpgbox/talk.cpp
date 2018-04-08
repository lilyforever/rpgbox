#include "talk.h"

Talk::Talk() {

}

Talk::~Talk() {

}

bool Talk::loadfaceFromFile(SDL_Renderer* renderer, std::string path) {
	bool b = loadtexture(facetexture, renderer, path);
	return b;
}

bool Talk::loadtalkFromFont(TTF_Font* font, SDL_Renderer* renderer, string talk, SDL_Color talkcolor) {
	SDL_Texture* newTexture = NULL;

	SDL_Surface* loadedSurface = TTF_RenderText_Solid(font, talk.c_str(), talkcolor);
	if (loadedSurface == NULL) {
		cout << "����Ի�ʧ��" << endl;
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
	talktexture = newTexture;
	return talktexture != NULL;
}

void Talk::render(SDL_Renderer* renderer) {
	SDL_Rect rendertalkbox = { TALK_X, TALK_Y,TALK_WIDTH,TALK_HEIGHT };
	SDL_Rect talkbox = { 0,0,TALK_WIDTH,TALK_HEIGHT };
	SDL_Rect renderfacebox = { FACE_X, FACE_Y,FACE_WIDTH,FACE_HEIGHT };
	SDL_Rect facebox = { 0,0,FACE_WIDTH,FACE_HEIGHT };

	SDL_RenderCopy(renderer, talktexture, &talkbox, &rendertalkbox);
	SDL_RenderCopy(renderer, facetexture, &facebox, &renderfacebox);
}

void Talk::show() {
	
}