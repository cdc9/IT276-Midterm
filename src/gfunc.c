//This class handles the functions for the game
#include "includer.h"

bool init()
{
	/* start SDL 1.2 */
	if ( SDL_Init(SDL_INIT_EVERYTHING) == -1 )
	{
		return false;
	}

	/* fonts for text */
	if ( TTF_Init() == -1 )
	{
		return false;
	}

	/* Fourth argument creates the screens surface in system memory */
	screen = SDL_SetVideoMode (SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
	if (screen == NULL)
	{
		return false;
	}

	/* Window title */
	SDL_WM_SetCaption ("Midterm Game", NULL);

	/* If nothing's wrong, return true. */
	return true;
}

/* Loads all files in one function, foreshadow to precaching? */
bool load_Files()
{
	/* lvl 1 sprites */
	background = load_Image("level1.png");
	if (background == NULL)
	{
		return false;
		printf("error: %s\n", SDL_GetError());
	}

	// player sprite 
	dot = load_Image(".bmp");
	if (player == NULL)
	{
		return false;
		printf("error: %s\n", SDL_GetError());
	}

	/* font */
	font = TTF_OpenFont ("font/lazy.ttf", 28);
	if (font == NULL)
	{
		return false;
		printf("error: %s\n", SDL_GetError());
	}

	return true;
}

void set_Camera (entity_t *ent)
{
	 //Center the camera over the player 
	camera.x = ( (int)ent->x + ent->width / 2) - SCREEN_WIDTH / 2;
	camera.y = ( (int)ent->y + ent->height / 2) - SCREEN_HEIGHT / 2;

	if ( camera.x < 0 )
		camera.x = 0;
	if ( camera.y < 0 )
		camera.y = 0;
	if ( camera.x > LEVEL_WIDTH - camera.w)
		camera.x = LEVEL_WIDTH - camera.w;
	if ( camera.y > LEVEL_HEIGHT - camera.h )
		camera.y = LEVEL_HEIGHT - camera.h;
}

/* for program exiting, cleaning and freeing up memory */
void clear()
{
	//Free the memory
	SDL_FreeSurface (background);
	SDL_FreeSurface (dot);

	/* Closing the fonts and text engine */
	TTF_CloseFont (font);
	TTF_Quit();

	//Will free the screen surface and close SDL
	SDL_Quit();
}