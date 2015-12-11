#include "CPlayer.h"
#include "BaseUtil.h"

CPlayer::CPlayer(SDL_Surface *image) {
    displayImage = image;
    characterContainer.x = 30;
    characterContainer.y = 20;
    characterContainer.w = TILE_SIZE;
    characterContainer.h = TILE_SIZE;

    onGround = 0;
    xVelocity = yVelocity = 0;
    currentFrame = 0.;

    for (int i = 0; i < 4; i++) {
        frames[i].x = i * TILE_SIZE;
        frames[i].y = 0;
        frames[i].w = frames[i].h = TILE_SIZE;
    }
    onJump = 0;
    lives = 10;
    playerDirecion = 'r';
    moving = false;
}

CPlayer::~CPlayer() {
    SDL_FreeSurface(displayImage);
}

int CPlayer::getX() {
    return characterContainer.x;
}

int CPlayer::getXVelocity() {
    return xVelocity;
}

void CPlayer::setXVelocity(int vel) {
    xVelocity = vel;
}

void CPlayer::setMoving(bool b) {
    moving = b;
}

char CPlayer::getPlayerDirection() {
    return playerDirecion;
}

void CPlayer::displaySurface(SDL_Surface *screen) {
    SDL_BlitSurface(displayImage, &frames[(int) (currentFrame + 0.5)], screen, &characterContainer);
}

void CPlayer::jump() {
    if (onGround && !onJump) {
        onGround = 0;
        onJump = 1;
        yVelocity = -17;
        characterContainer.y -= 5;
    }
}

SDL_Rect *CPlayer::getContainer() {
    return &characterContainer;
}

int CPlayer::getHealth() {
    return lives;
}

void CPlayer::setLives(int lives) {
    lives = lives;
}

void CPlayer::setDirection(const char dir) {
    if ((dir == 'r' || dir == 'l') && playerDirecion != dir) {
        playerDirecion = dir;
        if (playerDirecion == 'r')
            currentFrame = 0.0;
        else
            currentFrame = 2.6;
    }
}
