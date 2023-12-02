#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    mainGameMechsRef = thisGMRef;

    objPos head;
    head.setObjPos(10,5,'*');

    playerPosList = new objPosArrayList();
    playerPosList -> insertHead(head);

    // more actions to be included
}


Player::~Player()
{
    // delete any heap members here
    delete mainGameMechsRef;
    delete playerPosList;
}

void Player::getPlayerHead(objPos &returnPos)
{
    
    playerPosList->getHeadElement(returnPos);
}

objPosArrayList* Player::getPlayerList(){

    // return the reference to the playerPos arrray list
    return playerPosList;
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

            playerPosList->getHeadElement(temp);
            temp.x -= 1;
            if (temp.x <= 0){
                temp.x = xBounds - 2;
                playerPosList->insertHead(temp);
                playerPosList->removeTail();
            }
            else{
                playerPosList->insertHead(temp);
                playerPosList->removeTail();
            }

            break;

        case RIGHT:

            playerPosList->getHeadElement(temp);
            temp.x += 1;
            if (temp.x >= xBounds - 1){
                temp.x = 1;
                playerPosList->insertHead(temp);
                playerPosList->removeTail();
            }
            else{
                playerPosList->insertHead(temp);
                playerPosList->removeTail();
            }
            break;

        case UP:

            playerPosList->getHeadElement(temp);
            temp.y -= 1;
            if (temp.y <= 0){
                temp.y = yBounds - 2;
                playerPosList->insertHead(temp);
                playerPosList->removeTail();
            }
            else{
                playerPosList->insertHead(temp);
                playerPosList->removeTail();
            }
            break;

        case DOWN:

            playerPosList->getHeadElement(temp);
            temp.y += 1;
            if (temp.y >= yBounds - 1){
                temp.y = 1;
                playerPosList->insertHead(temp);
                playerPosList->removeTail();
            }
            else{
                playerPosList->insertHead(temp);
                playerPosList->removeTail();
            }
            break;
        case STOP:
            break;
    }
}

