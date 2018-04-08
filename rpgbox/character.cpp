#include "character.h"
#include "collision.h"
#include "map.h"
#include <iostream>
using namespace std;

const double CHA_V = 0.1;

Character::Character() {
	m_posx = 96;
	m_posy = 32;
	m_vx = 0;
	m_vy = 0;
	mCollision.w = CHA_WIDTH;
	mCollision.h = CHA_HEIGHT;
}

Character::~Character() {
	free();
}

bool Character::loadFromFile(SDL_Renderer* renderer, string path) {
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

void Character::free() {
	if (mTexture != NULL) {
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void Character::handleEvent(SDL_Event& e) {
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
		switch (e.key.keysym.sym) {
		case SDLK_w:m_vy -= CHA_V; cout << "press w" << endl; break;
		case SDLK_s:m_vy += CHA_V; cout << "press s" << endl; break;
		case SDLK_a:m_vx -= CHA_V; cout << "press a" << endl; break;
		case SDLK_d:m_vx += CHA_V; cout << "press d" << endl; break;
		}
	}
	if (e.type == SDL_KEYUP && e.key.repeat == 0) {
		switch (e.key.keysym.sym) {
		case SDLK_w:m_vy += CHA_V; break;
		case SDLK_s:m_vy -= CHA_V; break;
		case SDLK_a:m_vx += CHA_V; break;
		case SDLK_d:m_vx -= CHA_V; break;
		}
	}
}

int Character::move(int x,int y, MapTexture* m, int jump) {
	m_posx += m_vx;
	mCollision.x = m_posx;
	bool flag = true;

	/*if ((m_posx == m->gett()->x)&&m_posy == m->gett()->y) {
		jump = true;
		return jump;
	}*/
	for (int i = 0; i < 30; i++) {
		if (m->gett(i)) {
			if (checkCollision(mCollision, *m->gett(i))) {
				jump = i;
				return jump;
			}
		}
	}

	if ((m_posx < 0) || (m_posx + CHA_WIDTH > x)) {
		m_posx -= m_vx;
		mCollision.x = m_posx;
		flag = false;
	}

	if (flag) {
		for (int i = 0; i < m->getwallnum(); i++) {
			if (checkCollision(mCollision, m->getwall()[i])) {
				m_posx -= m_vx;
				mCollision.x = m_posx;
			}
		}
		flag = true;
	}

	m_posy += m_vy;
	mCollision.y = m_posy;

	/*if ((m_posx == m->gett()->x) && m_posy == m->gett()->y) {
		jump = true;
		return jump;
	}*/

	for (int i = 0; i < 30; i++) {
		if (m->gett(i)) {
			if (checkCollision(mCollision, *m->gett(i))) {
				jump = i;
				return jump;
			}
		}
	}

	if ((m_posy < 0) || (m_posy + CHA_HEIGHT > y)) {
		m_posy -= m_vy;
		mCollision.y = m_posy;
		flag = false;
	}

	if (flag) {
		for (int i = 0; i < m->getwallnum(); i++) {
			if (checkCollision(mCollision, m->getwall()[i])) {
				m_posy -= m_vy;
				mCollision.y = m_posy;
			}
		}
		flag = true;
	}
	return jump;

}

void Character::render(SDL_Renderer* renderer){
	SDL_Rect renderbox = { m_posx, m_posy, CHA_WIDTH, CHA_HEIGHT };
	SDL_Rect chabox = { 0,0,CHA_WIDTH,CHA_HEIGHT };

	SDL_RenderCopy(renderer, mTexture, &chabox, &renderbox);
}

void Character::setname(char* n) {
	m_name = n;
}

void Character::setsex(bool n) {
	m_sex = n;
}

//void Character::settype(int n) {
//	m_type = n;
//}

char* Character::getname() {
	return m_name;
}

bool Character::getsex() {
	return m_sex;
}

double Character::getmposx() {
	return m_posx;
}

double Character::getmposy() {
	return m_posy;
}

void Character::setmposx(int x) {
	m_posx = x;
}

void Character::setmposy(int y) {
	m_posy = y;
}