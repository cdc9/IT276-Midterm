#ifndef _RESOURCES_
#define _RESOURCES_
//Surfaces, entities, flags, and other stuff
typedef enum { false, true} bool;
//Flags for confirming things
#define ENTFLAG_SHOW	0x00000001
#define ENTFLAG_THINK	0x00000002
#define ENT_SOLID		0x00000004

//SDL_Rect stuff
extern SDL_Rect camera;
//extern SDL_Rect platform1; 

//Stuff that gets drawn to the screen.
extern SDL_Surface *screen;	
extern SDL_Surface *background;
extern SDL_Surface *message;
extern SDL_Surface *playerSprite;


//SDL Events
extern SDL_Event event;
//Font stuff
extern TTF_Font *font;
extern SDL_Color textColor;

//Frame rate stuff
extern int frameCount;

//Manipulating Flag stuff
#define REMOVE_FLAG(x, y) (x &= ~y)
#define SET_FLAG(x, y) (x |= y)
#define IS_SET(x, y) (x & y)
#endif