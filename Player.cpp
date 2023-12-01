#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    mainGameMechsRef = thisGMRef;
    playerPos.setObjPos(10, 5, '*');
    // more actions to be included
}


Player::~Player()
{
    // delete any heap members here
}

void Player::getPlayerPos(objPos &returnPos)
{
    // return the reference to the playerPos arrray list
    playerPos.getObjPos(returnPos);
}

void Player::updatePlayerDir()
{
    // PPA3 input processing logic

    switch(myDir){

        case LEFT:
        default:

        if ((mainGameMechsRef -> getInput()) == 'W' || (mainGameMechsRef -> getInput()) == 'w'){
            myDir = UP;
        }

        if ((mainGameMechsRef -> getInput()) == 'S' || (mainGameMechsRef -> getInput()) == 's'){
            myDir = DOWN;
        }
        break;

        case RIGHT:

        if ((mainGameMechsRef -> getInput()) == 'W' || (mainGameMechsRef -> getInput()) == 'w'){
            myDir = UP;
        }

        if ((mainGameMechsRef -> getInput()) == 'S' || (mainGameMechsRef -> getInput()) == 's'){
            myDir = DOWN;
        }
        break;

        case UP:

        if ((mainGameMechsRef -> getInput()) == 'A' || (mainGameMechsRef -> getInput()) == 'a'){
            myDir = LEFT;
        }

        if ((mainGameMechsRef -> getInput()) == 'D' || (mainGameMechsRef -> getInput()) == 'd'){
            myDir = RIGHT;
        }
        break;

        case DOWN:

        if ((mainGameMechsRef -> getInput()) == 'A' || (mainGameMechsRef -> getInput()) == 'a'){
            myDir = LEFT;
        }

        if ((mainGameMechsRef -> getInput()) == 'D' || (mainGameMechsRef -> getInput()) == 'd'){
            myDir = RIGHT;
        }
        break;

        case STOP:

        if ((mainGameMechsRef -> getInput()) == 'W' || (mainGameMechsRef -> getInput()) == 'w'){
            myDir = UP;
        }

        if ((mainGameMechsRef -> getInput()) == 'S' || (mainGameMechsRef -> getInput()) == 's'){
            myDir = DOWN;
        }

        if ((mainGameMechsRef -> getInput()) == 'A' || (mainGameMechsRef -> getInput()) == 'a'){
            myDir = LEFT;
        }

        if ((mainGameMechsRef -> getInput()) == 'D' || (mainGameMechsRef -> getInput()) == 'd'){
            myDir = RIGHT;
        }
        break;    
    }
        
}

void Player::movePlayer()
{
    // PPA3 Finite State Machine logic

    objPos temp;
    int xBounds = mainGameMechsRef->getBoardSizeX();
    int yBounds = mainGameMechsRef->getBoardSizeY();

    switch(myDir){

        case LEFT:
        default:

            playerPos.getObjPos(temp);
            temp.x -= 1;
            if (temp.x <= 0){
                playerPos.setObjPos(xBounds-2, temp.y, temp.symbol);
            }
            else{
                playerPos.setObjPos(temp);
            }

            break;

        case RIGHT:

            playerPos.getObjPos(temp);
            temp.x += 1;
            if (temp.x >= xBounds - 1){
                playerPos.setObjPos(1, temp.y, temp.symbol);
            }
            else{
                playerPos.setObjPos(temp);
            }
            break;

        case UP:

            playerPos.getObjPos(temp);
            temp.y -= 1;
            if (temp.y <= 0){
                playerPos.setObjPos(temp.x, yBounds - 2, temp.symbol);
            }
            else{
                playerPos.setObjPos(temp);
            }
            break;

        case DOWN:

            playerPos.getObjPos(temp);
            temp.y += 1;
            if (temp.y >= yBounds - 1){
                playerPos.setObjPos(temp.x, 1, temp.symbol);
            }
            else{
                playerPos.setObjPos(temp);
            }
            break;
        case STOP:
            break;
    }
}

