#include "map.h"
#include <iostream>
using namespace std;


MapTexture::MapTexture() {
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
	mapdata = NULL;
	walldata = NULL;
	portal = NULL;
	wallnum = 0;
	next = NULL;
}

MapTexture::MapTexture(int(*m)[15], int(*w)[15],SDL_Rect* p,SDL_Rect* b) {
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
	mapdata = m;
	walldata = w;
	portal = p;
	birth = b;
	wallnum = 0;
	next = NULL;
}

MapTexture::~MapTexture() {
	free();
}

bool MapTexture::loadFromFile(SDL_Renderer* renderer, string path) {
	free();
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

int MapTexture::initmap(MapTexture m) {
	mapdata = m.mapdata;
	walldata = m.walldata;
	portal = m.portal;
	birth = m.birth;
	next = m.next;
	wallnum = 0;

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 15; j++) {
			if (walldata[i][j] == 1) {
				//wall����û������ɾ�
				wall[wallnum] = { j * 32,i * 32,32,32 };
				wallnum += 1;
			}
		}
	}
	return wallnum;
}

void MapTexture::free() {
	if (mTexture != NULL) {
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void MapTexture::render(SDL_Renderer* renderer, int x, int y, SDL_Rect* clip)
{
	//������Ⱦ�������
	SDL_Rect renderbox = { x, y, mWidth, mHeight };

	//������Ⱦ��Ĵ�С
	if (clip != NULL)
	{
		renderbox.w = clip->w;
		renderbox.h = clip->h;
	}

	//���������и�鲿�ֵ����ݸ��Ƶ�ָ������Ⱦ�鴦
	SDL_RenderCopy(renderer, mTexture, clip, &renderbox);
}

int MapTexture::getWidth() {
	return mWidth;
}

int MapTexture::getHeight() {
	return mHeight;
}

SDL_Rect* MapTexture::getp() {
	return portal;
}

SDL_Rect* MapTexture::getwall() {
	return wall;
}

void MapTexture::setwallnum(int w) {
	wallnum = w;
}

int MapTexture::getwallnum() {
	return wallnum;
}

//int* MapTexture::getmapdata() {
//	return mapdata;
//}

MapTexture* MapTexture::getnext() {
	return next;
}

void MapTexture::setnext(MapTexture* m) {
	next = m;
}

SDL_Rect* MapTexture::getb() {
	return birth;
}