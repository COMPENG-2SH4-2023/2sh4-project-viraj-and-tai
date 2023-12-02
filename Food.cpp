#include "Food.h"
#include "GameMechs.h"
#include <stdlib.h>

Food::Food(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
}

Food::~Food(){
    delete foodPos;
}

void Food::genFood(objPos blockOff)
{
    int y = mainGameMechsRef->getBoardSizeY();
    int x = mainGameMechsRef->getBoardSizeX();
    int myBitV[y][x] = {0,0};
    int xRand = (rand() % (x-1)) + 1;
    int yRand = (rand() % (y-1)) + 1;
    int success = 0;

    while(success == 0){
        if(xRand == blockOff.x && yRand == blockOff.y)
            {
                myBitV[yRand][xRand] = 1;
            }
        if(myBitV[yRand][xRand] == 0)
        {
            myBitV[yRand][xRand] = 1;
            foodPos.x = xRand;
            foodPos.y = yRand;
            foodPos.symbol = "a";
            success = 1;
        }
    }
}

void Food::getFood(objPos &returnPos)
{
    returnPos.x = foodPos.x;
    returnPos.y = foodPos.y;
}