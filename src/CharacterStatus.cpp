#include "CharacterStatus.h"
#include "Error.h"
#include "GameComponentType.h"

CharacterStatus::CharacterStatus(GameObject& associated,
                                 TileMap<TileInfo>* tileMap,
                                 float hp, float mp,
                                 float speed, int range,
                                 float attack, float defense,
                                 float magic, float resistence):
    Component(associated),
    tileMap(tileMap),
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

void CharacterStatus::Update(float dt){
}

void CharacterStatus::LateUpdate(float dt){}
void CharacterStatus::Render(){}
bool CharacterStatus::Is(unsigned int type) const{
    DEBUG_PRINT("My type: " << GameComponentType::CHARACTER_STATUS );
    DEBUG_PRINT("Type: " << type );
    return GameComponentType::CHARACTER_STATUS == type;
}
void CharacterStatus::Walk(Vec2 destination){
    Vec2 currentPosition(associated.box.x, associated.box.y);
    if(destination.x > currentPosition.x)
    {
        if(direction != RIGHT) ChangeDirection(RIGHT);
        associated.box.x += speed;
    }
    else if(destination.x < currentPosition.x)
    {
        if(direction != LEFT) ChangeDirection(LEFT);
        associated.box.x -= speed;
    }
    if(destination.y > currentPosition.y)
    {
        if(direction != DOWN) ChangeDirection(DOWN);
        associated.box.y += speed;
    }
    else if(destination.y < currentPosition.y)
    {
        if(direction != UP) ChangeDirection(UP);
        associated.box.y -= speed;
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
        (dynamic_cast<Sprite&>(associated.GetComponent(SPRITE))).SetAnimationLine(1);
        break;
    case RIGHT:
        direction = RIGHT;
        (dynamic_cast<Sprite&>(associated.GetComponent(SPRITE))).SetAnimationLine(2);
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

vector<Vec2> CharacterStatus::CellsInRange(){
    DEBUG_PRINT("inicio");
    vector<Vec2> cells;// = new vector<Vec2>;
    Vec2 currentPosition(tileMap->PixelToMap(associated.GetPosition())) ;
    for(int i = currentPosition.x - range; i < currentPosition.x +1 + range; i++){
        for(int j = currentPosition.y - range; j < currentPosition.y +1 + range; j++){
            cells.push_back(Vec2(i, j));
        }
    }
    DEBUG_PRINT("fim");
    return cells;
}
