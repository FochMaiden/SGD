//
//  UILabel.h
//  Liann
//
//  Created by Gosia Zdybel on 24/01/2019.
//  Copyright © 2019 Liann. All rights reserved.
//
#include "ECS.h"
#include "../AssetManager.h"
#include "../Game.h"

#include "SDL2/SDL.h"
#include "SDL2_ttf/SDL_ttf.h"
#include <string>

#pragma once

class UILabel : public Component {
    
public:
    UILabel(int xpos, int ypos, std::string text, std::string font, SDL_Color& color) : labelText(text), labelFont(font), textColor(color){
        position.x = xpos;
        position.y = ypos;
        
        SetLabelText(labelText, labelFont);
    }
    ~UILabel(){
        
    }
    
    void SetLabelText(std::string text, std::string font){
        SDL_Surface* surf = TTF_RenderText_Blended(Game::assets->GetFont(font), text.c_str(), textColor);
        labelTexture = SDL_CreateTextureFromSurface(Game::renderer, surf);
        SDL_FreeSurface(surf);
        
        SDL_QueryTexture(labelTexture, nullptr, nullptr, &position.w, &position.h);
    }
    void draw() override{
        SDL_RenderCopy(Game::renderer, labelTexture, nullptr, &position);
    };
private:
    SDL_Rect position;
    std::string labelText;
    std::string labelFont;
    SDL_Color textColor;
    SDL_Texture* labelTexture;
};
