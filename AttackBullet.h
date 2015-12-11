#include <SDL/SDL.h>
#include <iostream>
#include <vector>

#ifndef BULLET_H
#define BULLET_H

class AttackBullet {
	SDL_Rect container;
	int xVelocity;
	int yVelocity;
	SDL_Surface* surfaceContainer;
	public:
	AttackBullet(SDL_Surface* img, int x, int y, int xVel, int yVel);
	~AttackBullet();
	SDL_Rect* getContainer();
	void move();
	void draw(SDL_Surface *screen);
};

#endif
