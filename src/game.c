//SDL libraries and such
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <stdlib.h>
#include "resources.h"


//My header files
#include "sprites.h"
//#include "gfunc.h"
#include "entity.h"
#include "globals.h"

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

	/* font */
	font = TTF_OpenFont ("lazy.ttf", 28);
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
	SDL_FreeSurface (message);

	/* Closing the fonts and text engine */
	TTF_CloseFont (font);
	TTF_Quit();

	//Will free the screen surface and close SDL
	SDL_Quit();
}

// Main function
int main(int argc, char *argv[])
{

	bool quit = false;
	
	// Start everything (SDL, open window, etc.), make sure done successfully 
	if ( init() == false)
	{
		return 1;
	}
	
	// Load all the files, check if done successfully 
	if ( load_Files() == false)
	{
		return 1;
	}

	//Player creation
	player = Init_Ent();
	player->resetPosition = init_Position;
	player->handle_Input = handle_Input;
	player->move = move;
	player->show = show;

	init_Position(player);

	SET_FLAG(player->flags, ENT_SOLID);

	//Ground creation
	ground = Init_Ent();
	sprintf(ground->classname, "ground");
	ground ->x = 0;
	ground ->y = 400;
	ground ->width = 400;
	ground ->height = 40;

	// GAME		
	do
	{
		while (SDL_PollEvent (&event))
		{
			handle_Input(player);

			//If the user presses Quit (the x button on the window)
			if(event.type == SDL_QUIT)
			{
				//Game is done
				quit = true;
			}

			move(player);
			set_Camera(player);
			show(player);
		}
		//Fill in player square
		//SDL_FillRect( screen, &playerSprite, SDL_MapRGB( screen->format, 0x77, 0x77, 0x77 ) );
		//Show the ground
        //SDL_FillRect( screen, &platform1, SDL_MapRGB( screen->format, 0x77, 0x77, 0x77 ) );

		 //Update the screen
        if( SDL_Flip( screen ) == -1 )
        {
            return 1;
        }
	}
	
	while(!quit);

	clear();

	exit(0);
	return 0;
}