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
    lastPosition(nullptr),
    walkDirection(nullptr),
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
    vector<Vec2>cells = CellsInRange();
    for(auto it = cells.begin(); it != cells.end(); it++){
        GameObject* someChar = tileMap->At(it->x, it->y).GetCharacter();
        if( someChar && someChar != &associated &&
           *it != tileMap->PixelToMap(associated.box)){
            DEBUG_PRINT("cell: " << it->x << ", " << it->y);
            DEBUG_PRINT("SOMEONE HERE!");
        }else{
            //DEBUG_PRINT("no one here...!");
        }
    }
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
    if(destination == nullptr) return;

    Vec2 currentGridPosition(tileMap->PixelToMap(associated.box));

    if( *destination == currentGridPosition){//se chegou ao destino
        StopWalking(*destination);
    }else{//se não chegou ao destino
        Vec2 negativeDirection( walkDirection->x == -1, walkDirection->y == -1);
        if(lastPosition == nullptr){//e está rodando pela primeira vez
            lastPosition = new Vec2(currentGridPosition);//consider-se a posição atual como "ultima posição"
        }else if(*lastPosition != currentGridPosition + negativeDirection){//se last e current forem diferentes, o personagem ja andou um quadrado
            *lastPosition = currentGridPosition + negativeDirection;
            pathVerifyed = false;//deve verificar novamente se o caminho está livre
        }

        Vec2 nextGridPosition = currentGridPosition + *walkDirection + negativeDirection;
        if(!pathVerifyed){
           if(tileMap->At(nextGridPosition.x, nextGridPosition.y).IsPassable()){
              if(tileMap->At(nextGridPosition.x, nextGridPosition.y).IsFree() ){
                tileMap->At(nextGridPosition.x, nextGridPosition.y).PutCharacter(associated);//reserva a posição
                tileMap->At(lastPosition->x, lastPosition->y).RemoveCharacter();
                pathVerifyed = true;
              }else{
                  //Non-Empty
                  charState = ATTAKCING;
                  StopWalking(currentGridPosition);
              }
           }else{
               //Non-Passable
           }
                //DEBUG_PRINT("Celula que ocupava " << lastPosition->x << " ," << lastPosition->y << " liberada.");
                //DEBUG_PRINT("Celula de destino " << nextGridPosition.x << " ," << nextGridPosition.y << " reservada.");
        }else{
            //DEBUG_PRINT("Andando");
            Vec2 currentPosition(associated.box);
            Vec2 pixelDestination = tileMap->MapToPixel(*destination);
            if(pixelDestination.x > associated.box.x)
            {
                if(direction != RIGHT) ChangeDirection(RIGHT);
                associated.box.x += speed;
            }
            else if(pixelDestination.x < associated.box.x)
            {
                if(direction != LEFT) ChangeDirection(LEFT);
                associated.box.x -= speed;
            }
            if(pixelDestination.y > associated.box.y)
            {
                if(direction != DOWN) ChangeDirection(DOWN);
                associated.box.y += speed;
            }
            else if(pixelDestination.y < associated.box.y)
            {
                if(direction != UP) ChangeDirection(UP);
                associated.box.y -= speed;
            }
        }
    }
}

void CharacterStatus::StopWalking(Vec2 position){
    if(walkDirection->x < 0){
        destination->x += 1;
    }else if(walkDirection->y < 0){
        destination->y += 1;
    }
    associated.SetPosition(tileMap->MapToPixel(position));

    tileMap->At(lastPosition->x, lastPosition->y).RemoveCharacter();//remove o personagem da posição anterior
    delete(lastPosition);
    lastPosition = nullptr;

    delete(destination);
    destination = nullptr;
    pathVerifyed = false;
    delete(walkDirection);
    walkDirection = nullptr;
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
    //DEBUG_PRINT("inicio");
    vector<Vec2> cells;
    Vec2 currentPosition(tileMap->PixelToMap(associated.GetPosition())) ;
    for(int i = currentPosition.x - range; i < currentPosition.x +1 + range; i++){
        for(int j = currentPosition.y - range; j < currentPosition.y +1 + range; j++){
            cells.push_back(Vec2(i, j));
        }
    }
    //DEBUG_PRINT("fim");
    return cells;
}

void CharacterStatus::SetDestination(Vec2 destination){
    DEBUG_PRINT("inicio");
    Vec2 currentPosition = tileMap->PixelToMap(associated.box);
    walkDirection = new Vec2( destination - currentPosition);
    walkDirection->Normalize();
    if(walkDirection->x + walkDirection->y > 0){
        this->destination = new Vec2(destination);
    }else if(walkDirection->x + walkDirection->y < 0){
        this->destination = new Vec2(destination);
        *(this->destination) += *walkDirection;
    }else{
        delete(walkDirection);
        walkDirection = nullptr;
    }
    DEBUG_PRINT("fim");
}
