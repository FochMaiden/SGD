//
//  AssetManager.hpp
//  Liann
//
//  Created by Gosia Zdybel on 22/01/2019.
//  Copyright © 2019 Liann. All rights reserved.
//

#pragma once

#include "TextureManager.h"

class AssetManager {
public:
    AssetManager();
    ~AssetManager();
  
    void AddTexture(std::string id, const char* path);
    SDL_Texture GetTexture(std::string id);
private:
    std::map<std::string, SDL_Texture*> textures;
};


