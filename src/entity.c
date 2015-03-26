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

entity_t entityArray [MAX_ENTITIES];
SDL_Event event;
//Initializes the entity into memory
entity_t *Init_Ent (void)
{
	int i;
	//Entity pointer
	entity_t *ent;

	//Travel through the entity array
	for (i = 0; i < max_ents+1; i++)
	{
		//if there is free memory in list
		if(entityArray[i].used == 0)
		{
			//Look at entity itself, not it's point in memory
			ent = &entityArray[i];
			//Set it to being used
			ent->used = 1;
			//Continue through the entity array.
			max_ents++;
		}
		//if there is memory at end of list
		else if (max_ents < MAX_ENTITIES) 
		{
			//Go to the next spot in the in the entity list and set it to being used.
			ent = &entityArray[max_ents++];
			ent->used = 1;
		}
		//if there is not enough slots for memory to be used, give an error
		else if(i == max_ents) 
		{
			fprintf(stderr, "Not enough memory!", SDL_GetError());
			exit(1);
			return 0;
		}

		return ent;
	}
}

void Free_Ent(entity_t *self)
{
	//Set the entity to not being used
	self->used = 0;
}

void EntityShow ()
{
	int i = 0;
	//Entity pointer to array
	entity_t *e = entityArray;
	//Travel through the array
	for (i = 0; i < MAX_ENTITIES; i++)
	{
		//If the entity is in use
		if (entityArray[i].used)
		{
			//If the show function is not NULL
			if (entityArray[i].show != NULL)
			{
				//Show it.
				(*entityArray[i].show)(&entityArray[i]);
			}
		}
		e++;
	}
}

//In-Game Entity
void init_Position (entity_t *ent)
{
	//The player's starting position
	ent->x = 0;
	ent->y = 350;
	
	//Player's velocity
	ent->xVel = 0;
	ent->yVel = 0;

	//Player width and height
	ent->width = 20;
	ent->height = 20;

	//Player's bounding box. Should be the same as the player's width and height
	ent->bBox.w = 20;
	ent->bBox.h = 20;

	
}

void handle_Input ( entity_t *ent )
{
	if (ent)
	{
		//If player hits a key
		if (event.type == SDL_KEYDOWN)
		{
			//Check which key the player picked and act accordingly
			switch (event.key.keysym.sym )
			{
				//Movement. Running left. Running right. Jumping.
				case SDLK_UP: ent->yVel -= 50; break; //Used to be ent->height decided to just put in a number
				case SDLK_LEFT: ent->xVel -= 10; break; //Used to be ent->width decided to just put in a number
				case SDLK_RIGHT: ent->xVel += 10; break; //Used to be ent->width decided to just put in a number
				
			}
		}
		//Once player releases the key, go in opposite direction to make them stop.
		else if ( event.type == SDL_KEYUP )
		{
			switch ( event.key.keysym.sym)
			{
				case SDLK_UP: ent->yVel += 50; break; //Should I get rid of this? So they won't stop in mid air and gravity will take over?
				case SDLK_LEFT: ent->xVel += 10; break;
				case SDLK_RIGHT: ent->xVel -= 10; break;
			}
		}
	}
}

void move ( entity_t *ent )
{
	//Move player left or right
	ent->x += ent->xVel;

	//If player went too far to the left or the right, keep him from moving off the screen
	if ( ( ent->x < 0 ) || ( ent->x + ent->width > LEVEL_WIDTH ) )
	{
		ent->x -= ent->xVel;
	}
	//If player went too far to the left or the right, keep him from moving off the screen
	ent->y += ent->yVel;
	
	if ( ( ent->y < 0 ) || ( ent->y + ent->height > LEVEL_HEIGHT ) )
	{
		ent->y -= ent->xVel;
	}
}

void show (entity_t *ent)
{
	//Show entity on screen.
	apply_surface (ent->x - camera.x, ent->y - camera.y, playerSprite, screen, NULL);
}

/*
void show_ground(entity_t *ent)
{
	//Show ground on screen
	apply_surface(ent ->x, ent->y, platform1, screen, NULL);
}
*/
void CheckCollisions()
{
	int i = 0;
	//Entity pointer to Array
	entity_t *e = entityArray;

	//Travel through array
	for (i = 0; i < MAX_ENTITIES; i++)
	{
	if (entityArray[i].used) //If it is being used...
		{
			//Flag to check if the collsion was between a solid object
			if (IS_SET(entityArray[i].flags, ENT_SOLID))
			{
				//If you have a velocity
				if (entityArray[i].xVel != 0 || entityArray[i].yVel != 0) 
				{
					//Call the other collision function
					CheckCollision(&entityArray[i], &entityArray[i+1], MAX_ENTITIES-i); 
					//ent is the cur, target is next, how many people are left
					//you checked in one direction, don't check in the other
				}

			}
		}
	}
	//if entity exists, is solid and has a velocity...
}
//Checking collision between two objects. Pass the postion in the entity list also.
void CheckCollision (entity_t *ent, entity_t *otherEnt, int max)
{
	int i = 0;
	//Entity pointer to array
	entity_t *e = entityArray; 

	//Traveling through the array
	for (i = 0; i < max; i++)
	{
		if (isCollide (otherEnt, ent)) //Call ANOTHER collision function
		{
			//Check the entity's "tag". If it a ground type, set onGround to true
			if (strcmp(otherEnt->classname, "ground") == 0) 
				ent ->onGround = true;
			else 
			{
				ent->x -= ent->xVel;
				ent->y -= ent->yVel;
			}
		}
		otherEnt++;
	}
}
/* Check Collision */
bool isCollide (entity_t *otherEnt, entity_t *ent) /* example: A = Enemy, B = Player */
{
	//Creating rectangles for collisions
	SDL_Rect A;
	SDL_Rect B;

	//Setting bounding boxes postion to the entity
	B.x = (Sint16)ent->x + ent->bBox.x;
	B.y = (Sint16)ent->y + ent->bBox.y;
	//Setting bounding boxes size to the entity
	B.w = ent->bBox.w;
	B.h = ent->bBox.h;

	//Setting other entity's bounding box to it's postion
	A.x =(Sint16)otherEnt->x + otherEnt->bBox.x;
	A.y = (Sint16)otherEnt->y + otherEnt->bBox.y;
	//Setting other entity's bounding box to it's postion
	A.w = otherEnt->bBox.w;
	A.h = otherEnt->bBox.h;

	//if one edge of A is greater than one edge of B, but the second edge is less then there second edge, it means there is a collision.
	//This goes for both the x and y. 
	if((A.x + A.w >= B.x) && (A.x <= B.x + B.w) && (A.y + A.h >= B.y) && (A.y <= B.y + B.h))
		return true; 

	return false;
}
//Checking to see if player is in the air
void inAir( entity_t *ent)
{
	//If onGround is false, force the player to fall to the ground
	if(ent -> onGround == false)
	{
		ent -> yVel += 10;
	}
}
