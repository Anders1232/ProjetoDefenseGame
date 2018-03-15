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
    barraVida( *(new GameObject("BarraVida", associated.GetContext())) ),
    barraCoolDown( *(new GameObject("BarraCoolDown", associated.GetContext())) ),
    piloto(nullptr),
    movingPath(nullptr),
    playerUnityMenu(nullptr),
    clicked(false),
    selected(false),
    walkPressed(false),
    tileMap(tileMap)
{
    DEBUG_CONSTRUCTOR("inicio: [ " << this << "]");
    /*
        Barra de vida
    */
    barraVida.SetParent(associated, -16, 64);//Hardcoded = posicionando a barra em relação ao parent
    barraVida.AddComponent(new Bar(barraVida, 200, BARRA_VIDA_MOLDURA, BARRA_VIDA));
    associated.CreateNewObject(&barraVida);

    /*
        Barra de cooldown
    */
    barraCoolDown.SetParent(associated, -14, 74);//Hardcoded = posicionando a barra em relação ao parent
    barraCoolDown.AddComponent(new Bar(barraCoolDown, 10, BARRA_COOLDDOWN_MOLDURA, BARRA_COOLDOWN));
    associated.CreateNewObject(&barraCoolDown);

    barraCoolDown.GetComponent<Bar>().SetRefilAuto(10);
    barraCoolDown.GetComponent<Bar>().SetPoints(0);

    playerUnityMenu = new GameObject("UnityMenu", associated.GetContext());
    playerUnityMenu->SetParent(associated);
    PlayerUnityMenu* playerUnityMenuComponent = new PlayerUnityMenu(*playerUnityMenu);
    playerUnityMenu->AddComponent(playerUnityMenuComponent);

    associated.CreateNewObject(playerUnityMenu);
    playerUnityMenu->debug = true;

    GameObject* movingPathObject = new GameObject("Path", associated.GetContext());
    movingPathObject->SetParent(associated);

    movingPath = new PlayerUnityPath(*movingPathObject, tileMap, destination);
    movingPathObject->AddComponent(movingPath);
    associated.CreateNewObject(movingPathObject);

    //playerUnity contem uma função que será atribuida a um botão do menu
    playerUnityMenuComponent->AddButton(BOTAO1, "Andar", this);

    //O menu reage a um evento do movingPath:
    //Quando terminar de criar o caminho, os listeners serão chamados
    playerUnityMenuComponent->SubscribeToPath(*movingPath);

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
    DEBUG_UPDATE("inicio");
    CharacterStatus::Update(dt);
    switch(charState){
    case CharacterState::IDLE:
        if(walkPressed){
            if(movingPath->HasPoints()){
                SetDestination(movingPath->GetNext() );
                charState = CharacterState::WALKING;
            }else{
                walkPressed = false;
            }
        }
        break;
    case CharacterState::WALKING:
        if(destination == nullptr){
            charState = IDLE;
        }else{
            Walk();
        }
        break;
    }
    DEBUG_UPDATE("fim");
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
    if(dynamic_cast<Button&>(*btn).name == "Andar"){
        walkPressed = true;
    }
    DEBUG_PRINT("fim");
}


#include "Error_footer.h"
