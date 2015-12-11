#include "CApp.h"

SDL_Rect BaseUtil::Coordinator;

void CApp::showMessage(const char *c) {
    SDL_Color textColor = {255, 0, 0};
    SDL_Surface *text = TTF_RenderText_Solid(font, c, textColor);
    SDL_Rect textPosition = {this->screen->w / 2 - text->w / 2, 100};
    SDL_BlitSurface(text, NULL, screen, &textPosition);
    SDL_FreeSurface(text);
    SDL_Flip(screen);
}

CApp::CApp() {
    screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_SWSURFACE);
    blocks = loadImageFromFile("obstacles.bmp");
    background = loadImageFromFile("ocean.bmp");

    BaseUtil::Coordinator.x = camera.x = 0;
    BaseUtil::Coordinator.y = camera.y = 0;
    BaseUtil::Coordinator.w = camera.w = SCREEN_WIDTH;
    BaseUtil::Coordinator.h = camera.h = SCREEN_HEIGHT;

    TTF_Init();

    running = 1;
    playerDirection[0] = 0;
    playerDirection[1] = 0;
    mainPlayer = new CPlayer(loadImageFromFile("player.bmp"));
    font = TTF_OpenFont("font.ttf", 20);

    finalDestination.x = 0;
    finalDestination.y = 0;
    finalDestination.w = TILE_SIZE;
    finalDestination.h = TILE_SIZE;

}

CApp::~CApp() {
    SDL_FreeSurface(blocks);
    SDL_FreeSurface(background);
    SDL_Quit();
    delete mainPlayer;
    for (int i = 0; i < bullets.size(); i++)
        delete bullets[i];
}

SDL_Surface *CApp::loadImageFromFile(const char *c) {
    SDL_Surface *temp = SDL_LoadBMP(c);
    SDL_Surface *returnImg = SDL_DisplayFormat(temp);
    SDL_FreeSurface(temp);
    SDL_SetColorKey(returnImg,
                    SDL_SRCCOLORKEY, SDL_MapRGB(screen->format, 0x00, 0xff, 0xff));
    return returnImg;
}

void CApp::showMap() {
    int start = (BaseUtil::Coordinator.x - (BaseUtil::Coordinator.x % TILE_SIZE)) / TILE_SIZE;
    int end = (BaseUtil::Coordinator.x + BaseUtil::Coordinator.w +
               (TILE_SIZE - (BaseUtil::Coordinator.x + BaseUtil::Coordinator.w) % TILE_SIZE)) / TILE_SIZE;
    if (end > tileMap[0].size())
        end = tileMap[0].size();
    if (start < 0)
        start = 0;
    for (int i = 0; i < tileMap.size(); i++)
        for (int j = start; j < end; j++)
            if (tileMap[i][j] != 0) {
                if (tileMap[i][j] == -1) {
                    continue;
                }
                SDL_Rect blockrect = {(tileMap[i][j] - 1) * TILE_SIZE, 0, TILE_SIZE, TILE_SIZE};
                SDL_Rect destrect = {j * TILE_SIZE - BaseUtil::Coordinator.x, i * TILE_SIZE};
                SDL_BlitSurface(blocks, &blockrect, screen, &destrect);
            }
}

void CApp::start() {
    std::ifstream in("CApp.dat");    //open the files with the maps
    char c[20][30];
    int nummaps = 0;
    int currentmap = 0;
    while (!in.eof() && nummaps < 20) {
        in.getline(c[nummaps], 30);    //load at max 20 maps (use vector for more) std::vector<std::string>  moremaps
        nummaps++;    //number of maps
    }
    nummaps--;    //we go through with one map
    in.close();
    Uint32 start;
    loadMap(c[currentmap]);    //load the current map (start with 0)
    while (running) {
        start = SDL_GetTicks();
        if (playerDirection[0]) {
            mainPlayer->setDirection('l');
            if (mainPlayer->getX() > 0)
                mainPlayer->setXVelocity(-1);
            else {
                mainPlayer->setXVelocity(0);
                camera.x--;
                BaseUtil::Coordinator.x--;
            }
            if (camera.x < 0)
                camera.x = 2000 - SCREEN_WIDTH;
        } else if (playerDirection[1]) {
            mainPlayer->setDirection('r');
            if (mainPlayer->getX() < 80)
                mainPlayer->setXVelocity(1);
            else {
                mainPlayer->setXVelocity(0);
                camera.x++;
                BaseUtil::Coordinator.x++;
            }
            if (camera.x >= 2000 - SCREEN_WIDTH)
                camera.x = 0;
        } else {
            mainPlayer->setXVelocity(0);
        }
        mainPlayer->onMove(tileMap);

        SDL_BlitSurface(background, &camera, screen, NULL);
        showMap();
        mainPlayer->displaySurface(screen);
        for (int i = 0; i < enemies.size(); i++) {
            if (collisionHandler(&BaseUtil::Coordinator, enemies[i]->getContainer())) {
                //			std::cout << "coll" << std::endl;
                SDL_Rect tmprect = {enemies[i]->getContainer()->x - BaseUtil::Coordinator.x, enemies[i]->getContainer()->y,
                                    enemies[i]->getContainer()->w, enemies[i]->getContainer()->h};
                if (collisionHandler(&tmprect, mainPlayer->getContainer())) {
                    //			std::cout << "collsionHandler" << std::endl;
                    if (mainPlayer->getContainer()->y + mainPlayer->getContainer()->h >= enemies[i]->getContainer()->y &&
                        mainPlayer->getContainer()->y + mainPlayer->getContainer()->h <=
                        enemies[i]->getContainer()->y + 10) //we jumped to an CEnemy
                    {
                        delete enemies[i];
                        enemies.erase(enemies.begin() + i);
                        continue;
                    } else {
                        mainPlayer->setLives(mainPlayer->getHealth() - 1);
                    }
                }
                enemies[i]->move(tileMap);
                enemies[i]->displaySurface(screen);
            }
        }



        //hadle the bullets!
        for (int i = 0; i < bullets.size(); i++)
            if (bullets[i]->getContainer()->x > SDL_GetVideoSurface()->clip_rect.w ||
                bullets[i]->getContainer()->x < 0) {
                delete bullets[i];
                bullets.erase(bullets.begin() + i);
            }

        for (int i = 0; i < bullets.size(); i++) {
            bullets[i]->draw(screen);
            bullets[i]->move();
        }

        int str = (BaseUtil::Coordinator.x - (BaseUtil::Coordinator.x % TILE_SIZE)) / TILE_SIZE;
        int end = (BaseUtil::Coordinator.x + BaseUtil::Coordinator.w +
                   (TILE_SIZE - (BaseUtil::Coordinator.x + BaseUtil::Coordinator.w) % TILE_SIZE)) / TILE_SIZE;
        bool nc = 0;
        if (end > tileMap[0].size())
            end = tileMap[0].size();
        if (start < 0)
            start = 0;
        for (int i = 0; i < tileMap.size(); i++)
            for (int j = str; j < end; j++) {
                if (tileMap[i][j] == 0)
                    continue;
                SDL_Rect destrect = {j * TILE_SIZE - BaseUtil::Coordinator.x, i * TILE_SIZE, TILE_SIZE, TILE_SIZE};
                for (int g = 0; g < bullets.size(); g++)
                    if (collisionHandler(&destrect, bullets[g]->getContainer())) {
                        delete bullets[g];
                        bullets.erase(bullets.begin() + g);
                    }
            }

        for (int i = 0; i < enemies.size(); i++)
            for (int j = 0; j < bullets.size(); j++) {
                SDL_Rect tmprec = {enemies[i]->getContainer()->x - BaseUtil::Coordinator.x, enemies[i]->getContainer()->y, 40,
                                   40};
                if (collisionHandler(&tmprec, bullets[j]->getContainer())) {
                    delete enemies[i];
                    delete bullets[j];
                    enemies.erase(enemies.begin() + i);
                    bullets.erase(bullets.begin() + j);
                }
            }


        eventHandler();
        SDL_Flip(screen);


        if (mainPlayer->getHealth() == 0 || mainPlayer->getContainer()->y > screen->h) {
            showMessage("Game over");
            running = false;
            SDL_Delay(3000);
        }
        SDL_Rect tmp = {BaseUtil::Coordinator.x + mainPlayer->getContainer()->x, mainPlayer->getContainer()->y, TILE_SIZE, TILE_SIZE};
        if ((BaseUtil::Coordinator.x + mainPlayer->getContainer()->x >= finalDestination.x && finalDestination.y == 0) ||
            collisionHandler(&tmp, &finalDestination)) {
            currentmap++;
            if (currentmap < nummaps)    //if there are other maps
            {
                showMessage("You win, loading next map...");    //draw a message on the screen
                SDL_Delay(3000);    //wait 3 seconds, so you can see
                tileMap.clear();                        //load the new map and set back every variable to their initialize state;
                finalDestination.x = finalDestination.y = 0;    //set back the finish coordinate to default
                loadMap(c[currentmap]);    //load the map

                for (int i = 0; i < enemies.size(); i++) {
                    delete enemies[i];                                //delete reserved memory
                    enemies.erase(enemies.begin() + i);    //and delete it from the vector too
                }
                for (int i = 0; i < bullets.size(); i++) {
                    delete bullets[i];
                    bullets.erase(bullets.begin() + i);
                }
                Coordinator.x = 0;    //set all parameter back
                Coordinator.y = 0;
                camera.x = 0;
                camera.y = 0;
                delete mainPlayer;
                mainPlayer = new CPlayer(loadImageFromFile("player.bmp"));    //if you need another picture for the CPlayer
                playerDirection[0] = 0;    //we are not moving
                playerDirection[1] = 0;
            } else {
                showMessage("You win, exiting...");
                SDL_Delay(3000);
                running = false;
                break;
            }
        }
        if (1000 / 30 > (SDL_GetTicks() - start))
            SDL_Delay(1000 / 30 - (SDL_GetTicks() - start));
    }
}

CPlayer* CApp::getPlayer() {
    return mainPlayer;
}