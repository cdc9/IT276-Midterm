//SDL libraries and such
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <stdlib.h>

#include "resources.h"
//My header files
#include "sprites.h"
#include "gfunc.h"
#include "entity.h"
#include "globals.h"
//Creating surfaces. Stuff the player will see.
SDL_Surface *screen = NULL;
SDL_Surface *background = NULL;
SDL_Surface *message = NULL;
SDL_Surface *playerSprite;

//SDL_Rect
//SDL_Rect platform1; 

//Font stuff.
TTF_Font *font = NULL;
SDL_Color textColor = { 255, 255, 255 };

//Frame rate stuff.
int frameCount;

//Creating the Camera
SDL_Rect camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

//SDL event stuff
SDL_Event event;

//Creating entities to use throughout code
entity_t *player = NULL;
entity_t *ground = NULL;
