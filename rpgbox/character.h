#ifndef _CHARACTER_H_
#define _CHARACTER_H_
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include "collision.h"
#include "map.h"
#include "loadimg.h"
#include "SDL_mixer.h"
class Character {
public:
	//���Ǵ�СС�ڵ�ͼ��һ�񣬲����ڱ�Ե��������Ϊ��������ȥһ����·������
	static const int CHA_WIDTH = 31;
	static const int CHA_HEIGHT = 31;
	//static const int CHA_V = 1;

	Character();
	~Character();
	bool loadFromFile(SDL_Renderer* renderer, std::string path);
	void free();
	void handleEvent(SDL_Event& e);
	int move(int screenwidth, int screenheight, MapTexture* m, int jump, Mix_Chunk *w);
	void render(SDL_Renderer* renderer);
	void setname(char* n);
	void setsex(bool n);
	//void settype(int n);
	char* getname();
	bool getsex();
	double getmposx();
	double getmposy();
	void setmposx(int x);
	void setmposy(int y);
	int gethp();
	void sethp(int i);
	int getatk();
	void setatk(int i);
private:
	char* m_name;
	bool m_sex;
	//int m_type;
	SDL_Texture* mTexture;
	int mWidth;
	int mHeight;
	double m_posx, m_posy;
	double m_vx, m_vy;
	SDL_Rect mCollision;
	int hp;
	int atk;
};
#endif