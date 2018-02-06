#include "TileInfo.h"

TileInfo::TileInfo(int index):
    BaseTile(index),
    passable(true),
    characterInside(nullptr)
{
    //ctor
}

TileInfo::~TileInfo()
{
    //dtor
}

void TileInfo::PutCharacter(GameObject* object){
    characterInside = object;
}

void TileInfo::RemoveCharacter(){
    characterInside = nullptr;
}


GameObject* TileInfo::GetCharacter(){
    return characterInside;
}


