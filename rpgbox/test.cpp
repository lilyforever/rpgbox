#include "map.h"
#include "character.h"
#include "talk.h"
#include "fight.h"
#include "ui.h"
#include "monster.h"
#include <fstream>
#include <Windows.h>

//包含了main函数

using namespace std;

const int SCREEN_WIDTH = 480;
const int SCREEN_HEIGHT = 320;
const int PIXEL_WIDTH = 32;
const int PIXEL_HEIGHT = 32;

//[6][6]放着石头,[6][6]原本是11沙子
//int mapdata1[10][15] = {
//	18,18,18,17,18,18,18,18,18,18,18,55,55,55,18,
//	18,17,18,17,17,17,17,17,17,17,17,55,55,55,18,
//	18,17,17,17,17,17,18,18,17,17,17,55,55,55,18,
//	18,17,17,17,18,18,18,18,18,17,17,55,55,17,18,
//	18,17,17,18,22,23,23,23,24,18,17,21,21,17,18,
//	18,17,17,18,25,28,26,79,27,18,55,55,55,17,18,
//	18,17,17,18,18,10,72,12,17,18,55,55,17,68,18,
//	18,18,17,17,10,16,16,16,11,55,55,17,17,17,18,
//	18,18,17,17,77,16,16,16,16,21,21,17,17,17,18,
//	18,18,18,18,18,18,18,18,18,55,55,18,18,18,18
//
//};
//
//int walldata1[10][15] = {
//	1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
//	1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1,
//	1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1,
//	1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 1,
//	1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1,
//	1, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1,
//	1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 1, 1, 0, 0, 1,
//	1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1,
//	1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
//	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
//};
//
//int triggerdata1[10][15] = {
//	0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//	0, 0, 0, 32, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//	0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0,
//	0, 0, 0, 0, 0, 0, 31, 0, 0, 0, 0, 0, 0, 11, 0,
//	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//};
//
//int mapdata2[10][15] = {
//	0,0,1,2,2,2,2,2,2,2,2,1,0,0,0,
//	0,0,1,3,5,5,1,3,5,5,5,1,0,0,0,
//	0,0,1,80,82,4,1,80,4,4,4,1,0,0,0,
//	0,0,1,80,4,4,1,80,8,7,8,1,0,0,0,
//	0,0,1,80,4,4,5,81,4,4,4,1,0,0,0,
//	0,0,1,2,2,2,6,4,4,4,4,1,0,0,0,
//	0,0,1,3,5,5,81,4,4,4,4,1,0,0,0,
//	0,0,1,80,4,4,4,4,4,4,9,1,0,0,0,
//	0,0,1,2,2,2,2,6,2,2,2,1,0,0,0,
//	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
//};
//
//int walldata2[10][15] = {
//	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
//	1,1,1,0,0,0,1,0,0,0,0,1,1,1,1,
//	1,1,1,0,0,0,1,0,0,0,0,1,1,1,1,
//	1,1,1,0,0,0,1,0,0,1,0,1,1,1,1,
//	1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,
//	1,1,1,1,1,1,0,0,0,0,0,1,1,1,1,
//	0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,
//	0,1,1,0,0,0,0,0,0,0,1,1,1,1,1,
//	0,0,0,1,1,1,1,0,1,1,1,1,1,1,1,
//	1,1,0,0,1,1,1,1,1,1,1,1,1,1,1
//};
//
//int triggerdata2[10][15] = {
//	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//	0, 0, 0, 0, 21, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//	0, 0, 0, 0, 0, 0, 0, 31, 0, 0, 0, 0, 0, 0, 0,
//	0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0,
//	0, 0, 0, 22, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//};
//
//int mapdata3[10][15] = {
//	18,18,18,18,18,18,18,18,18,18,18,18,55,55,18,
//	18,17,17,17,17,17,17,17,17,17,17,17,55,55,18,
//	18,17,17,17,17,17,17,17,17,17,17,17,55,55,18,
//	18,17,17,17,17,17,17,17,17,17,17,55,55,55,18,
//	18,17,17,17,0,17,17,17,17,18,18,55,55,55,18,
//	18,17,17,17,17,17,17,17,17,18,18,55,55,55,18,
//	18,17,17,17,17,17,17,17,17,18,18,55,55,55,18,
//	18,17,17,17,17,17,17,17,17,18,18,55,55,55,18,
//	18,17,17,17,17,17,17,17,17,18,18,55,55,55,18,
//	18,18,18,17,18,18,18,18,18,18,18,55,55,55,18
//};
//
//int walldata3[10][15] = {
//	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
//	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1,
//	1,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1,
//	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1,
//	1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1,
//	1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1,
//	1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1,
//	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1,
//	1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1,
//	1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1
//};
//
//int triggerdata3[10][15] = {
//	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//	0, 0, 0, 0, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//	0, 0, 0, 32, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//	0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 12, 0, 0, 0,
//};

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
TTF_Font* font = NULL;
TTF_Font* font2 = NULL;

string bgwtext = "RPGBOX";
SDL_Color bgwcolor = { 255,255,255 };
MapTexture sceneTexture;
Ui bgw = Ui(80, 200, 400, 120);
Talk talk[100];

string titletext = "RPGBOX DEMO";
Ui title = Ui(40, 10, 400, 120);
Ui titlepic = Ui(0, 0, 480, 320);

//创建怪物
//Monster slime(20, 1, "slime");
//Monster littlemonkey(30, -1, "littlemonkey");

Monster monstertype[20];
Monster monster;
int monsterpos[10][10] = { 0 };
int monsterhp[10][10] = { 0 };

string loadconfig[10];

SDL_Color talkcolor = { 0,0,0, };
SDL_Color maincolor = { 255,255,0, };
Character cha;
int chadata[4];
Fight fight;
SDL_Rect sceneClips[100];

Ui charahpui = Ui(32, 128, 64, 32);
Ui mainhpui = Ui(0, 0, 64, 32);
//主菜单UI
Ui continuegame = Ui(160, 160, 160, 64);
Ui newgame = Ui(160, 240, 160, 64);

string chahpstr;
Ui monsterhpui = Ui(384, 128, 64, 32);
string monhpstr;
Ui monsternameui = Ui(384, 96, 64, 32);
Ui attackui = Ui(160, 180, 160, 64);

//string map3str[20] = { "hello, adventure!","ok, i will help you~","", "", "", "", "", "", "", "",
//									"can you disappear the stone?", "the stone has been disappeared!", "", "", "", "", "", "", "", "", };
//string mapstr[60] = {
//"you are too weak!","","", "", "", "", "", "", "", "",
//"be stronger plzzz", "", "", "", "", "", "", "", "", "",
//"", "", "", "", "", "", "", "", "", "",
//"", "", "", "", "", "", "", "", "", "",
//"hello, adventure!", "ok, i will help you~", "", "", "", "", "", "", "", "",
//"can you disappear the stone?", "the stone has been disappeared!", "", "", "", "", "", "", "", "", };
//string congratulation = "fine, congratulations~!";
//string secretachievement = "o, niupi.";

MapTexture maps[10];

struct Mapdata {
	int mapdata[10][15];
	int walldata[10][15];
	int triggerdata[10][15];
	int next[10];
};

//struct Talkdata {
//	int state[3] = { 0 };
//	const char* content = "null";
//};

Mapdata mapdata[10];
string talklist[10][10][2];
int talkstate[10][10] = { 0 };
int maptotal[1] = { 0 };
int currentmap[1] = { 0 };

bool mainmenu(bool &q, SDL_Event &ev) {
	bool startnew = false;
	bool startload = false;
	while (!startnew && !startload) {
		while (SDL_PollEvent(&ev) != 0)
		{
			startnew = newgame.handleEvent(ev);
			startload = continuegame.handleEvent(ev);
			if (ev.type == SDL_QUIT)
			{
				q = true;
				startload = true;
			}
		}
		titlepic.renderpic(renderer);
		title.rendertext(renderer);
		newgame.renderbutton(renderer);
		continuegame.renderbutton(renderer);
		SDL_RenderPresent(renderer);
	}
	return startnew;
}

void initmaps() {
	ifstream f("testconfig.dat", ios::binary);
	f.read((char*)maptotal, sizeof(int));
	for (int i = 0; i < maptotal[0]; i++) {
		f.read((char*)mapdata[i].mapdata, 150 * sizeof(int));
		f.read((char*)mapdata[i].walldata, 150 * sizeof(int));
		f.read((char*)mapdata[i].triggerdata, 150 * sizeof(int));
		f.read((char*)mapdata[i].next, 10 * sizeof(int));
		maps[i] = MapTexture(mapdata[i].mapdata, mapdata[i].walldata, mapdata[i].triggerdata, i);
		for (int j = 0; j < 10; j++) {
			maps[i].setnext(j, &maps[mapdata[i].next[j]]);
		}
	}
	f.read((char*)monsterpos, 100 * sizeof(int));
	f.close();
}

void inittalk() {
	ifstream f("talklist.txt");
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			for (int k = 0; k < 2; k++) {
				getline(f, talklist[i][j][k]);
			}
		}
	}
	f.close();
}

void loaddata() {
	SDL_RWops* file = SDL_RWFromFile("testsave.bin", "r+b");
	if (file != NULL) {
		SDL_RWread(file, &maptotal[0], sizeof(int), 1);
		SDL_RWread(file, &currentmap[0], sizeof(int), 1);
		for (int i = 0; i < maptotal[0]; i++) {
			SDL_RWread(file, &mapdata[i].mapdata, 150 * sizeof(int), 1);
			SDL_RWread(file, &mapdata[i].walldata, 150 * sizeof(int), 1);
			SDL_RWread(file, &mapdata[i].triggerdata, 150 * sizeof(int), 1);
			SDL_RWread(file, &mapdata[i].next, 10 * sizeof(int), 1);
			maps[i] = MapTexture(mapdata[i].mapdata, mapdata[i].walldata, mapdata[i].triggerdata, i);
			for (int j = 0; j < 10; j++) {
				maps[i].setnext(j, &maps[mapdata[i].next[j]]);
			}
		}
		SDL_RWread(file, &chadata, 4 * sizeof(int), 1);
		cha.setatk(chadata[0]);
		cha.sethp(chadata[1]);
		cha.setmposx(chadata[2]);
		cha.setmposy(chadata[3]);
		SDL_RWread(file, &talkstate, 100 * sizeof(int), 1);
		SDL_RWread(file, &monsterhp, 100 * sizeof(int), 1);
		SDL_RWclose(file);
	}
}

void savedata() {
	SDL_RWops* file = SDL_RWFromFile("testsave.bin", "w+b");
	if (file != NULL) {
		SDL_RWwrite(file, &maptotal[0], sizeof(int), 1);
		currentmap[0] = sceneTexture.getnum();
		SDL_RWwrite(file, &currentmap[0], sizeof(int), 1);
		for (int i = 0; i < maptotal[0]; i++) {
			SDL_RWwrite(file, &mapdata[i].mapdata, 150 * sizeof(int), 1);
			SDL_RWwrite(file, &mapdata[i].walldata, 150 * sizeof(int), 1);
			SDL_RWwrite(file, &mapdata[i].triggerdata, 150 * sizeof(int), 1);
			SDL_RWwrite(file, &mapdata[i].next, 10 * sizeof(int), 1);

		}
		chadata[0] = cha.getatk();
		chadata[1] = cha.gethp();
		chadata[2] = cha.getmposx();
		chadata[3] = cha.getmposy();
		SDL_RWwrite(file, &chadata, 4 * sizeof(int), 1);
		SDL_RWwrite(file, &talkstate, 100 * sizeof(int), 1);
		SDL_RWwrite(file, &monsterhp, 100 * sizeof(int), 1);
		SDL_RWclose(file);
	}
}


//MapTexture outTexture = MapTexture(mapdata1,walldata1,triggerdata1,0);
//MapTexture inTexture = MapTexture(mapdata2, walldata2, triggerdata2,1);
//MapTexture outTexture2 = MapTexture(mapdata3, walldata3, triggerdata3,2);
//void bound() {
//	//outTexture.setnext(0,&inTexture);
//	//outTexture.setnext(1, &outTexture2);
//	//inTexture.setnext(0,&outTexture);
//	//outTexture2.setnext(1, &outTexture);
//	//mapdata[0] = mapdata1;
//}
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

	ifstream f("loadconfig.txt");
	for (int i = 0; i < 10; i++) {
		getline(f, loadconfig[i]);
	}
	f.close();

	if (!sceneTexture.loadFromFile(renderer, loadconfig[0].c_str()))
	{
		std::cout << "加载场景图片失败" << std::endl;
		success = false;
	}

	if (!cha.loadFromFile(renderer, loadconfig[1].c_str()))
	{
		std::cout << "加载人物图片失败" << std::endl;
		success = false;
	}

	if (!Talk::loadbackFromFile(renderer, loadconfig[2].c_str())) {
		cout << "加载对话背景图片失败" << endl;
		success = false;
	}

	if (!attackui.loadpicFromFile(renderer, loadconfig[3].c_str())) {
		cout << "加载攻击按钮图片失败" << endl;
		success = false;
	}

	if (!newgame.loadpicFromFile(renderer, loadconfig[4].c_str())) {
		cout << "加载新游戏按钮图片失败" << endl;
		success = false;
	}

	if (!continuegame.loadpicFromFile(renderer, loadconfig[5].c_str())) {
		cout << "加载继续游戏按钮图片失败" << endl;
		success = false;
	}
	
	if (!mainhpui.loadpicFromFile(renderer, loadconfig[6].c_str())) {
		cout << "加载主页血条图片失败" << endl;
		success = false;
	}

	if (!titlepic.loadpicFromFile(renderer, loadconfig[7].c_str())) {
		cout << "加载主页标题图片失败" << endl;
		success = false;
	}

	font = TTF_OpenFont(loadconfig[8].c_str(), 30);
	font2 = TTF_OpenFont(loadconfig[9].c_str(), 20);
	if (!font) {
		cout << "加载字体文件失败" << endl;
		success = false;
	}

	if (!bgw.loadtextFromFont(font, renderer, bgwtext, bgwcolor)) {
		cout << "加载背景文本失败" << endl;
		success = false;
	}

	if (!title.loadtextFromFont(font, renderer, titletext, bgwcolor)) {
		cout << "加载标题文本失败" << endl;
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


	int r = bgw.settextAlpha(63);
	return success;
}

bool loadmonster() {
	string ms[20][5];
	string montotalstr;
	int montotal;
	ifstream f("monstertype.txt");
	getline(f, montotalstr);
	montotal = atoi(montotalstr.c_str());
	for (int i = 0; i < montotal; i++) {
		for (int j = 0; j < 5; j++) {
			getline(f, ms[i][j]);
			if (j == 0) {
				monstertype[i].setnum(atoi(ms[i][j].c_str()));
			}
			if (j == 1) {
				monstertype[i].setatk(atoi(ms[i][j].c_str()));
			}
			if (j == 3) {
				monstertype[i].setname(&ms[i][j]);
			}
			if (j == 4) {
				monstertype[i].sethp(atoi(ms[i][j].c_str()));
			}
		}
	}
	bool success = true;
	for (int i = 0; i < montotal; i++) {
		if (!monstertype[i].loadFromFile(renderer, ms[i][2].c_str())) {
			cout << "怪物图片载入失败" << endl;
			success = false;
		}
	}
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			monsterhp[i][j] = monstertype[monsterpos[i][j]].gethp();
		}
	}
	//if (!slime.loadFromFile(renderer, "slime.png")) {
	//	cout << "史莱姆图片载入失败" << endl;
	//	success = false;
	//}
	//if (!littlemonkey.loadFromFile(renderer, "littlemonkey.png")) {
	//	cout << "成哥图片载入失败" << endl;
	//	success = false;
	//}
	//monster[10] = slime;
	//monster[11] = littlemonkey;
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
	chahpstr = to_string(cha.gethp());
	mainhpui.free();
	mainhpui.loadtextFromFont(font2, renderer, chahpstr, maincolor);
	mainhpui.setpicAlpha(125);
	mainhpui.renderpic(renderer);
	mainhpui.rendertext(renderer);
	bgw.rendertext(renderer);
	SDL_RenderPresent(renderer);
}

void close()
{
	savedata();
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
	//bound();
	initmaps();
	inittalk();
	
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
				bool startnew = true;
				startnew = mainmenu(quit, e);
				if (!startnew) {
					loaddata();
				}

				int wallnum = sceneTexture.initmap(maps[currentmap[0]]);
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

					if (jump < 10) {
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
						int currentm = sceneTexture.getnum();
						int currentt = jump - 10;
						int talknum = currentm * 10 + currentt;
						while (SDL_PollEvent(&e) != 0)
						{
							if (e.type == SDL_QUIT)
							{
								quit = true;
							}
							cha.handleEvent(e);
							jump = talk[talknum].handleEvent(e, jump);
						}
						/*if (!talk[talknum].getstate() && cha.gethp() < 115) {*/
						if (talkstate[currentm][currentt] == 0) {
							if (jump == 100) {
								talkstate[currentm][currentt] = 1;
							}
							talk[talknum].free();
							talk[talknum].loadtalkFromFont(font, renderer, talklist[currentm][currentt][0], talkcolor);
							
							talk[talknum].render(renderer);
							SDL_RenderPresent(renderer);
						}
						if(talkstate[currentm][currentt] == 1) {
							if (talknum == 21) {
								maps[0].mapdata[6][6] = 11;
								maps[0].walldata[6][6] = 0;
							}
							talk[talknum].free();
							talk[talknum].loadtalkFromFont(font, renderer, talklist[currentm][currentt][1], talkcolor);
							talk[talknum].render(renderer);
							SDL_RenderPresent(renderer);
						}
						/*if (talk[talknum].getstate() && cha.gethp() >= 115) {
							talk[talknum].free();
							talk[talknum].loadtalkFromFont(font, renderer, congratulation, talkcolor);
							talk[talknum].render(renderer);
							SDL_RenderPresent(renderer);
						}
						if (!talk[talknum].getstate() && cha.gethp() >= 115) {
							talk[talknum].free();
							talk[talknum].loadtalkFromFont(font, renderer, secretachievement, talkcolor);
							talk[talknum].render(renderer);
							SDL_RenderPresent(renderer);
						}*/
					}

					else if (jump >= 20 && jump < 30) {
						int montype = monsterpos[sceneTexture.getnum()][ jump - 20];
						if (monsterhp[sceneTexture.getnum()][jump - 20] > 0) {
							bool over = false;
							monster.sethp(monsterhp[sceneTexture.getnum()][jump - 20]);
							monster.setatk(monstertype[montype].getatk());
							cout << montype << endl;
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
									atk = attackui.handleEvent(e);
								}
								charahpui.free();
								monsterhpui.free();
								monsternameui.free();
								fight.free();
								fight.loadFromFile(renderer, "fight.png");
								fight.render(renderer);
								attackui.renderbutton(renderer);
								int x = cha.getmposx();
								int y = cha.getmposy();
								cha.setmposx(64);
								cha.setmposy(180);
								cha.render(renderer);
								monstertype[montype].render(renderer);
								chahpstr = to_string(cha.gethp());
								monhpstr = to_string(monster.gethp());
								charahpui.loadtextFromFont(font2, renderer, chahpstr, talkcolor);
								monsterhpui.loadtextFromFont(font2, renderer, monhpstr, talkcolor);
								monsternameui.loadtextFromFont(font, renderer, *monstertype[montype].getname(), talkcolor);
								charahpui.rendertext(renderer);
								monsterhpui.rendertext(renderer);
								monsternameui.rendertext(renderer);
								SDL_RenderPresent(renderer);
								over = fight.fightprocess(&cha, &monster, atk, over);
								monsterhp[sceneTexture.getnum()][jump - 20] = monster.gethp();
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