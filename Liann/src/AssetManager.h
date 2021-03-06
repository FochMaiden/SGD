//
//  AssetManager.hpp
//  Liann
//
//  Created by Gosia Zdybel on 22/01/2019.
//  Copyright © 2019 Liann. All rights reserved.
//

#pragma once

#include <map>
#include <string>
#include "TextureManager.h"
#include "Vector2D.h"
#include "ECS/ECS.h"
#include "SDL2_ttf/SDL_ttf.h"


class AssetManager {
public:
    AssetManager(Manager* man);
    ~AssetManager();
  
    //gameobjects
    void CreateProjectile(Vector2D pos, Vector2D vel, int range, int speed, std::string id);
    void CreateMonster(Vector2D pos, std::string id);
    
    //texture manager
    void AddTexture(std::string id, const char* path);
    SDL_Texture* GetTexture(std::string id);
    
    void AddFont(std::string id, std::string path, int fontSize);
    TTF_Font* GetFont(std::string id);
private:
    Manager* manager;
    std::map<std::string, SDL_Texture*> textures;
    std::map<std::string, TTF_Font*> fonts;
};


