#include "map.h"
#include "character.h"
#include "talk.h"
#include "fight.h"
#include "ui.h"
#include "monster.h"

//������main����

using namespace std;

const int SCREEN_WIDTH = 480;
const int SCREEN_HEIGHT = 320;
const int PIXEL_WIDTH = 32;
const int PIXEL_HEIGHT = 32;



//[6][6]����ʯͷ,[6][6]ԭ����11ɳ��
int mapdata1[10][15] = {
	18,18,18,17,18,18,18,18,18,18,18,55,55,55,18,
	18,17,18,17,17,17,17,17,17,17,17,55,55,55,18,
	18,17,17,17,17,17,18,18,17,17,17,55,55,55,18,
	18,17,17,17,18,18,18,18,18,17,17,55,55,17,18,
	18,17,17,18,22,23,23,23,24,18,17,21,21,17,18,
	18,17,17,18,25,28,26,79,27,18,55,55,55,17,18,
	18,17,17,18,18,10,72,12,17,18,55,55,17,68,18,
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
	1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 1, 1, 0, 0, 1,
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
	0, 0, 0, 0, 0, 0, 31, 0, 0, 0, 0, 0, 0, 11, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};

int mapdata2[10][15] = {
	0,0,1,2,2,2,2,2,2,2,2,1,0,0,0,
	0,0,1,3,5,5,1,3,5,5,5,1,0,0,0,
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
	0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,
	0,1,1,0,0,0,0,0,0,0,1,1,1,1,1,
	0,0,0,1,1,1,1,0,1,1,1,1,1,1,1,
	1,1,0,0,1,1,1,1,1,1,1,1,1,1,1
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
	0, 0, 0, 22, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
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
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1,
	1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1
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
	0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 12, 0, 0, 0,
};

SDL_Window* window = NULL;

SDL_Renderer* renderer = NULL;

TTF_Font* font = NULL;
TTF_Font* font2 = NULL;

string bgwtext = "RPGBOX";
SDL_Color bgwcolor = { 255,255,255 };
MapTexture sceneTexture;
Ui bgw = Ui(80, 200, 400, 120);
Talk talk[30];
Monster monster[30];

//��������
Monster slime(20, 1, "slime");
Monster littlemonkey(30, -1, "littlemonkey");


SDL_Color talkcolor = { 0,0,0, };
SDL_Color maincolor = { 255,255,0, };
Character cha;
Fight fight;
SDL_Rect sceneClips[100];

Ui charahp = Ui(32, 128, 64, 32);
Ui mainhp = Ui(0, 0, 64, 32);
string chahpstr;
Ui monsterhp = Ui(384, 128, 64, 32);
string monhpstr;
Ui monstername = Ui(384, 96, 64, 32);
Ui attack = Ui(160, 180, 160, 64);

//string map3str[20] = { "hello, adventure!","ok, i will help you~","", "", "", "", "", "", "", "",
//									"can you disappear the stone?", "the stone has been disappeared!", "", "", "", "", "", "", "", "", };

string mapstr[60] = {
"you are too weak!","","", "", "", "", "", "", "", "",
"be stronger plzzz", "", "", "", "", "", "", "", "", "",
"", "", "", "", "", "", "", "", "", "",
"", "", "", "", "", "", "", "", "", "",
"hello, adventure!", "ok, i will help you~", "", "", "", "", "", "", "", "",
"can you disappear the stone?", "the stone has been disappeared!", "", "", "", "", "", "", "", "", };
string congratulation = "fine, congratulations~!";
string secretachievement = "o, niupi.";


MapTexture outTexture = MapTexture(mapdata1,walldata1,triggerdata1,0);
MapTexture inTexture = MapTexture(mapdata2, walldata2, triggerdata2,1);
MapTexture outTexture2 = MapTexture(mapdata3, walldata3, triggerdata3,2);

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
		cout << "SDL��ʼ��ʧ��" << endl;
		success = false;
	}
	else
	{
		window = SDL_CreateWindow("rpgbox test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			cout << "���ڴ���ʧ��" << endl;
			success = false;
		}
		else
		{
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			if (renderer == NULL)
			{
				cout << "��Ⱦ������ʧ��" << endl;
				success = false;
			}
		}
		if (TTF_Init() == -1)
		{
			cout << "������ʼ��ʧ��" << endl;
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
		std::cout << "���س���ͼƬʧ��" << std::endl;
		success = false;
	}

	if (!cha.loadFromFile(renderer, "cha.png"))
	{
		std::cout << "��������ͼƬʧ��" << std::endl;
		success = false;
	}

	font = TTF_OpenFont("123.ttf",30);
	font2 = TTF_OpenFont("lazy.ttf", 20);
	if (!font) {
		cout << "���������ļ�ʧ��" << endl;
		success = false;
	}

	if (!bgw.loadtextFromFont(font, renderer, bgwtext, bgwcolor)) {
		cout << "���ر����ı�ʧ��" << endl;
		success = false;
	}

	if (!Talk::loadbackFromFile(renderer, "back.png")) {
		cout << "���ضԻ�����ͼƬʧ��" << endl;
		success = false;
	}

	if (!attack.loadpicFromFile(renderer, "fightbutton.png")) {
		cout << "���ذ�ťͼƬʧ��" << endl;
		success = false;
	}
	
	if (!mainhp.loadpicFromFile(renderer, "mainuihp.png")) {
		cout << "������ҳѪ��ͼƬʧ��" << endl;
		success = false;
	}

	//��ԭ��ĳ���ͼƬ�и��100�ݣ�ÿ��32*32
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
	bool success = true;
	if (!slime.loadFromFile(renderer, "slime.png")) {
		cout << "ʷ��ķͼƬ����ʧ��" << endl;
		success = false;
	}
	if (!littlemonkey.loadFromFile(renderer, "littlemonkey.png")) {
		cout << "�ɸ�ͼƬ����ʧ��" << endl;
		success = false;
	}
	monster[10] = slime;
	monster[11] = littlemonkey;
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
	mainhp.free();
	mainhp.loadtextFromFont(font2, renderer, chahpstr, maincolor);
	mainhp.setpicAlpha(125);
	mainhp.renderpic(renderer);
	mainhp.rendertext(renderer);
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
		cout << "��ʼ��ʧ��" << endl;
	}
	else
	{
		if (!loadScene())
		{
			cout << "���ض�ý���ļ�ʧ��" << endl;
		}
		else
		{
			if (!loadmonster()) {
				cout << "���ع����ļ�ʧ��" << endl;
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

					if (jump < 10) {
						wallnum = sceneTexture.initmap(*sceneTexture.getnext(jump));
						cha.setmposx(sceneTexture.getb(jump)->x);
						cha.setmposy(sceneTexture.getb(jump)->y);
						cout << "���ͳɹ�" << endl;
						for (int i = 0; i < 30; i++) {
							trigger[i] = sceneTexture.gett(i);
						}
						wall = sceneTexture.getwall();
						jump = 100;

						renderscreen();
					}

					else if (jump >= 10 && jump < 20) {
						int talknum = sceneTexture.getnum() * 10 + jump - 10;
						int talkpos = sceneTexture.getnum() * 20 + jump - 10;
						while (SDL_PollEvent(&e) != 0)
						{
							if (e.type == SDL_QUIT)
							{
								quit = true;
							}
							cha.handleEvent(e);
							jump = talk[talknum].handleEvent(e, jump);
						}
						if (!talk[talknum].getstate() && cha.gethp() < 115) {
							if (jump == 100) {
								talk[talknum].setstate(true);
							}
							talk[talknum].free();
							talk[talknum].loadtalkFromFont(font, renderer, mapstr[talkpos], talkcolor);
							
							talk[talknum].render(renderer);
							SDL_RenderPresent(renderer);
						}
						if(talk[talknum].getstate() && cha.gethp() < 115) {
							if (talknum == 21) {
								outTexture.mapdata[6][6] = 11;
								outTexture.walldata[6][6] = 0;
							}
							talk[talknum].free();
							talk[talknum].loadtalkFromFont(font, renderer, mapstr[talkpos+10], talkcolor);
							talk[talknum].render(renderer);
							SDL_RenderPresent(renderer);
						}
						if (talk[talknum].getstate() && cha.gethp() >= 115) {
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
						}
					}

					else if (jump >= 20 && jump < 30) {
						int monsternum = sceneTexture.getnum() * 10 + jump - 20;
						if (monster[monsternum].gethp() > 0) {
							bool over = false;
							cout << monsternum << endl;
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
								monstername.free();
								fight.free();
								fight.loadFromFile(renderer, "fight.png");
								fight.render(renderer);
								attack.renderbutton(renderer);
								int x = cha.getmposx();
								int y = cha.getmposy();
								cha.setmposx(64);
								cha.setmposy(180);
								cha.render(renderer);
								monster[monsternum].render(renderer);
								chahpstr = to_string(cha.gethp());
								monhpstr = to_string(monster[monsternum].gethp());
								charahp.loadtextFromFont(font2, renderer, chahpstr, talkcolor);
								monsterhp.loadtextFromFont(font2, renderer, monhpstr, talkcolor);
								monstername.loadtextFromFont(font, renderer, *monster[monsternum].getname(), talkcolor);
								charahp.rendertext(renderer);
								monsterhp.rendertext(renderer);
								monstername.rendertext(renderer);
								SDL_RenderPresent(renderer);
								over = fight.fightprocess(&cha, &monster[monsternum], atk, over);
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