#include "talk.h"

Talk::Talk() {

}

Talk::~Talk() {

}

bool Talk::loadfaceFromFile(SDL_Renderer* renderer, std::string path) {
	bool b = loadtexture(mWidth,mHeight,facetexture, renderer, path);
	return b;
}

bool Talk::loadtalkFromFile(SDL_Renderer* renderer, std::string path) {
	bool b = loadtexture(mWidth, mHeight,talktexture, renderer, path);
	return b;
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