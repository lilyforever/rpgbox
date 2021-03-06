#include "map.h"
#include <iostream>
using namespace std;


MapTexture::MapTexture() {
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
	mapdata = NULL;
	walldata = NULL;
	wallnum = 0;
}

MapTexture::MapTexture(int(*m)[15], int(*w)[15], int(*t)[15],  int i) {
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
	mapdata = m;
	walldata = w;
	triggerdata = t;
	mapnum = i;
	wallnum = 0;
}

MapTexture::~MapTexture() {
	free();
}

bool MapTexture::loadFromFile(SDL_Renderer* renderer, string path) {
	free();
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

int MapTexture::initmap(MapTexture m) {
	mapdata = m.mapdata;
	walldata = m.walldata;
	triggerdata = m.triggerdata;
	mapnum = m.getnum();
	for (int i = 0; i < 10; i++) {
		birth[i] = m.birth[i];
		next[i] = m.next[i];
	}
	for (int i = 0; i < 30; i++) {
		trigger[i] = NULL;
	}
	
	wallnum = 0;

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 15; j++) {
			if (walldata[i][j] == 1) {
				//wall里面没有清除干净
				wall[wallnum] = { j * 32,i * 32,32,32 };
				wallnum += 1;
			}
		}
	}
	
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 15; j++) {
			if (triggerdata[i][j]) {
				int t = triggerdata[i][j] - 1;
				if (t>=0 && t< 30) {
					//这里可以改触发点的大小
					Trigger[t] = { j * 32+8,i * 32+8,16,16 };
					trigger[t] = &Trigger[t];
					cout << "triggernum" << triggerdata[i][j] << " x: " << trigger[t]->x << " y: " << trigger[t]->y <<endl;
				}
				else {
					Birth[t - 30] = { j * 32,i * 32,32,32 };
					birth[t - 30] = &Birth[t - 30];
				}
			}
		}
	};
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
	//设置渲染块的坐标
	SDL_Rect renderbox = { x, y, mWidth, mHeight };

	//设置渲染块的大小
	if (clip != NULL)
	{
		renderbox.w = clip->w;
		renderbox.h = clip->h;
	}

	//将纹理在切割块部分的内容复制到指定的渲染块处
	SDL_RenderCopy(renderer, mTexture, clip, &renderbox);
}

int MapTexture::getWidth() {
	return mWidth;
}

int MapTexture::getHeight() {
	return mHeight;
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

MapTexture* MapTexture::getnext(int i) {
	return next[i];
}

void MapTexture::setnext(int i, MapTexture* m) {
	next[i] = m;
}

SDL_Rect* MapTexture::getb(int i) {
	return birth[i];
}

SDL_Rect* MapTexture::gett(int i) {
	return trigger[i];
}

int MapTexture::getnum() {
	return mapnum;
}