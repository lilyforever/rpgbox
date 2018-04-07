#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include "map.h"
#include "character.h"

//包含了main函数

using namespace std;

const int SCREEN_WIDTH = 480;
const int SCREEN_HEIGHT = 320;
const int PIXEL_WIDTH = 32;
const int PIXEL_HEIGHT = 32;



int mapdata1[10][15] = {
	18,18,18,18,18,18,18,18,18,18,18,18,55,55,18,
	18,17,18,17,17,17,17,17,17,17,17,17,55,55,18,
	18,17,17,17,17,17,18,18,17,17,17,17,55,55,18,
	18,17,17,17,18,18,18,18,18,17,17,55,55,17,18,
	18,17,17,18,22,23,23,23,24,18,17,21,21,17,18,
	18,17,17,18,25,28,26,79,27,18,55,55,55,17,18,
	18,17,17,18,18,10,11,12,17,18,55,55,17,17,18,
	18,18,17,17,10,16,16,16,11,55,55,17,17,17,18,
	18,18,17,17,77,16,16,16,16,21,21,17,17,17,18,
	18,18,18,18,18,18,18,18,18,55,55,18,18,18,18

};

int walldata1[10][15] = {
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1,
	1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1,
	1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 1,
	1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1,
	1, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1,
	1, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1,
	1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1,
	1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
};

SDL_Rect portal1 = { 192, 160,32,32 };
SDL_Rect birth1 = { 192,192,32,32 };

int mapdata2[10][15] = {
	0,0,1,2,2,2,2,2,2,2,2,1,0,0,0,
	0,0,1,3,5,5,1,5,5,5,5,1,0,0,0,
	0,0,1,80,4,4,1,80,4,4,4,1,0,0,0,
	0,0,1,80,4,4,1,80,8,7,8,1,0,0,0,
	0,0,1,80,4,4,5,81,4,4,4,1,0,0,0,
	0,0,1,2,2,2,6,4,4,4,4,1,0,0,0,
	0,0,1,3,5,5,81,4,4,4,4,1,0,0,0,
	0,0,1,80,4,4,4,4,4,4,9,1,0,0,0,
	0,0,1,2,2,2,2,6,2,2,2,1,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
};

int walldata2[10][15] = {
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,0,0,0,1,0,0,0,0,1,1,1,1,
	1,1,1,0,0,0,1,0,0,0,0,1,1,1,1,
	1,1,1,0,0,0,1,0,0,1,0,1,1,1,1,
	1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,
	1,1,1,1,1,1,0,0,0,0,0,1,1,1,1,
	1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,
	1,1,1,0,0,0,0,0,0,0,1,1,1,1,1,
	1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
};

SDL_Rect portal2 = { 224, 256,32,32 };
SDL_Rect birth2 = { 224,224,32,32 };

SDL_Window* window = NULL;

SDL_Renderer* renderer = NULL;

MapTexture sceneTexture;

MapTexture outTexture = MapTexture(mapdata1,walldata1,&portal1,&birth1);
MapTexture inTexture = MapTexture(mapdata2, walldata2, &portal2,&birth2);
void bound() {
	outTexture.setnext(&inTexture);
	inTexture.setnext(&outTexture);
}
Character cha;

SDL_Rect sceneClips[100];
//SDL_Rect wall[150];
//int (*mapdata)[15] = NULL;
//int (*walldata)[15] = NULL;
//int wallnum = 0;


bool init()
{
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "SDL初始化失败" << endl;
		success = false;
	}
	else
	{
		window = SDL_CreateWindow("map test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			cout << "窗口创建失败" << endl;
			success = false;
		}
		else
		{
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			if (renderer == NULL)
			{
				cout << "渲染器创建失败" << endl;
				success = false;
			}
		}
	}
	return success;
}

bool loadScene()
{
	const int width = 32;
	const int height = 32;

	bool success = true;
	if (!sceneTexture.loadFromFile(renderer, "test.jpg"))
	{
		std::cout << "加载场景图片失败" << std::endl;
		success = false;
	}

	if (!cha.loadFromFile(renderer, "cha.jpg"))
	{
		std::cout << "加载场景图片失败" << std::endl;
		success = false;
	}

	//将原版的场景图片切割成100份，每份32*32
	else
	{
		for (int i = 0; i < 100; i++) {
			sceneClips[i].x = i % 10 * 32;
			sceneClips[i].y = i / 10 * 32;
			sceneClips[i].w = width;
			sceneClips[i].h = height;
		}
	}



	return success;
}

void close()
{
	sceneTexture.free();
	cha.free();

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	window = NULL;
	renderer = NULL;
	IMG_Quit();
	SDL_Quit();
}





int main(int argc, char* argv[])
{
	bound();
	
	if (!init())
	{
		cout << "初始化失败" << endl;
	}
	else
	{
		if (!loadScene())
		{
			cout << "加载多媒体文件失败" << endl;
		}
		else
		{
			bool quit = false;

			SDL_Event e;

			int wallnum = sceneTexture.initmap(outTexture);
			SDL_Rect* portal = sceneTexture.getp();
			SDL_Rect* wall = sceneTexture.getwall();
			bool jump = false;

			while (!quit)
			{
				while (SDL_PollEvent(&e) != 0)
				{
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}
					cha.handleEvent(e);
				}

				jump = cha.move(SCREEN_WIDTH, SCREEN_HEIGHT, &sceneTexture, jump);

				if (jump) {
					int wallnum = sceneTexture.initmap(*sceneTexture.getnext());
					cha.setmposx(sceneTexture.getb()->x);
					cha.setmposy(sceneTexture.getb()->y);
					cout << "chuansongchenggong" << endl;
					SDL_Rect* portal = sceneTexture.getp();
					SDL_Rect* wall = sceneTexture.getwall();
					jump = false;
				}

				SDL_RenderClear(renderer);

				for (int i = 0; i < 10; i++) {
					for (int j = 0; j < 15; j++) {
						sceneTexture.render(renderer, j*32, i*32, &sceneClips[sceneTexture.mapdata[i][j]]);
					}
				}
				cha.render(renderer);
				SDL_RenderPresent(renderer);
			}
		}
	}

	close();

	return 0;

}