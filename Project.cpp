#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "Player.h"
#include "GameMechs.h"
#include "Food.h"

using namespace std;

#define DELAY_CONST 100000

GameMechs *mechsPtr = new GameMechs(20, 10);
Player *playerPtr = new Player(mechsPtr);
Food *foodPtr = new Food(mechsPtr);

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);



int main(void)
{

    Initialize();

    while(mechsPtr -> getExitFlagStatus() == false)  
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();

}


void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();
    objPos temp;
    playerPtr -> getPlayerHead(temp);
    foodPtr -> genFood(temp);
}

void GetInput(void)
{
    if (MacUILib_hasChar()){
        mechsPtr -> setInput(MacUILib_getChar());
    }
}

void RunLogic(void)
{
    char input = mechsPtr -> getInput();
    if(input != 0){

        switch(input){

            case ' ':
                mechsPtr -> setExitTrue();
                break;

            default:
                break;
        }
    }

    playerPtr -> movePlayer();
    playerPtr -> updatePlayerDir();
    mechsPtr -> clearInput();
   
    objPos temp;
    playerPtr -> getPlayerHead(temp);

    objPos tempFood;
    foodPtr -> getFood(tempFood);
    if(tempFood.x == temp.x && tempFood.y == temp.y)
    {
        mechsPtr -> incrementScore(1);
        foodPtr -> genFood(temp);
    }

}

void DrawScreen(void)
{
    MacUILib_clearScreen();

    int yBounds = mechsPtr -> getBoardSizeY();
    int xBounds = mechsPtr -> getBoardSizeX();

    objPosArrayList* playerPosList = playerPtr -> getPlayerList();

    objPos playerNode;

    objPos food;
    foodPtr -> getFood(food);

    int printed;
    for (int y = 0; y < yBounds; y++){
        for (int x = 0; x < xBounds; x++){
            printed = 0;
            for (int i = 0; i < playerPosList->getSize();i++){
                playerPosList -> getElement(playerNode, i);
                if (x == playerNode.x && y == playerNode.y){
                    MacUILib_printf("%c", playerNode.symbol);
                    printed = 1;
                }
            }

            if (y == 0 || y == yBounds -1){
                MacUILib_printf("#");               
            }
            else if (x == 0 || x == xBounds-1){
                MacUILib_printf("#");
            }
            else if (x == food.x && y == food.y){
                MacUILib_printf("%c", food.symbol);
            }
            else if (printed == 0){
                MacUILib_printf(" ");
            }
        }
        printf("\n");
    }
    MacUILib_printf("x: %d, y: %d c: %c\n", playerNode.x, playerNode.y, playerNode.symbol);
    MacUILib_printf("score: %d, size: %d\n", mechsPtr->getScore(), playerPosList->getSize());


}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();   

    delete mechsPtr;
    delete playerPtr;
    delete foodPtr;
  
    MacUILib_uninit();
}
