#include "CharacterStatus.h"
#include "GameObject.h"
#include "Sprite.h"


#include "Error.h"

using std::vector;

CharacterStatus::CharacterStatus(GameObject& associated,
                                 Vec2 position,
                                 TileMap<TileInfo>* tileMap,
                                 float hp, float mp,
                                 float speed, int range,
                                 float attack, float defense,
                                 float magic, float resistence):
    Component(associated),
    tileMap(tileMap),
    destination(nullptr),
    hp(hp),
    mp(mp),
    speed(speed),
    range(range),
    attack(attack),
    defense(defense),
    magic(magic),
    resistence(resistence),
    pathVerifyed(false),
    charState(IDLE)

{
    associated.SetPosition(tileMap->MapToPixel(position));
    tileMap->At(position.x, position.y).PutCharacter(associated);
}

CharacterStatus::~CharacterStatus()
{
    //dtor
}

void CharacterStatus::EarlyUpdate(float dt){}

void CharacterStatus::Update(float dt){
    DEBUG_UPDATE("inicio");
    DEBUG_UPDATE("fim");
}

void CharacterStatus::LateUpdate(float dt){}
void CharacterStatus::Render(){}
bool CharacterStatus::Is(unsigned int type) const{
    DEBUG_PRINT("My type: " << GameComponentType::CHARACTER_STATUS );
    DEBUG_PRINT("Type: " << type );
    return GameComponentType::CHARACTER_STATUS == type;
}
void CharacterStatus::Walk(){
    if( *destination == associated.box){
        DEBUG_PRINT("Cheguei no destino.");
        delete(destination);
        destination = nullptr;
        pathVerifyed = false;
    }else{
        Vec2 currentPosition(associated.box);
        Vec2 currentGridPosition(tileMap->PixelToMap(associated.box));
        Vec2 destinationGridPosition = tileMap->PixelToMap(*destination);

        /*
            *   Sempre que o personagem for andar, ele deve checar antes se
            *   a posição pra onde ele pretende ir está vazia.
            */
        if(!pathVerifyed){
            if(tileMap->At(destinationGridPosition.x, destinationGridPosition.y).IsPassable() &&
               tileMap->At(destinationGridPosition.x, destinationGridPosition.y).IsFree() ){
                tileMap->At(destinationGridPosition.x, destinationGridPosition.y).PutCharacter(associated);
                tileMap->At(currentGridPosition.x, currentGridPosition.y).RemoveCharacter();
                pathVerifyed = true;
                DEBUG_PRINT("Celula de destino " << destinationGridPosition.x << " ," << destinationGridPosition.y << " reservada.");
                DEBUG_PRINT("Celula que ocupava " << currentGridPosition.x << " ," << currentGridPosition.y << " liberada.");
            }
        }else{
            DEBUG_PRINT("Andando");
            if(destination->x > currentPosition.x)
            {
                if(direction != RIGHT) ChangeDirection(RIGHT);
                associated.box.x += speed;
            }
            else if(destination->x < currentPosition.x)
            {
                if(direction != LEFT) ChangeDirection(LEFT);
                associated.box.x -= speed;
            }
            if(destination->y > currentPosition.y)
            {
                if(direction != DOWN) ChangeDirection(DOWN);
                associated.box.y += speed;
            }
            else if(destination->y < currentPosition.y)
            {
                if(direction != UP) ChangeDirection(UP);
                associated.box.y -= speed;
            }
        }
    }
}

void CharacterStatus::ChangeDirection(Direction dir)
{
    DEBUG_PRINT("inicio");
    switch(dir)
    {
    case UP:
        direction = UP;
        //(dynamic_cast<Sprite&>(associated.GetComponent(SPRITE))).SetAnimationLine(3);
        associated.GetComponent<Sprite>().SetAnimationLine(3);
        break;
    case DOWN:
        direction = DOWN;
        //(dynamic_cast<Sprite&>(associated.GetComponent(SPRITE))).SetAnimationLine(0);
        associated.GetComponent<Sprite>().SetAnimationLine(0);
        break;
    case LEFT:
        direction = LEFT;
        //(dynamic_cast<Sprite&>(associated.GetComponent(SPRITE))).SetAnimationLine(1);
        associated.GetComponent<Sprite>().SetAnimationLine(1);
        break;
    case RIGHT:
        direction = RIGHT;
        //(dynamic_cast<Sprite&>(associated.GetComponent(SPRITE))).SetAnimationLine(2);
        associated.GetComponent<Sprite>().SetAnimationLine(2);
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
    vector<Vec2> cells;
    Vec2 currentPosition(tileMap->PixelToMap(associated.GetPosition())) ;
    for(int i = currentPosition.x - range; i < currentPosition.x +1 + range; i++){
        for(int j = currentPosition.y - range; j < currentPosition.y +1 + range; j++){
            cells.push_back(Vec2(i, j));
        }
    }
    DEBUG_PRINT("fim");
    return cells;
}
