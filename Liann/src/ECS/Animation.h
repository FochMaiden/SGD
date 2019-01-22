//
//  Animation.hpp
//  Liann
//
//  Created by Gosia Zdybel on 22/01/2019.
//  Copyright © 2019 Liann. All rights reserved.
//

#pragma once

struct Animation {
    
    int index;
    int frames;
    int speed;
    
    Animation(){}
    Animation(int i, int f, int s){
        index = i;
        frames = f;
        speed = s;
    }
};


