#ifndef _GFUNC_
#define _GFUNC_
#include "includer.h"

/* Header file for game functions (loading, clearing, etc.) */

bool init();
bool load_Files();
void CheckLevel();
void clear();
//char* FormatTimeString(Uint32 offset);
//char* timeString(Uint32 offset);
int level;

//void set_Clips();
#endif