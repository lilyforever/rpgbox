#ifndef _MAP_H_
#define _MAP_H_
#include <string>
#include <SDL.h>
#include <SDL_image.h>

class MapTexture {
public:
	//���캯��
	MapTexture();
	MapTexture(int(*m)[15], int(*w)[15], SDL_Rect* p, SDL_Rect* b);
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
	SDL_Rect* getp();
	SDL_Rect* getb();
	SDL_Rect* getwall();
	void setwallnum(int w);
	int getwallnum();
	//int** getmapdata();
	int(*mapdata)[15];
	int(*walldata)[15];
	MapTexture* getnext();
	void setnext(MapTexture* m);
private:
	//��ǰ��texture
	SDL_Texture* mTexture;
	//ͼƬ�ĳߴ�
	int mWidth;
	int mHeight;

	SDL_Rect* portal;
	SDL_Rect* birth;
	SDL_Rect wall[150];
	int wallnum;
	MapTexture* next;
};
#endif