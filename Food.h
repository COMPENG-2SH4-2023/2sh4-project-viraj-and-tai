#ifndef FOOD_H
#define FOOD_H

#include "objPos.h"
#include "GameMechs.h"
#include <stdlib.h>

class Food{

    private:
    objPosArrayList* foodBucket;
    GameMechs* mainGameMechsRef;

    public:
    Food(GameMechs* thisGMRef);
    ~Food();

    void genFood(objPosArrayList* playerPosList);
    objPosArrayList* getFoodBucket();
};

#endif