#ifndef _ENTITY_
#define _ENTITY_
//SDL libraries and such


#define MAX_ENTITIES  510 //max number that can be created
int max_ents; //max number of ents that have been created in game

typedef struct entity_s
{
	//If entity is being used
	int				used;
	//Postion of entity
	float			x,y;
	//Velocity of entity
	float			xVel, yVel;

	//Bounding box. Used for collision
	SDL_Rect		bBox;
	//The sprite of the entity
	SDL_Surface		*sprite;

	//The width and height of entity
	int				width;
	int				height;

	//Checking if entity is on ground or not
	bool			onGround;

	//Used to "tag" the entity. Sort of like in Unity.
	char			classname[25];


	long flags;
	//These are functions that Entity can use
	struct entity_s	*owner;

	void			(*resetPosition) (struct entity_s *ent);
	void			(*handle_Input)(struct entity_s *ent);
	void			(*move)(struct entity_s *ent);
	void			(*show)(struct entity_s *ent);
	void			(*setCamera)(void);
} entity_t; //Entity type. Use this to access all this stuff.

//More functions for the entity to use.
//Entity creation
entity_t *Init_Ent (void);		// adds entity into memory
void Free_Ent(entity_t *self);	// entity is ready to be replaced

//Collision stuff
void CheckCollisions();
void CheckCollision(entity_t *ent, entity_t *otherEnt, int max_ents);
bool isCollide(entity_t *otherEnt, entity_t *ent);

//Entity movement/position
void init_Position( entity_t *ent );
void handle_Input( entity_t *ent );
void move( entity_t *ent );
void show( entity_t *ent );

//camera stuff
void set_Camera( entity_t *ent);

#endif