#ifndef PLAYER_H
#define PLAYER_H
#include <vector>
#include <iostream>
#include <SDL/SDL.h>
#include <cmath>
#include "AttackBullet.h"
#include "BaseUtil.h"

class CPlayer : public BaseUtil
{
private:
	SDL_Rect characterContainer;
	SDL_Surface* displayImage;
	int xVelocity;
	int yVelocity;
	SDL_Rect frames[4];
	double currentFrame;
	bool onGround;
	bool onJump;
	int lives;
	bool moving;
	char playerDirecion;

public:
	CPlayer(SDL_Surface*);
	~CPlayer();

	int getX();
	int getXVelocity();
	void setXVelocity(int);

	void displaySurface(SDL_Surface *);
	void onMove(const std::vector<std::vector<int> > &);
	void jump();

	SDL_Rect* getContainer();
	int getHealth();
	void setLives(int);
	void setDirection(const char dir);
	void setMoving(bool);
	char getPlayerDirection();
};
#endif
