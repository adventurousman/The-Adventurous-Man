#include <iostream>
#include <fstream>
#include <vector>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "BaseUtil.h"
#include "CPlayer.h"
#include "AttackBullet.h"
#include "CEnemy.h"
#include <SDL/SDL_image.h>

#ifndef GAME_H
#define GAME_H

using namespace std;

class CApp : public BaseUtil {
private:
	SDL_Rect camera;	//the coordinate of the CApp
	std::vector<std::vector<int> > tileMap;
	std::vector<CEnemy *> enemies;

	SDL_Surface* blocks,*screen,*background;

	bool running;
	bool playerDirection[2];
	CPlayer *mainPlayer;
	std::vector<AttackBullet *> bullets;
	TTF_Font* font;
	SDL_Rect finalDestination;

public:
	SDL_Surface* loadImageFromFile(const char *c);

	void loadMap(const char *c);
	void showMap();
	void eventHandler();
	static const int SCREEN_WIDTH = 640;
	static const int SCREEN_HEIGHT = 480;
	CApp();
	~CApp();
	void start();
	int showMenu(SDL_Surface *);
	void showMessage(const char* c);
	CPlayer* getPlayer();
};

#endif
