#ifndef _MAP_H_
#define _MAP_H_
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include "loadimg.h"
class MapTexture {
public:
	//���캯��
	MapTexture();
	MapTexture(int(*m)[15], int(*w)[15], int (*t)[15]);
	//��������
	~MapTexture();
	//��ָ��·����ȡͼƬ
	bool loadFromFile(SDL_Renderer* renderer, std::string path);
	int initmap(MapTexture m);
	//����texture
	void free();
	//�Ը���������ʹ�С��Ⱦtexture
	void render(SDL_Renderer* renderer, int x, int y, SDL_Rect* clip = NULL);
	//�õ�ͼƬ�ĳߴ�
	int getWidth();
	int getHeight();
	SDL_Rect* getb(int i);
	SDL_Rect* getwall();
	SDL_Rect* gett(int i);
	void setwallnum(int w);
	int getwallnum();
	//int** getmapdata();
	int(*mapdata)[15];
	int(*walldata)[15];
	int(*triggerdata)[15];
	MapTexture* getnext(int i);
	void setnext(int i,MapTexture* m);
private:
	//��ǰ��texture
	SDL_Texture* mTexture;
	//ͼƬ�ĳߴ�
	int mWidth;
	int mHeight;
	SDL_Rect* trigger[30];
	SDL_Rect Trigger[30];
	SDL_Rect* birth[10];
	SDL_Rect Birth[10];
	SDL_Rect wall[150];
	int wallnum;
	MapTexture* next[10];
};
#endif