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
void CharacterStatus::Walk(Vec2 destination){
    Vec2 currentPosition(associated.box.x, associated.box.y);
    if(destination.x > currentPosition.x)
    {
        if(direction != RIGHT) ChangeDirection(RIGHT);
        associated.box.x += 1;
    }
    else if(destination.x < currentPosition.x)
    {
        if(direction != LEFT) ChangeDirection(LEFT);
        associated.box.x -= 1;
    }
    if(destination.y > currentPosition.y)
    {
        if(direction != DOWN) ChangeDirection(DOWN);
        associated.box.y += 1;
    }
    else if(destination.y < currentPosition.y)
    {
        if(direction != UP) ChangeDirection(UP);
        associated.box.y -= 1;
    }
}

void CharacterStatus::ChangeDirection(Direction dir)
{
    DEBUG_PRINT("inicio");
    switch(dir)
    {
    case UP:
        direction = UP;
        (dynamic_cast<Sprite&>(associated.GetComponent(SPRITE))).SetAnimationLine(3);
        break;
    case DOWN:
        direction = DOWN;
        (dynamic_cast<Sprite&>(associated.GetComponent(SPRITE))).SetAnimationLine(0);
        break;
    case LEFT:
        direction = LEFT;
        (dynamic_cast<Sprite&>(associated.GetComponent(SPRITE))).SetAnimationLine(2);
        break;
    case RIGHT:
        direction = RIGHT;
        (dynamic_cast<Sprite&>(associated.GetComponent(SPRITE))).SetAnimationLine(1);
        break;
    }
    DEBUG_PRINT("fim");
}

void CharacterStatus::debug()
{
    if(associated.debug)
    {
        if(InputManager::GetInstance().KeyPress(SDLK_LEFT))
        {
            ChangeDirection(LEFT);
        }
        if(InputManager::GetInstance().KeyPress(SDLK_UP))
        {
            ChangeDirection(UP);
        }
        if(InputManager::GetInstance().KeyPress(SDLK_RIGHT))
        {
            ChangeDirection(RIGHT);
        }
        if(InputManager::GetInstance().KeyPress(SDLK_DOWN))
        {
            ChangeDirection(DOWN);
        }
    }
    if(InputManager::GetInstance().KeyPress(SDLK_0))
    {
        associated.debug = !associated.debug;
    }
}

