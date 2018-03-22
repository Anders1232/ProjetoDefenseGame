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
    lastGridPosition(nullptr),
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
    DEBUG_UPDATE("Character::inicio");
    charactersInRange = CharactersInRange();
    DEBUG_UPDATE("Character::fim");
}

void CharacterStatus::LateUpdate(float dt){}
void CharacterStatus::Render(){}
bool CharacterStatus::Is(unsigned int type) const{
    return GameComponentType::CHARACTER_STATUS == type;
}

void CharacterStatus::Walk(){
    DEBUG_UPDATE("inicio");
    if(destination){
        //DEBUG_PRINT("destination: " << destination->x << ", " << destination->y);
    }
    if(destination == nullptr) return;
    if(tileMap->PixelToMap(associated.box.Center()) != *lastGridPosition){
        DEBUG_PRINT("Mudou de celula: " <<
                    lastGridPosition->x << ", " << lastGridPosition->y << " -> " <<
                    tileMap->PixelToMap(associated.box.Center()).x << ", " <<
                    tileMap->PixelToMap(associated.box.Center()).y);
        pathVerifyed = false;
        tileMap->At(lastGridPosition->x, lastGridPosition->y).RemoveCharacter();
        *lastGridPosition = tileMap->PixelToMap(associated.box.Center());
        tileMap->At(lastGridPosition->x, lastGridPosition->y).PutCharacter(associated);

    }

    Vec2 currentWorldPosition(associated.box.Center());
    //DEBUG_PRINT("currentWorldPosition: " << currentWorldPosition.x << ", " << currentWorldPosition.y);
    //se não foi verificado e chegou perto do centro
    if(!pathVerifyed && tileMap->NearCellCenter(currentWorldPosition, delta)){
        //DEBUG_PRINT("Caminho a frente nao verificado");
        //DEBUG_PRINT("perto do centro da celula");
        if(tileMap->PixelToMap(currentWorldPosition) == *destination){
            //DEBUG_PRINT("Chegou na celula destino");
            StopWalking();
        }else{
            //DEBUG_PRINT("Nao chegou na celula de destino");
            //caso contrário, verifica o proximo
            Vec2 currentGridPosition(tileMap->PixelToMap(associated.box.Center()));
            Vec2 nextGridPosition = currentGridPosition + *walkDirection;
            //DEBUG_PRINT("currentGridPosition: " << currentGridPosition.x << ", " << currentGridPosition.y);
            //DEBUG_PRINT("nextGridPosition: " << nextGridPosition.x << ", " << nextGridPosition.y);
            if(tileMap->At(nextGridPosition.x, nextGridPosition.y).IsPassable()){
                //DEBUG_PRINT("is passable");
                if(tileMap->At(nextGridPosition.x, nextGridPosition.y).IsFree(associated)){
                    //DEBUG_PRINT("is free");
                    tileMap->At(nextGridPosition.x, nextGridPosition.y).ReserveTo(associated);
                    //tileMap->At(nextGridPosition.x, nextGridPosition.y).PutCharacter(associated);//reserva a posição
                    //tileMap->At(currentGridPosition.x, currentGridPosition.y).RemoveCharacter();
                    pathVerifyed = true;
                }else{
                    //Non-Empty
                    //DEBUG_PRINT("is not free");
                    StopWalking();
                    charState = ATTAKCING;
                }
            }else{
                //DEBUG_PRINT("is not passable");
                //Non-Passable
            }
        }
    }else{
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
            if(i >= 0 && j >= 0 ){
                cells.push_back(Vec2(i, j));
            }
        }
    }
    //DEBUG_PRINT("fim");
    return cells;
}

vector<CharacterStatus*> CharacterStatus::CharactersInRange(){
    DEBUG_UPDATE("inicio");
    vector<CharacterStatus*> characters;
    Vec2 currentPosition(tileMap->PixelToMap(associated.GetPosition())) ;
    for(int i = currentPosition.x - range; i < currentPosition.x +1 + range; i++){
        if(i < 0) continue;
        for(int j = currentPosition.y - range; j < currentPosition.y +1 + range; j++){
            if(j < 0) continue;
            GameObject* character = tileMap->At(i, j).GetCharacter();
            if(character && character != &associated){
                characters.push_back(&character->GetComponent<CharacterStatus>());
            }
        }
    }
    DEBUG_UPDATE("fim");
    return characters;
}

void CharacterStatus::SetDestination(Vec2 destination){
    DEBUG_PRINT("inicio");
    Vec2 currentWorldPosition = tileMap->PixelToMap(associated.box.Center());
    walkDirection = new Vec2( destination - currentWorldPosition);
    walkDirection->Normalize();

    if(walkDirection->x + walkDirection->y > 0 ||
       walkDirection->x + walkDirection->y < 0){
        this->destination = new Vec2(destination);
        lastGridPosition = new Vec2(tileMap->PixelToMap(associated.box.Center()));
    }else{
        delete(walkDirection);
        walkDirection = nullptr;
    }

    DEBUG_PRINT("fim");
}

void CharacterStatus::Attack(CharacterStatus* character){
    DEBUG_PRINT("inicio");
    DEBUG_PRINT("[ " << this << " ] attacking [ " << character <<" ]" );
    character->ReceiveDamage(attack);
    DEBUG_PRINT("fim");
}

void CharacterStatus::ReceiveDamage(int damage){
    DEBUG_PRINT("inicio");
    hp -= damage - defense;
    if(hp <= 0){
        Die();
    }
    DEBUG_PRINT("fim");
}

void CharacterStatus::Die(){
    DEBUG_PRINT("Dead");
    charState = CharacterState::DEAD;
    Vec2 currentPosition = Vec2(tileMap->PixelToMap(associated.box.Center()));
    tileMap->At(currentPosition.x, currentPosition.y).RemoveCharacter();

    //associated.RequestDelete();
    DEBUG_PRINT("Dead");
}
