//
//  AssetManager.cpp
//  Liann
//
//  Created by Gosia Zdybel on 22/01/2019.
//  Copyright © 2019 Liann. All rights reserved.
//

#include "AssetManager.h"
#include "ECS/Components.h"

AssetManager::AssetManager(Manager* man) : manager(man) {
}
AssetManager::~AssetManager(){
    
}
//game objects
void AssetManager::CreateProjectile(Vector2D pos, Vector2D vel, int range, int speed, std::string id){
    auto& projecitle(manager->addEntity());
    projecitle.addComponent<TransformComponent>(pos.x, pos.y, 32, 32, 1);
    projecitle.addComponent<SpriteComponent>(id, false);
    projecitle.addComponent<ProjectileComponent>(range, speed, vel);
    projecitle.addComponent<ColliderComponent>("projectile");
    projecitle.addGroup(Game::groupProjectiles);
}

void AssetManager::CreateMonster(std::string id){
    auto& monster(manager->addEntity());
    monster.addComponent<TransformComponent>(1600, 1600, 32, 32, 2);
    monster.addComponent<SpriteComponent>("monster", false);
    monster.addComponent<ColliderComponent>("monster");
    monster.addGroup(Game::groupMonsters);
}

//textures
void AssetManager::AddTexture(std::string id, const char* path){
    textures.emplace(id, TextureManager::LoadTexture(path));
}
SDL_Texture* AssetManager::GetTexture(std::string id){
    return textures[id];
}

void AssetManager::AddFont(std::string id, std::string path, int fontSize){
    fonts.emplace(id, TTF_OpenFont(path.c_str(), fontSize));
    
}

TTF_Font* AssetManager::GetFont(std::string id){
    return fonts[id];
}
