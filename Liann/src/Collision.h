//
//  Collision.hpp
//  Liann
//
//  Created by Gosia Zdybel on 21/01/2019.
//  Copyright © 2019 Liann. All rights reserved.
//

#pragma once

#include "SDL2/SDL.h"


class ColliderComponent;

class Collision {
    
public:    
    static bool CircleCircle(const SDL_Rect& recA, const SDL_Rect& recB);
    static bool CircleSquare(const SDL_Rect& recA, const SDL_Rect& recB);
    static bool AABB(const SDL_Rect& recA, const SDL_Rect& recB);
    static bool AABB(const ColliderComponent& colA, const ColliderComponent& colB);
};


