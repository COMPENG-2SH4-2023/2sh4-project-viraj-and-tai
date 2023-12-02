#include "Food.h"
#include "GameMechs.h"
#include <stdlib.h>
#include <time.h>

Food::Food(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    //foodPos.setObjPos(5, 7, 'a');
}

Food::~Food(){

    delete mainGameMechsRef;
}

void Food::genFood(objPosArrayList* playerPosList)
{
    int y = mainGameMechsRef->getBoardSizeY();
    int x = mainGameMechsRef->getBoardSizeX();
    int myBitV[y][x] = {0,0};
    int xRand;
    int yRand;
    int success = 0;
    srand(time(NULL));

    objPos food;

    while(success == 0){
        xRand = (rand() % (x-2)) + 1;
        yRand = (rand() % (y-2)) + 1;
        for (int i = 0; i < playerPosList->getSize();i++){
            playerPosList -> getElement(food, i);
            if (food.x == xRand && food.y == yRand){
                myBitV[yRand][xRand] = 1;
            }
        }

        if(myBitV[yRand][xRand] == 0)
        {
            myBitV[yRand][xRand] = 1;
            foodPos.x = xRand;
            foodPos.y = yRand;
            foodPos.symbol = 'a';
            success = 1;
        }
    }
}

void Food::getFood(objPos &returnPos)
{
    returnPos.x = foodPos.x;
    returnPos.y = foodPos.y;
    returnPos.symbol = foodPos.symbol;
}