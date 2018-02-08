#ifndef GAMECOMPONENTTYPE_H
#define GAMECOMPONENTTYPE_H

#include "ComponentType.h"

enum GameComponentType{
	PLAYER_UNITY= ComponentType::COMPONENT_TYPE_SIZE,
	CHARACTER_STATUS,
	BAR,
    ROBO,
    PILOTO,
    PLAYER_UNITY_PATH,
    PLAYER_UNITY_MENU,
    CURSOR,
    PATH_MARKER,
    ENEMY
};

#endif // GAMECOMPONENTTYPE_H
