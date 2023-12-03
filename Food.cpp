#include "Food.h"
#include "GameMechs.h"
#include <stdlib.h>
#include <time.h>

Food::Food(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    foodBucket = new objPosArrayList();
    //foodPos.setObjPos(5, 7, 'a');
}

Food::~Food(){

    delete mainGameMechsRef;
    delete foodBucket;
}

void Food::genFood(objPosArrayList* playerPosList)
{

    //since we only every expect there to be two items in the food bucket
    //we need to ensure it is empty before we add new items
    while (foodBucket->getSize() != 0){
        foodBucket -> removeTail();
    }

    int y = mainGameMechsRef->getBoardSizeY();
    int x = mainGameMechsRef->getBoardSizeX();
    int myBitV[y][x] = {0,0};
    int xRand;
    int yRand;
    int success = 0;
    srand(time(NULL));

    //temporary objPos objects used for manipulating data from getters and setters
    objPos food;
    objPos foodPos;

    //spawn 1 regular food
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
            foodBucket->insertHead(foodPos);
            success = 1;
        }
    }

    success = 0;
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
            //randomly select a special food type based on the even/odd-ness of a rng number from 1 to 100
            if ((1 + (rand() % 100)) % 2){
                foodPos.symbol = 'x';
            }else{
                foodPos.symbol = 'o';
            }
            
            foodBucket->insertHead(foodPos);
            success = 1;
        }
    }

}

// void Food::getFood(objPos &returnPos)
// {
//     returnPos.x = foodPos.x;
//     returnPos.y = foodPos.y;
//     returnPos.symbol = foodPos.symbol;
// }

objPosArrayList* Food::getFoodBucket(){
    return foodBucket;
}