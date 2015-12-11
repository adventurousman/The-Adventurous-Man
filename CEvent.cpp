//
// Created by hoang on 12/9/15.
//
#include "CApp.h"
#include "AttackBullet.h"

void CApp::eventHandler() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                running = false;
                return;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_LEFT:
                        playerDirection[0] = 1;
                        mainPlayer->setMoving(1);
                        break;
                    case SDLK_RIGHT:
                        playerDirection[1] = 1;
                        mainPlayer->setMoving(1);
                        break;
                    case SDLK_SPACE:
                        mainPlayer->jump();
                        break;
                    case SDLK_f:
                        if (mainPlayer->getPlayerDirection() == 'r')
                            bullets.push_back(new AttackBullet(loadImageFromFile("bullet.bmp"),
                                                               mainPlayer->getContainer()->x + mainPlayer->getContainer()->w,
                                                               mainPlayer->getContainer()->y + 13, 5, 0));
                        else
                            bullets.push_back(new AttackBullet(loadImageFromFile("bullet.bmp"), mainPlayer->getContainer()->x,
                                                               mainPlayer->getContainer()->y + 13, -5, 0));
                        break;
                    case SDLK_ESCAPE:
                        int g = showMenu(screen);
                        if (g == 1) {
                            //							mapcreator mc;
                            //							mc.start();
                            showMessage("Not implemented");
                            SDL_Delay(1000);
                        } else if (g == 2)
                            running = false;
                        break;
                }
                break;
            case SDL_KEYUP:
                switch (event.key.keysym.sym) {
                    case SDLK_LEFT:
                        playerDirection[0] = 0;
                        mainPlayer->setMoving(0);
                        break;
                    case SDLK_RIGHT:
                        mainPlayer->setMoving(0);
                        playerDirection[1] = 0;
                        break;
                }
                break;
        }
    }
}

