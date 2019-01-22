//
//  ECS.cpp
//  Liann
//
//  Created by Gosia Zdybel on 21/01/2019.
//  Copyright © 2019 Liann. All rights reserved.
//

#include <stdio.h>
#include "ECS.h"

void Entity::addGroup(Group mGroup){
    groupBitSet[mGroup] = true;
    manager.AddToGroup(this, mGroup);
}
