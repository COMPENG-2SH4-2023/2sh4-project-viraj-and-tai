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

objPosArrayList* Player::getPlayerList(){

    // return the reference to the playerPos arrray list
    return playerPosList;
}

void Player::updatePlayerDir()
{
    // PPA3 input processing logic
    //same input processing logic at ppa 2 and 3

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
    //we used a swithc case and enum system for the different directions like in ppa2 and ppa3
    switch(myDir){

        case LEFT:
        default:

            
            head.x -= 1;
            //comparing head of the snake to every element in the food bucket and setting impact flag to 1 if contact is made
            for(int i = 0; i < foodBucket->getSize(); i++){
                foodBucket->getElement(food, i);
                if (compareCOORD(head, food)){
                    impact = 1;
                    break;
                }
            }
            //if contact was made earlier, call the food collision handler, located at bof, see function for details
            if(impact == 1){
                foodCollisionHandler(head, food.symbol);
            }
            //if no contact continue on merry way
            else{
                //if contact is made with a wall, wrap around pac-man style
                if (head.x <= 0){
                    head.x = xBounds - 2;
                    playerPosList->insertHead(head);
                    playerPosList->removeTail();
                }
                //if not continue on jolly way
                else{
                    playerPosList->insertHead(head);
                    playerPosList->removeTail();
                }
            }

            //snake death conditional checking
            //starts at one so we can check the head versus every body node, and not head vs head
            for (int i = 1; i < playerPosList->getSize();i++){
                playerPosList->getElement(playerNode, i);
                    if (compareCOORD(head, playerNode)){
                        mainGameMechsRef->setLoseTrue();
                    }
                }

            break;   

            //all above comments apply to each individual direction
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
            
            //if in stop, do nothing, the snake should only be in this mode at the first start
        case STOP:
            break;
    }
}


//simple helper functions used to reduce copy pasted code
//compares object coordinates of two objPos objects and returns a boolean based on results
bool Player::compareCOORD(objPos obj1, objPos obj2){
    if (obj1.x == obj2.x && obj1.y == obj2.y){
        return true;
    }

    return false;
}

//handles all food collision based, resulting in different effects based on food type
//'a' food, regular food +1 points +1 length
//'o' food, super food +10 points + 1 length
//'x' food, diet pill -3 length, +1 point per snake segment removed
//if you hit 0 segments after eating a 'x' pill you will lose, this is INTENDED
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