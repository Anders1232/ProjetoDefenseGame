#include "TileInfo.h"
//#include "GameObject.h"

TileInfo::TileInfo(int index):
    BaseTile(index),
    passable(true),
    isFree(true),
    characterInside(nullptr)
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
    isFree = true;
}


GameObject* TileInfo::GetCharacter(){
    return characterInside;
}

bool TileInfo::IsFree(){
    return isFree;
}

bool TileInfo::IsPassable(){
    return passable;
}
