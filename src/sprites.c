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
// Load Image from file function
//We are going to take an image in as a parameter and return a pointer 
SDL_Surface *load_Image (char *filename)
{
	 //The image that's loaded
	SDL_Surface* loadedImage = NULL;

	//The optimized surface that will be used
	SDL_Surface* optimizedImage = NULL;

	// Getting the image from the file system and attaching an address to the pointer.
	loadedImage = IMG_Load(filename);

	//if the image loaded
	if( loadedImage != NULL)
	{
		//Create an optimized version of the image to the surface
		optimizedImage = SDL_DisplayFormat( loadedImage );
		
		//Free the old surface
		SDL_FreeSurface (loadedImage);

		//If the image was optimized
		if (optimizedImage != NULL)
		{
			//This creates a color key. Color key defines a color I wish to remove.
			Uint32 colorkey = SDL_MapRGB( optimizedImage->format, 0, 0xFF, 0xFF );
			
			//Gets rid of color in the first argument
			SDL_SetColorKey (optimizedImage, SDL_SRCCOLORKEY, colorkey);
		}
	}

	//returns pointer to the optimized image
	return optimizedImage;
}

// Displaying Image function 
void apply_surface (float x, float y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip)
{
	//Holds the offsets for the source
	SDL_Rect offset;

	//Get the offsets
	//We have to type cast the x and y into integers
	offset.x = (int)x;
	offset.y = (int)y;

	//Displaying (blitting) the image to the surface
	SDL_BlitSurface( source, clip, destination, &offset);
}