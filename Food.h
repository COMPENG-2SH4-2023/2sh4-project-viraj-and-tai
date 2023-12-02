#ifndef FOOD_H
#define FOOD_H

#include "objPos.h"
#include "GameMechs.h"
#include <stdlib.h>

class Food{

    private:
    objPos foodPos;
    GameMechs* mainGameMechsRef;

    public:
    Food(GameMechs* thisGMRef);
    ~Food();

    void genFood(objPosArrayList* playerPosList);
    void getFood(objPos &returnPos);
};

#endif