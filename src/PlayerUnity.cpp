#include "../include/PlayerUnity.h"

#include "GameObject.h"
#include "State.h"
#include "Camera.h"
#include "Button.h"

#include "PlayerUnityPath.h"
#include "PlayerUnityMenu.h"
#include "Bar.h"
#include "CharacterStatus.h"
#include "resources_path.h"


#include "Error.h"

using std::string;
using std::vector;

PlayerUnity::PlayerUnity(GameObject& associated, Vec2 position, TileMap<TileInfo>* tileMap):
    CharacterStatus(associated, position, tileMap),
    piloto(nullptr),
    movingPath(nullptr),
    playerUnityMenu(nullptr),
    clicked(false),
    selected(false),
    walkPressed(false),
    tileMap(tileMap)
{
    DEBUG_CONSTRUCTOR("inicio: [ " << this << "]");
    charType = CharacterType::PLAYER_UNITY;
    SetStatus(50, 10, 30, 1, 3, 2, 1 ,0, 5, 3);
    /*
        Barra de vida
    */
    GameObject* barraVidaObject = new GameObject("BarraVida", associated.GetContext());
    barraVida = new Bar(*barraVidaObject, status.hp, BARRA_VIDA_MOLDURA, BARRA_VIDA);
    barraVidaObject->SetParent(associated, -16, 64);//Hardcoded = posicionando a barra em relação ao parent
    barraVidaObject->AddComponent(barraVida);
    associated.CreateNewObject(barraVidaObject);

    /*
        Barra de cooldown
    */
    GameObject* barraCoolDownObject = new GameObject("BarraCoolDown", associated.GetContext());
    barraCoolDown = new Bar(*barraCoolDownObject, status.coolDown, BARRA_COOLDDOWN_MOLDURA, BARRA_COOLDOWN);
    barraCoolDownObject->SetParent(associated, -14, 74);//Hardcoded = posicionando a barra em relação ao parent
    barraCoolDownObject->AddComponent(barraCoolDown);
    associated.CreateNewObject(barraCoolDownObject);

    barraCoolDown->SetRefilAuto(status.coolDown);
    barraCoolDown->SetPoints(0);

    /*
        Player Menu
    */
    playerUnityMenu = new GameObject("UnityMenu", associated.GetContext());
    playerUnityMenu->SetParent(associated);
    PlayerUnityMenu* playerUnityMenuComponent = new PlayerUnityMenu(*playerUnityMenu);
    playerUnityMenu->AddComponent(playerUnityMenuComponent);

    associated.CreateNewObject(playerUnityMenu);
    playerUnityMenu->debug = true;

    /*
        Player Path
    */
    GameObject* movingPathObject = new GameObject("Path", associated.GetContext());
    movingPathObject->SetParent(associated);

    movingPath = new PlayerUnityPath(*movingPathObject, tileMap, destination);
    movingPathObject->AddComponent(movingPath);
    associated.CreateNewObject(movingPathObject);

    //playerUnity contem uma função que será atribuida a um botão do menu
    playerUnityMenuComponent->AddButton(BOTAO1, "Andar", this);

    //O menu reage a um evento do movingPath:
    //Quando terminar de criar o caminho, os listeners serão chamados
    movingPath->pathFinished.Subscribe(playerUnityMenuComponent->OnPathFinished, playerUnityMenuComponent);

    DEBUG_CONSTRUCTOR("box:{" <<
                      associated.box.x << ", " <<
                      associated.box.y << ", " <<
                      associated.box.w << ", " <<
                      associated.box.h << "}");
    DEBUG_CONSTRUCTOR("fim: [ " << this << "]");
}

PlayerUnity::~PlayerUnity()
{
}

void PlayerUnity::Update(float dt)
{
    DEBUG_UPDATE("PlayerUnity::inicio");
    CharacterStatus::Update(dt);
    switch(charState){
        case CharacterState::IDLE:
            if(charactersInRange.size()>0){
                for(unsigned int i = 0; i < charactersInRange.size(); i++){
                    if(charactersInRange[i]->charType == CharacterType::ENEMY){
                        charState = CharacterState::ATTAKCING;
                        CharacterStatus::Attack(charactersInRange[i]);
                    }
                }
            }
            break;
        case CharacterState::ATTAKCING:
            attackTimer.Update(dt);
            Attack(CharacterType::ENEMY);
            break;
        case CharacterState::WALKING:
            Walk(dt);
            break;
        case CharacterState::DEAD:
            break;
    }
    DEBUG_UPDATE("PlayerUnity::fim");
}

void PlayerUnity::Render() const
{
}

bool PlayerUnity::Is(unsigned int type)const
{
    return (type == PLAYER_UNITY);
}

void PlayerUnity::EarlyUpdate(float dt) {
    CharacterStatus::EarlyUpdate(dt);
}
void PlayerUnity::LateUpdate(float dt) {
    CharacterStatus::LateUpdate(dt);
}

void PlayerUnity::onClick()
{

}

void PlayerUnity::MenuOpen()
{
}

void PlayerUnity::MenuClose()
{
    playerUnityMenu->RequestDelete();
    playerUnityMenu = nullptr;
}

void PlayerUnity::SetPosition(float x, float y)
{
    associated.box.x = x;
    associated.box.y = y;
}

Vec2& PlayerUnity::Destination()
{
    return *destination;
}

GameObject* PlayerUnity::GetMenu(){
    return playerUnityMenu;
}

void PlayerUnity::ButtonObserver(Component* btn){
    DEBUG_PRINT("inicio");
    DEBUG_PRINT("button clicked: " << (dynamic_cast<Button&>(*btn)).name );
    if(dynamic_cast<Button&>(*btn).name == "Andar"){
        DEBUG_PRINT("Mudando estado para WALKING");
        if(barraCoolDown->GetPercentPoints() == Bar_FULL){
            barraCoolDown->SetPoints(0);
            barraCoolDown->refilAuto = false;
            charState = CharacterState::WALKING;
            SetDestination(movingPath->GetNext());
        }
    }
    DEBUG_PRINT("fim");
}

void PlayerUnity::ReceiveDamage(int damage){
    DEBUG_PRINT("inicio");
    CharacterStatus::ReceiveDamage(damage);
    barraVida->SetPoints(status.hp);
    DEBUG_PRINT("hp: " << status.hp);
    DEBUG_PRINT("fim");
}

void PlayerUnity::Walk(float dt){
    DEBUG_UPDATE("inicio");
    if(destination == nullptr){
        if(movingPath->HasPoints()){
            SetDestination(movingPath->GetNext());
        }else{
            charState = CharacterState::IDLE;
            barraCoolDown->refilAuto = true;
        }
    }else{
        CharacterStatus::Walk(dt);
    }
    DEBUG_UPDATE("fim");
}

bool PlayerUnity::Attack(CharacterType other){
    DEBUG_UPDATE("inicio");
    bool attacked = false;
    if(attackTimer.Get() > status.attackCoolDown){
        attackTimer.Restart();
        if(charactersInRange.size()>0){
            for(unsigned int i = 0; i < charactersInRange.size(); i++){
                if(charactersInRange[i]->charType == other){
                    attacked = true;
                    charState = CharacterState::ATTAKCING;
                    CharacterStatus::Attack(charactersInRange[i]);
                }
            }
        }else{
            charState = CharacterState::IDLE;
        }
    }
    return attacked;
    DEBUG_UPDATE("fim");
}

#include "Error_footer.h"
