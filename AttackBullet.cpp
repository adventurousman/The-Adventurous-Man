#include "AttackBullet.h"

AttackBullet::AttackBullet(SDL_Surface* img, int x, int y, int xVel, int yVel)
{
	surfaceContainer =img;
	container.x=x;
	container.y=y;
	container.w= surfaceContainer->clip_rect.w;
	container.h= surfaceContainer->clip_rect.h;
	xVelocity =xVel;
	yVelocity =yVel;
}

AttackBullet::~AttackBullet()
{
	SDL_FreeSurface(surfaceContainer);
}

SDL_Rect*AttackBullet::getContainer()
{
	return &container;
}

void AttackBullet::move()
{
	container.x+= xVelocity;
	container.y+= yVelocity;
}

void AttackBullet::draw(SDL_Surface *screen)
{
	SDL_BlitSurface(surfaceContainer, NULL, screen, &container);
}
