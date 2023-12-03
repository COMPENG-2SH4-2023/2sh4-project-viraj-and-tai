#ifndef PLAYER_H
#define PLAYER_H

#include "GameMechs.h"
#include "Food.h"
#include "objPos.h"
#include "objPosArrayList.h"

class Player
{
    // Construct the remaining declaration from the project manual.

    // Only some sample members are included here

    // You will include more data members and member functions to complete your design.

    public:
        enum Dir {UP, DOWN, LEFT, RIGHT, STOP};  // This is the direction state

        Player(GameMechs* thisGMRef, Food* thisFoodRef);
        ~Player();

        objPosArrayList* getPlayerList();
        void updatePlayerDir();
        void movePlayer();

    private:
        objPosArrayList* playerPosList;   // Upgrade this in iteration 3.       
        enum Dir myDir;

        // Need a reference to the Main Game Mechanisms and Food classs
        GameMechs* mainGameMechsRef;
        Food* mainGameFoodRef;

        //Additional helper functions to reduce copy paste, see player.cpp file for info
        bool compareCOORD(objPos obj1, objPos obj2);
        void foodCollisionHandler(objPos playerNode, char foodType);
};

#endif