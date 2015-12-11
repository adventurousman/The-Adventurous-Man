#ifndef BASE_H
#define BASE_H
#include <SDL/SDL.h>

class BaseUtil {
	protected:
		bool collisionHandler(SDL_Rect *, SDL_Rect *);
	public:
		static SDL_Rect Coordinator;
		static const int TILE_SIZE = 50;
};
#endif
