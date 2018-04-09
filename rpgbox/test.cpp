#include "map.h"
#include "character.h"
#include "talk.h"
#include "fight.h"
#include "ui.h"
#include "monster.h"
#include <Windows.h>

//包含了main函数

using namespace std;

const int SCREEN_WIDTH = 480;
const int SCREEN_HEIGHT = 320;
const int PIXEL_WIDTH = 32;
const int PIXEL_HEIGHT = 32;




int mapdata1[10][15] = {
	18,18,18,17,18,18,18,18,18,18,18,55,55,55,18,
	18,17,18,17,17,17,17,17,17,17,17,55,55,55,18,
	18,17,17,17,17,17,18,18,17,17,17,55,55,55,18,
	18,17,17,17,18,18,18,18,18,17,17,55,55,17,18,
	18,17,17,18,22,23,23,23,24,18,17,21,21,17,18,
	18,17,17,18,25,28,26,79,27,18,55,55,55,17,18,
	18,17,17,18,18,10,11,12,17,18,55,55,17,17,18,
	18,18,17,17,10,16,16,16,11,55,55,17,17,17,18,
	18,18,17,17,77,16,16,16,16,21,21,17,17,17,18,
	18,18,18,18,18,18,18,18,18,55,55,18,18,18,18

};

int walldata1[10][15] = {
	1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1,
	1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1,
	1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 1,
	1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1,
	1, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1,
	1, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1,
	1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1,
	1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
};

int triggerdata1[10][15] = {
	0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 32, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 31, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};

int mapdata2[10][15] = {
	0,0,1,2,2,2,2,2,2,2,2,1,0,0,0,
	0,0,1,3,5,5,1,5,5,5,5,1,0,0,0,
	0,0,1,80,82,4,1,80,4,4,4,1,0,0,0,
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

int triggerdata2[10][15] = {
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 21, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 31, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};

int mapdata3[10][15] = {
	18,18,18,18,18,18,18,18,18,18,18,18,55,55,18,
	18,17,17,17,17,17,17,17,17,17,17,17,55,55,18,
	18,17,17,17,17,17,17,17,17,17,17,17,55,55,18,
	18,17,17,17,17,17,17,17,17,17,17,55,55,55,18,
	18,17,17,17,0,17,17,17,17,18,18,55,55,55,18,
	18,17,17,17,17,17,17,17,17,18,18,55,55,55,18,
	18,17,17,17,17,17,17,17,17,18,18,55,55,55,18,
	18,17,17,17,17,17,17,17,17,18,18,55,55,55,18,
	18,17,17,17,17,17,17,17,17,18,18,55,55,55,18,
	18,18,18,17,18,18,18,18,18,18,18,55,55,55,18
};

int walldata3[10][15] = {
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1,
	1,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
};

int triggerdata3[10][15] = {
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 32, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};

SDL_Window* window = NULL;

SDL_Renderer* renderer = NULL;

TTF_Font* font = NULL;
TTF_Font* font2 = NULL;

string bgwtext = "RPGBOX";
SDL_Color bgwcolor = { 255,255,255 };
MapTexture sceneTexture;
Ui bgw = Ui(80, 200, 400, 120);
Talk talk;
string talktext = "ops,this is a bug!";
string talktext2 = "it should be fixed!";
SDL_Color talkcolor = { 0,0,0, };
Character cha;
Fight fight;
SDL_Rect sceneClips[100];


Monster slime(20, 1);
Ui charahp = Ui(32, 32, 64, 32);
string chahpstr;
Ui monsterhp = Ui(384, 32, 64, 32);
string monhpstr;
Ui attack = Ui(200, 64, 80, 32);


MapTexture outTexture = MapTexture(mapdata1,walldata1,triggerdata1);
MapTexture inTexture = MapTexture(mapdata2, walldata2, triggerdata2);
MapTexture outTexture2 = MapTexture(mapdata3, walldata3, triggerdata3);

void bound() {
	outTexture.setnext(0,&inTexture);
	outTexture.setnext(1, &outTexture2);
	inTexture.setnext(0,&outTexture);
	outTexture2.setnext(1, &outTexture);
}

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
		window = SDL_CreateWindow("rpgbox test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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
		if (TTF_Init() == -1)
		{
			cout << "字体库初始化失败" << endl;
			success = false;
		}
	}
	return success;
}

bool loadScene()
{
	const int width = 32;
	const int height = 32;

	bool success = true;
	if (!sceneTexture.loadFromFile(renderer, "test2.jpg"))
	{
		std::cout << "加载场景图片失败" << std::endl;
		success = false;
	}

	if (!cha.loadFromFile(renderer, "cha.png"))
	{
		std::cout << "加载人物图片失败" << std::endl;
		success = false;
	}

	font = TTF_OpenFont("123.ttf",12);
	font2 = TTF_OpenFont("lazy.ttf", 10);
	if (!font) {
		cout << "加载字体文件失败" << endl;
		success = false;
	}

	if (!bgw.loadtextFromFont(font, renderer, bgwtext, bgwcolor)) {
		cout << "加载背景文本失败" << endl;
		success = false;
	}

	if (!attack.loadpicFromFile(renderer, "attack.png")) {
		cout << "加载按钮图片失败" << endl;
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


	int r = bgw.setAlpha(63);
	return success;
}

bool loadmonster() {
	bool success = true;
	if (!slime.loadFromFile(renderer, "slime.png")) {
		cout << "史莱姆图片载入失败" << endl;
		success = false;
	}
	return success;
}

void renderscreen() {
	SDL_RenderClear(renderer);

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 15; j++) {
			sceneTexture.render(renderer, j * 32, i * 32, &sceneClips[sceneTexture.mapdata[i][j]]);
		}
	}
	cha.render(renderer);
	bgw.rendertext(renderer);
	SDL_RenderPresent(renderer);
}

void close()
{
	sceneTexture.free();
	cha.free();
	fight.free();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	window = NULL;
	renderer = NULL;
	TTF_CloseFont(font);
	font = NULL;
	TTF_Quit();
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
			if (!loadmonster()) {
				cout << "加载怪物文件失败" << endl;
			}
			else {
				bool quit = false;

				SDL_Event e;

				int wallnum = sceneTexture.initmap(outTexture);
				SDL_Rect* trigger[30];
				for (int i = 0; i < 30; i++) {
					trigger[i] = sceneTexture.gett(i);
					/*if (trigger[i]) {
					cout << trigger[i]->x << endl;
					}*/
				}
				SDL_Rect* wall = sceneTexture.getwall();
				int jump = 100;
				/*enum jumpto {

				};*/

				while (!quit)
				{
					if (jump == 100) {
						while (SDL_PollEvent(&e) != 0)
						{
							if (e.type == SDL_QUIT)
							{
								quit = true;
							}
							//cout << jump << endl;
							cha.handleEvent(e);
						}

						jump = cha.move(SCREEN_WIDTH, SCREEN_HEIGHT, &sceneTexture, jump);
					}

					/*if (e.type == SDL_MOUSEBUTTONDOWN) {
					cout << "鼠标按下" << endl;
					}*/

					if (jump < 10) {
						//cout << jump << endl;
						wallnum = sceneTexture.initmap(*sceneTexture.getnext(jump));
						cha.setmposx(sceneTexture.getb(jump)->x);
						cha.setmposy(sceneTexture.getb(jump)->y);
						cout << "传送成功" << endl;
						for (int i = 0; i < 30; i++) {
							trigger[i] = sceneTexture.gett(i);
						}
						wall = sceneTexture.getwall();
						jump = 100;

						renderscreen();
					}

					else if (jump >= 10 && jump < 20) {
						while (SDL_PollEvent(&e) != 0)
						{
							if (e.type == SDL_QUIT)
							{
								quit = true;
							}
							//cout << "jumpman" << endl;
							cha.handleEvent(e);
							jump = talk.handleEvent(e, jump);
						}

						talk.free();
						talk.loadbackFromFile(renderer, "back.png");
						talk.loadtalkFromFont(font, renderer, talktext, talkcolor);
						talk.render(renderer);
						SDL_RenderPresent(renderer);

						//Sleep(100);
						/*talk.loadbackFromFile(renderer, "back.png");
						talk.loadtalkFromFont(font, renderer, talktext2, talkcolor);
						talk.render(renderer);
						SDL_RenderPresent(renderer);
						SDL_RenderClear(renderer);
						Sleep(2000);*/
						//renderscreen();
					}

					else if (jump >= 20 && jump < 30) {
						if (slime.gethp() > 0) {
							bool over = false;
							SDL_RenderClear(renderer);
							while (!over) {
								bool atk = false;
								while (SDL_PollEvent(&e) != 0)
								{
									if (e.type == SDL_QUIT)
									{
										quit = true;
									}
									cha.handleEvent(e);
									atk = attack.handleEvent(e);
								}
								charahp.free();
								monsterhp.free();
								fight.free();
								fight.loadFromFile(renderer, "fight.png");
								fight.render(renderer);
								attack.renderpic(renderer);
								int x = cha.getmposx();
								int y = cha.getmposy();
								cha.setmposx(64);
								cha.setmposy(180);
								cha.render(renderer);
								slime.render(renderer);
								chahpstr = to_string(cha.gethp());
								monhpstr = to_string(slime.gethp());
								charahp.loadtextFromFont(font2, renderer, chahpstr, talkcolor);
								monsterhp.loadtextFromFont(font2, renderer, monhpstr, talkcolor);
								charahp.rendertext(renderer);
								monsterhp.rendertext(renderer);
								SDL_RenderPresent(renderer);
								over = fight.fightprocess(&cha, &slime, atk, over);
								cha.setmposx(x);
								cha.setmposy(y);
							}
						}
						jump = 100;
					}
					else {
						renderscreen();
					}
				}
			}
		}
	}

	close();

	return 0;

}