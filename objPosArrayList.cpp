#include "objPosArrayList.h"

// Check lecture contents on general purpose array list construction, 
// and modify it to support objPos array list construction.

objPosArrayList::objPosArrayList()
{
    sizeList = 0;
    sizeArray = ARRAY_MAX_CAP;
    aList = new objPos[ARRAY_MAX_CAP];
}

objPosArrayList::~objPosArrayList()
{
    delete[] aList;
}

int objPosArrayList::getSize()
{
    return sizeList;
}

void objPosArrayList::insertHead(objPos thisPos)
{
    if(sizeList == sizeArray){
        return;
    }

    for(int i = sizeList; i > 0; i--)
    {
        aList[i] = aList[i - 1];
    }
    aList[0].setObjPos(thisPos.x,thisPos.y, thisPos.symbol);
    sizeList++;
}

void objPosArrayList::insertTail(objPos thisPos)
{
    if(sizeList == sizeArray){
    return;
    }
    aList[sizeList].setObjPos(thisPos.x,thisPos.y,thisPos.symbol);
    sizeList++;
}

void objPosArrayList::removeHead()
{
    for(int i = 0; i < sizeList-1; i++)
    {
        aList[i] = aList[i+1];
    }
    sizeList--;
}

void objPosArrayList::removeTail()
{
    sizeList--;
}

void objPosArrayList::getHeadElement(objPos &returnPos)
{
    returnPos.x = aList[0].x;
    returnPos.y = aList[0].y;
    returnPos.symbol = aList[0].symbol;
}

void objPosArrayList::getTailElement(objPos &returnPos)
{
    returnPos.x = aList[sizeList - 1].x;
    returnPos.y = aList[sizeList - 1].y;
    returnPos.symbol = aList[sizeList - 1].symbol;
}

void objPosArrayList::getElement(objPos &returnPos, int index)
{
    returnPos.x = aList[index].x;
    returnPos.y = aList[index].y;
    returnPos.symbol = aList[index].symbol;
}