#ifndef _MONSTER_H_
#define _MONSTER_H_
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include "collision.h"
#include <iostream>
using namespace std;
class Monster {
public:
	static const int MON_WIDTH = 64;
	static const int MON_HEIGHT = 64;
	Monster();
	Monster(int hp, int atk, string n);
	~Monster();
	void free();
	bool loadFromFile(SDL_Renderer* renderer, string path);
	void render(SDL_Renderer* renderer);
	int gethp();
	void sethp(int i);
	int getnum();
	void setnum(int i);
	int getatk();
	void setatk(int i);
	string* getname();
	void setname(string* n);
private:
	SDL_Texture * mTexture;
	int m_posx;
	int m_posy;
	int mWidth;
	int mHeight;
	int hp;
	int atk;
	int monnum;
	string name;
};

#endif
