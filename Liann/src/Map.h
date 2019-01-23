//
//  Map.hpp
//  Liann
//
//  Created by Gosia Zdybel on 20/01/2019.
//  Copyright © 2019 Liann. All rights reserved.
//

#pragma once

#include <string>

class Map {
    
public:
    Map(std::string tID, int ms, int ts);
    ~Map();
    
    void LoadMap(std::string path, int sizeX, int sizeY);
    void AddTile(int srcX, int srcY, int xpos, int ypos);
    
private:
    std::string texID;
    int mapScale;
    int tileSize;
    int scaledSize;
    
};


