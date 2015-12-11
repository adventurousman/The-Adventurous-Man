#include "BaseUtil.h"

bool BaseUtil::collisionHandler(SDL_Rect *rec1, SDL_Rect *rec2)
{
	if(rec2->y+rec2->h <= rec1->y)
		return 0;
	if(rec2->x + rec2->w <= rec1->x)
		return 0;
	if(rec1->y + rec1->h <= rec2->y)
		return 0;
	if(rec1->x + rec1->w <= rec2->x)
		return 0;
	return 1;
}
