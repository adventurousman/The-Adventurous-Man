#include "CEnemy.h"

CEnemy::CEnemy(SDL_Surface *img, int x, int y, int xVel, int yVel) {
    displayImage = img;

    enemyContainer.x = x;
    enemyContainer.y = y;
    enemyContainer.w = displayImage->clip_rect.w / 2;
    enemyContainer.h = displayImage->clip_rect.h;

    xVelocity = xVel;
    yVelocity = yVel;

    onGround = 0;

    frames[0].x = frames[0].y = 0;
    frames[0].w = frames[0].h = 40;
    frames[1].x = 40;
    frames[1].y = 0;
    frames[1].w = frames[1].h = 40;

    currentFrame = 0.0;
}

CEnemy::~CEnemy() {
    SDL_FreeSurface(displayImage);
}

SDL_Rect *CEnemy::getContainer() {
    return &enemyContainer;
}

void CEnemy::move(std::vector<std::vector<int> > &map) {
    int start = (BaseUtil::Coordinator.x - (BaseUtil::Coordinator.x % TILE_SIZE)) / TILE_SIZE - 2;
    int end = (BaseUtil::Coordinator.x + BaseUtil::Coordinator.w +
               (TILE_SIZE - (BaseUtil::Coordinator.x + BaseUtil::Coordinator.w) % TILE_SIZE)) / TILE_SIZE + 2;

    bool keepAlive = 0;

    if (end > map[0].size())
        end = map[0].size();
    if (start < 0)
        start = 0;


    for (int i = 0; i < map.size(); i++)
        for (int j = start; j < end; j++) {
            if (map[i][j] == 0)
                continue;

            SDL_Rect destinationContainer = {j * TILE_SIZE, i * TILE_SIZE, TILE_SIZE, TILE_SIZE};
            if (collisionHandler(&destinationContainer, &enemyContainer)) {
                //			std::cout << box.x << std::endl;
                if (destinationContainer.y >= enemyContainer.y + enemyContainer.h - 11) {
                    onGround = 1;
                    yVelocity = 0;
                    keepAlive = 1;
                }
                if (enemyContainer.x + enemyContainer.w >= destinationContainer.x - 5 &&
                    enemyContainer.y + enemyContainer.h >= destinationContainer.y + 6 &&
                        enemyContainer.x + enemyContainer.w <= destinationContainer.x + 20)
                    //collsionHandler - right to the CPlayer
                {
                    xVelocity = -xVelocity;
                }
                else if (enemyContainer.x <= destinationContainer.x + destinationContainer.w &&
                         enemyContainer.y + enemyContainer.h >= destinationContainer.y + 6)
                    //collsionHandler - left to the CPlayer
                {
                    xVelocity = -xVelocity;
                }
            }
        }
    if (!keepAlive)
        yVelocity = 5;
    enemyContainer.x += xVelocity;
    enemyContainer.y += yVelocity;
    currentFrame += 0.1;
    if (currentFrame >= 1.4)
        currentFrame = 0.0;
}


void CEnemy::displaySurface(SDL_Surface *screen) {
    SDL_Rect tmp = {enemyContainer.x - BaseUtil::Coordinator.x, enemyContainer.y, TILE_SIZE, TILE_SIZE};
    SDL_BlitSurface(displayImage, &frames[(int) (currentFrame + 0.5)], screen, &tmp);
}

double CEnemy::getXVel() {
    return xVelocity;
}

void CEnemy::setXVel(double vel) {
    xVelocity = vel;
}
