//
// Created by hoang on 12/9/15.
//
# include "CApp.h"

void CApp::loadMap(const char *file) {
    std::ifstream inputStream(file);
    if (!inputStream.is_open()) {
        inputStream.open("map.map");
    }
    int mapWidth, mapHeight;

    inputStream>> mapWidth;
    inputStream>> mapHeight;

    int current;
    for (int i = 0; i < mapHeight; i++) {
        std::vector<int> mapVector;
        for (int j = 0; j < mapWidth; j++) {
            if (inputStream.eof())
                return;
            inputStream>> current;
            if (current >= -1 && current <= 8) {
                if (current == -1) {
                    enemies.push_back(new CEnemy(loadImageFromFile("enemy.bmp"), j * TILE_SIZE, i * TILE_SIZE - 5, 1, 0));
                    mapVector.push_back(0);
                    continue;
                } else if (current == 3) {
                    finalDestination.x = j * TILE_SIZE;
                    finalDestination.y = i * TILE_SIZE;
                    mapVector.push_back(current);
                } else {
                    mapVector.push_back(current);
                }
            } else {
                mapVector.push_back(0);
            }
        }
        tileMap.push_back(mapVector);
    }
    inputStream.close();
    if (finalDestination.x == 0 && finalDestination.y == 0) {
        finalDestination.x = mapWidth * TILE_SIZE - TILE_SIZE;
    }
}
