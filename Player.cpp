#include "Player.h"


Player::Player(GameMechs* thisGMRef, Food* thisFoodRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    mainGameFoodRef = thisFoodRef;

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
    delete mainGameFoodRef;
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

    objPos head, food, playerNode;
    int xBounds = mainGameMechsRef->getBoardSizeX();
    int yBounds = mainGameMechsRef->getBoardSizeY();


    playerPosList->getHeadElement(head);
    objPosArrayList* foodBucket = mainGameFoodRef->getFoodBucket();
    int impact = 0;
    switch(myDir){

        case LEFT:
        default:

            
            head.x -= 1;
            for(int i = 0; i < foodBucket->getSize(); i++){
                foodBucket->getElement(food, i);
                if (compareCOORD(head, food)){
                    impact = 1;
                    break;
                }
            }
            if(impact == 1){
                foodCollisionHandler(head, food.symbol);
            }
            else{

                if (head.x <= 0){
                    head.x = xBounds - 2;
                    playerPosList->insertHead(head);
                    playerPosList->removeTail();
                }
                else{
                    playerPosList->insertHead(head);
                    playerPosList->removeTail();
                }
            }

            //starts at one so we can check the head versus every body node, and not head vs head
            for (int i = 1; i < playerPosList->getSize();i++){
                playerPosList->getElement(playerNode, i);
                    if (compareCOORD(head, playerNode)){
                        mainGameMechsRef->setLoseTrue();
                    }
                }

            break;   

        case RIGHT:

            head.x += 1;
            for(int i = 0; i < foodBucket->getSize(); i++){
                foodBucket->getElement(food, i);
                if (compareCOORD(head, food)){
                    impact = 1;
                    break;
                }
            }
            if(impact == 1){

                foodCollisionHandler(head, food.symbol);
            }
            else{
                if (head.x >= xBounds - 1){
                    head.x = 1;
                    playerPosList->insertHead(head);
                    playerPosList->removeTail();
                }
                else{
                    playerPosList->insertHead(head);
                    playerPosList->removeTail();
                }
            }

            for (int i = 1; i < playerPosList->getSize();i++){
                playerPosList->getElement(playerNode, i);
                    if (compareCOORD(head, playerNode)){
                        mainGameMechsRef->setLoseTrue();
                    }
                }

            break; 

        case UP:

            head.y -= 1;
            for(int i = 0; i < foodBucket->getSize(); i++){
                foodBucket->getElement(food, i);
                if (compareCOORD(head, food)){
                    impact = 1;
                    break;
                }
            }
            if(impact == 1){
                
                foodCollisionHandler(head, food.symbol);
            }
            else{
                if (head.y <= 0){
                    head.y = yBounds - 2;
                    playerPosList->insertHead(head);
                    playerPosList->removeTail();
                }
                else{
                    playerPosList->insertHead(head);
                    playerPosList->removeTail();
                }
            }

            for (int i = 1; i < playerPosList->getSize();i++){
                playerPosList->getElement(playerNode, i);
                    if (compareCOORD(head, playerNode)){
                        mainGameMechsRef->setLoseTrue();
                    }
                }

            break; 

        case DOWN:

            head.y += 1;
            for(int i = 0; i < foodBucket->getSize(); i++){
                foodBucket->getElement(food, i);
                if (compareCOORD(head, food)){
                    impact = 1;
                    break;
                }
            }
            if(impact == 1){

                foodCollisionHandler(head, food.symbol);
            }
            else{
                if (head.y >= yBounds - 1){
                    head.y = 1;
                    playerPosList->insertHead(head);
                    playerPosList->removeTail();
                }
                else{
                    playerPosList->insertHead(head);
                    playerPosList->removeTail();
                }
            }

            for (int i = 1; i < playerPosList->getSize();i++){
                playerPosList->getElement(playerNode, i);
                    if (compareCOORD(head, playerNode)){
                        mainGameMechsRef->setLoseTrue();
                    }
                }

            break; 
            
        case STOP:
            break;
    }
}


//simple helper function used to reduce copy pasted code
//compares object coordinates of two objPos objects and returns a boolean based on results
bool Player::compareCOORD(objPos obj1, objPos obj2){
    if (obj1.x == obj2.x && obj1.y == obj2.y){
        return true;
    }

    return false;
}

void Player::foodCollisionHandler(objPos playerNode, char foodType){

    if(foodType == 'a'){
        playerPosList->insertHead(playerNode);
        mainGameFoodRef->genFood(playerPosList);
        mainGameMechsRef->incrementScore(1);
    }else if (foodType == 'o'){
        playerPosList->insertHead(playerNode);
        mainGameFoodRef->genFood(playerPosList);
        mainGameMechsRef->incrementScore(10);
    }else if (foodType == 'x'){
        for(int i = 0; i < 3; i++){
            playerPosList->removeTail();
            mainGameMechsRef->incrementScore(1);
            if (playerPosList->getSize() <= 0){
                mainGameMechsRef->setLoseTrue();
            }
        }
        mainGameFoodRef->genFood(playerPosList);
        

    }

}