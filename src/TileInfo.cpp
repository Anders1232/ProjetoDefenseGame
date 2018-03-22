#include "TileInfo.h"
//#include "GameObject.h"

TileInfo::TileInfo(int index):
    BaseTile(index),
    passable(true),
    isFree(true),
    characterInside(nullptr),
    reservedTo(nullptr)
{
    //ctor
}

TileInfo::~TileInfo()
{
    //dtor
}

void TileInfo::PutCharacter(GameObject& object){
    characterInside = &object;
    isFree = false;
}

void TileInfo::RemoveCharacter(){
    characterInside = nullptr;
    reservedTo = nullptr;
    isFree = true;
}


GameObject* TileInfo::GetCharacter(){
    return characterInside;
}

bool TileInfo::IsFree(GameObject& obj){
    return (isFree && reservedTo == nullptr) || (!isFree && reservedTo == &obj);
}

bool TileInfo::IsPassable(){
    return passable;
}

void TileInfo::ReserveTo(GameObject& object){
    reservedTo = &object;
}
