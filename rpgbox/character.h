#ifndef _CHARACTER_H_
#define _CHARACTER_H_
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include "collision.h"
#include "map.h"
class Character {
public:
	static const int CHA_WIDTH = 32;
	static const int CHA_HEIGHT = 32;
	//static const int CHA_V = 1;

	Character();
	~Character();
	bool loadFromFile(SDL_Renderer* renderer, std::string path);
	void free();
	void handleEvent(SDL_Event& e);
	bool move(int screenwidth, int screenheight, MapTexture* m, bool jump);
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

};
#endif