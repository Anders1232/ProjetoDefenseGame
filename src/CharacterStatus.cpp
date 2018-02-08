#include "CharacterStatus.h"
#include "Error.h"
CharacterStatus::CharacterStatus(GameObject& associated,
                                 float hp, float mp,
                                 float speed, int range,
                                 float attack, float defense,
                                 float magic, float resistence):
    Component(associated),
    hp(hp),
    mp(mp),
    speed(speed),
    range(range),
    attack(attack),
    defense(defense),
    magic(magic),
    resistence(resistence)

{
    //ctor
}

CharacterStatus::~CharacterStatus()
{
    //dtor
}

void CharacterStatus::EarlyUpdate(float dt){}
void CharacterStatus::Update(float dt){}
void CharacterStatus::LateUpdate(float dt){}
void CharacterStatus::Render(){}
bool CharacterStatus::Is(unsigned int type) const{
    return GameComponentType::CHARACTER_STATUS == type;
}
