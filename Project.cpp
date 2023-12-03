#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "Player.h"
#include "GameMechs.h"
#include "Food.h"

using namespace std;

#define DELAY_CONST 100000

GameMechs *mechsPtr = new GameMechs(20, 10);
Food *foodPtr = new Food(mechsPtr);
Player *playerPtr = new Player(mechsPtr, foodPtr);
objPosArrayList* wallsList = new objPosArrayList();


void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);

int main(void)
{

    Initialize();

    //run while the exit flag is false
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
    //initial food gen
    foodPtr -> genFood(playerPtr -> getPlayerList());

    //creating and storing all wall objects in an arraylist
    objPos wall;
    int yBounds = mechsPtr -> getBoardSizeY();
    int xBounds = mechsPtr -> getBoardSizeX();
    for (int y = 0; y < yBounds; y++){
        for (int x = 0; x < xBounds; x++){

            if (y == 0 || y == yBounds -1){
                wall.setObjPos(x,y,'#');
                wallsList -> insertHead(wall);              
            }
            else if (x == 0 || x == xBounds-1){
                wall.setObjPos(x,y,'#');
                wallsList -> insertHead(wall);   
            }
        }
    }
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

    //standard movement logic, see individual functions for details
    playerPtr -> movePlayer();
    playerPtr -> updatePlayerDir();
    mechsPtr -> clearInput();

}

void DrawScreen(void)
{
    MacUILib_clearScreen();

    int yBounds = mechsPtr -> getBoardSizeY();
    int xBounds = mechsPtr -> getBoardSizeX();

    objPosArrayList* playerPosList = playerPtr -> getPlayerList();

    objPos playerNode;
    objPos wallNode;

    objPosArrayList* foodBucket = foodPtr -> getFoodBucket();
    objPos foodNode;

    int printed;//flag used to determine if a ' ' char should be printed
    for (int y = 0; y < yBounds; y++){
        for (int x = 0; x < xBounds; x++){
            printed = 0;
            //checking to see if a snake segment should be printed
            for (int i = 0; i < playerPosList->getSize();i++){
                playerPosList -> getElement(playerNode, i);
                if (x == playerNode.x && y == playerNode.y){
                    MacUILib_printf("%c", playerNode.symbol);
                    printed = 1;
                }
            }

            //checking to see if a wall object should be printed
            for (int j = 0; j < wallsList->getSize();j++){
                wallsList -> getElement(wallNode, j);
                if (x == wallNode.x && y == wallNode.y){
                    MacUILib_printf("%c", wallNode.symbol);
                    printed = 1;
                }
            }

            //checking to see if a piece of food should be printed
            for (int k = 0; k < foodBucket->getSize();k++){
                foodBucket -> getElement(foodNode, k);
                if (x == foodNode.x && y == foodNode.y){
                    MacUILib_printf("%c", foodNode.symbol);
                    printed = 1;
                }
            }

            //if all else did not print, print ' ' character
            if (printed == 0){
                MacUILib_printf(" ");
            }
        }
        MacUILib_printf("\n");
    }
    //game info print messages
    MacUILib_printf("Use WASD to control the snake\n\n");
    MacUILib_printf("a: +1 point, +1 length, o: +10 points, +1 length, x: +3 points -3 length\n");
    MacUILib_printf("Warning: Eating 'x' at 3 or less length cause death\n");
    MacUILib_printf("score: %d, snake size: %d\n", mechsPtr->getScore(), playerPosList->getSize());

}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();

    //print different messages based on exit or lose conditional
    if(mechsPtr -> getLoseFlagStatus()){
        MacUILib_printf("\nYou Lose :(\n");
    }
    MacUILib_printf("Final Score: %d\n", mechsPtr->getScore());   

    delete mechsPtr;
    delete playerPtr;
    delete foodPtr;
    delete wallsList;
  
    MacUILib_uninit();
}
