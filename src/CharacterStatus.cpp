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
    charState(IDLE),
    delta(0.5)

{
    tileMap->At(position.x, position.y).PutCharacter(associated);
}

CharacterStatus::~CharacterStatus()
{
    //dtor
}

void CharacterStatus::EarlyUpdate(float dt){}

void CharacterStatus::Update(float dt){
    DEBUG_UPDATE("inicio");
    /*
    vector<Vec2>cells = CellsInRange();
    for(auto it = cells.begin(); it != cells.end(); it++){
        GameObject* someChar = tileMap->At(it->x, it->y).GetCharacter();
        if( someChar && someChar != &associated &&
           *it != tileMap->PixelToMap(associated.box.Center())){
            //DEBUG_PRINT("cell: " << it->x << ", " << it->y);
            //DEBUG_PRINT("SOMEONE HERE!");
        }else{
            //DEBUG_PRINT("no one here...!");
        }
    }*/
    DEBUG_UPDATE("fim");
}

void CharacterStatus::LateUpdate(float dt){}
void CharacterStatus::Render(){}
bool CharacterStatus::Is(unsigned int type) const{
    return GameComponentType::CHARACTER_STATUS == type;
}

void CharacterStatus::Walk(){
    DEBUG_UPDATE("inicio");
    /*
    if(destination){
        DEBUG_PRINT("destination: " << destination->x << ", " << destination->y);
    }
    */
    if(destination == nullptr) return;

    Vec2 currentPosition(associated.box.Center());
    //DEBUG_PRINT("currentPosition: " << currentPosition.x << ", " << currentPosition.y);
    Vec2 destinationOnWorld = tileMap->CellCenterToPixel(*destination);
    if( destinationOnWorld.x - delta <= currentPosition.x && currentPosition.x <= destinationOnWorld.x + delta &&
        destinationOnWorld.y - delta <= currentPosition.y && currentPosition.y <= destinationOnWorld.y + delta){//se chegou ao destino
        StopWalking();
    }else{//se não chegou ao destino
        Vec2 currentGridPosition(tileMap->PixelToMap(associated.box.Center()));
        if(*lastGridPosition != currentGridPosition &&
           *destination != currentGridPosition){
            pathVerifyed = false;
            *lastGridPosition = currentGridPosition;
        }

        if(!pathVerifyed){
            //DEBUG_PRINT("pathNotVerifyed");
            Vec2 nextGridPosition = currentGridPosition + *walkDirection;
            //DEBUG_PRINT("currentGridPosition: " << currentGridPosition.x << ", " << currentGridPosition.y);
            //DEBUG_PRINT("nextGridPosition: " << nextGridPosition.x << ", " << nextGridPosition.y);

            if(tileMap->At(nextGridPosition.x, nextGridPosition.y).IsPassable()){
                //DEBUG_PRINT("is passable");
                if(tileMap->At(nextGridPosition.x, nextGridPosition.y).IsFree()){
                    //DEBUG_PRINT("is free");
                    tileMap->At(nextGridPosition.x, nextGridPosition.y).PutCharacter(associated);//reserva a posição
                    tileMap->At(currentGridPosition.x, currentGridPosition.y).RemoveCharacter();
                    pathVerifyed = true;
                }else{
                    //Non-Empty
                    //DEBUG_PRINT("is not free");
                    StopWalking();
                    //charState = ATTAKCING;
                }
            }else{
                //DEBUG_PRINT("is not passable");
                //Non-Passable
            }
        }else{ // Caminho já verificado e livre
            //DEBUG_PRINT("pathVerifyed");
            Vec2 currentPosition(associated.box.Center());
            Vec2 pixelDestination = tileMap->CellCenterToPixel(*destination);
            if(pixelDestination.x > associated.box.Center().x)
            {
                if(direction != RIGHT) ChangeDirection(RIGHT);
                associated.box.x += speed;
            }
            else if(pixelDestination.x < associated.box.Center().x)
            {
                if(direction != LEFT) ChangeDirection(LEFT);
                associated.box.x -= speed;
            }
            if(pixelDestination.y > associated.box.Center().y)
            {
                if(direction != DOWN) ChangeDirection(DOWN);
                associated.box.y += speed;
            }
            else if(pixelDestination.y < associated.box.Center().y)
            {
                if(direction != UP) ChangeDirection(UP);
                associated.box.y -= speed;
            }
        }
    }
    DEBUG_UPDATE("fim");
}

void CharacterStatus::StopWalking(){
    DEBUG_PRINT("inicio");
    associated.SetCenterPosition(tileMap->CellCenterToPixel(tileMap->PixelToMap(associated.box.Center())));

    delete(lastGridPosition);
    lastGridPosition = nullptr;
    delete(destination);
    destination = nullptr;
    pathVerifyed = false;
    delete(walkDirection);
    walkDirection = nullptr;
    DEBUG_PRINT("fim");
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
    Vec2 currentPosition = tileMap->PixelToMap(associated.box.Center());
    walkDirection = new Vec2( destination - currentPosition);
    walkDirection->Normalize();
    lastGridPosition = new Vec2(currentPosition);

    if(walkDirection->x + walkDirection->y > 0 ||
       walkDirection->x + walkDirection->y < 0){
        this->destination = new Vec2(destination);
    }else{
        delete(walkDirection);
        walkDirection = nullptr;
    }

    DEBUG_PRINT("fim");
}
