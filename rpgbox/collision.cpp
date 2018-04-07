#include "collision.h"

bool checkCollision(SDL_Rect a, SDL_Rect b) {
	int al, ar, at, ab, bl, br, bt, bb;
	al = a.x;
	ar = a.x + a.w;
	at = a.y;
	ab = a.y + a.h;
	bl = b.x;
	br = b.x + b.w;
	bt = b.y;
	bb = b.y + b.h;
	if (ab <= bt || at >= bb || ar <= bl || al >= br) {
		return false;
	}
	return true;
}