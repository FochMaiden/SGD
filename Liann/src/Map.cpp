//
//  Map.cpp
//  Liann
//
//  Created by Gosia Zdybel on 20/01/2019.
//  Copyright © 2019 Liann. All rights reserved.
//

#include "Map.h"
#include "Game.h"
#include <fstream>
#include "ECS/ECS.h"
#include "ECS/Components.h"

//external deffinition
extern Manager manager;

//h and w

Map::Map(std::string tID, int ms, int ts) : texID(tID), mapScale(ms), tileSize(ts){
    scaledSize = ms * ts;
}

Map::~Map(){
}

void Map::LoadMap(std::string path, int sizeX, int sizeY){

    char c;
    std::fstream mapFile;
    mapFile.open(path);
    
    int srcX, srcY;
   // int xpos, ypos;
    
    for (int y = 0; y < sizeY; y++) {
        for (int x = 0; x < sizeX; x++) {
            
            mapFile.get(c);
            srcY = atoi(&c) * tileSize;
            mapFile.get(c);
            srcX = atoi(&c) * tileSize;
            //cast int to char and x, y to size
            AddTile(srcX, srcY, x * scaledSize, y * scaledSize);
            //ignore next character = ,
            mapFile.ignore();
        }
    }
    
    
    mapFile.ignore();
    
    
    for (int y = 0; y < sizeY; y++) {
        for (int x = 0; x < sizeX; x++) {
            mapFile.get(c);
           // std::cout << c << std::endl;
            if (c == '1') {
                auto& tcol(manager.addEntity());
                tcol.addComponent<ColliderComponent>("terrain", x * scaledSize, y * scaledSize, scaledSize);
                tcol.addGroup(Game::groupColliders);
            }
            mapFile.ignore();
        }
        
    }
    
    mapFile.close();
}

void Map::AddTile(int srcX, int srcY, int xpos, int ypos){
    auto& tile(manager.addEntity());
    tile.addComponent<TileComponent>(srcX, srcY, xpos, ypos, tileSize, mapScale, texID);
    tile.addGroup(Game::groupMap);
}
