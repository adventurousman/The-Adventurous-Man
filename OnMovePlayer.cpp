//
// Created by hoang on 12/9/15.
//
#include "CPlayer.h"

void CPlayer::onMove(const std::vector<std::vector<int> > &map) {
    int begin = (BaseUtil::Coordinator.x - (BaseUtil::Coordinator.x % TILE_SIZE)) / TILE_SIZE;
    int end = (BaseUtil::Coordinator.x + BaseUtil::Coordinator.w +
               (TILE_SIZE - (BaseUtil::Coordinator.x + BaseUtil::Coordinator.w) % TILE_SIZE)) / TILE_SIZE;
    bool nc = 0;

    if (end > map[0].size())
        end = map[0].size();
    if (begin < 0)
        begin = 0;


    for (int i = 0; i < map.size(); i++)
        for (int j = begin; j < end; j++) {
            if (map[i][j] == 0)
                continue;
            SDL_Rect destrect = {j * TILE_SIZE - BaseUtil::Coordinator.x, i * TILE_SIZE, TILE_SIZE, TILE_SIZE};
            if (collisionHandler(&destrect, &characterContainer)) {
                //			std::cout << destrect.x << " " << destrect.y << " " << box.x << " " << box.y << std::endl;
                nc = 1;
                if (destrect.y >=
                    characterContainer.y + characterContainer.h - 11)
                    //collisionHandler - the block is under the CPlayer
                {
                    onGround = 1;
                    yVelocity = 0;
                } else if (destrect.y + destrect.h <= characterContainer.y + 11) {
                    characterContainer.y++;
                    yVelocity = 5;
                }
                if (characterContainer.x + characterContainer.w >= destrect.x - 5
                    && characterContainer.y + characterContainer.h >= destrect.y + 6 &&
                    characterContainer.x + characterContainer.w <= destrect.x + 20)
                    //collisionHandler - right to the CPlayer
                {
                    xVelocity = 0;
                    characterContainer.x--;
                    moving = false;
                }
                else if (characterContainer.x <= destrect.x + destrect.w
                         && characterContainer.y + characterContainer.h >= destrect.y + 6)
                    //collisionHandler - left to the CPlayer
                {
                    xVelocity = 0;
                    characterContainer.x++;
                    moving = false;
                }
            }
        }

    if (!nc && !onJump) {
        yVelocity = 5;
        onGround = 0;
    }
    if (onJump && yVelocity < 5)
        yVelocity++;
    else
        onJump = 0;
    characterContainer.x += xVelocity;
    characterContainer.y += yVelocity;
    if (moving) {
        currentFrame += 0.2f;
//		std::cout << (int)(frame+0.5) << std::endl;
        if (playerDirecion == 'r' && currentFrame >= 1.4)
            currentFrame = 0.f;
        else if (playerDirecion == 'l' && currentFrame >= 3.0f)
            currentFrame = 1.6f;
    }

}

