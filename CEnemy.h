#include <SDL/SDL.h>
#include <vector>
#include <iostream>
#include "BaseUtil.h"
#ifndef ENEMY_H
#define ENEMY_H

class CEnemy : public BaseUtil {
private:
	SDL_Rect enemyContainer;
	double xVelocity;
	double yVelocity;
	SDL_Surface* displayImage;
	int attack;
	bool onGround;
	SDL_Rect frames[2];
	double currentFrame;

public:
	CEnemy(SDL_Surface* img, int x, int y, int xVel, int yVel);
	~CEnemy();
	SDL_Rect* getContainer();
	void move(std::vector<std::vector<int> >&);
	void displaySurface(SDL_Surface *);
	double getXVel();
	void setXVel(double);
};

#endif
