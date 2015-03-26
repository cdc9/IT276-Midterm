#ifndef _SPRITES_
#define _SPRITES_
//SDL libraries and such
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <stdlib.h>


//My header files
#include "gfunc.h"
#include "entity.h"
#include "resources.h"

//Screen attributes
#define SCREEN_WIDTH	640
#define SCREEN_HEIGHT	480
#define SCREEN_BPP		32

//Level attributes
#define LEVEL_WIDTH		1920
#define LEVEL_HEIGHT	1200

/* Load Image from file function:  Takes an image by filename and optimizes it for the screen */
SDL_Surface *load_Image (char *filename);

//Apply images to the screen
void apply_surface (float x, float y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip);
#endif 