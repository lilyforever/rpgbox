#ifndef _LOADIMG_H_
#define _LOADIMG_H_
#include "SDL.h"
#include "SDL_image.h"
#include <string>
bool loadtexture(SDL_Texture* mTexture, SDL_Renderer* renderer, std::string path);
#endif
