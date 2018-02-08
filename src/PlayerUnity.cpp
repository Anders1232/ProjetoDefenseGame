#include "../include/PlayerUnity.h"

#include "Error.h"
PlayerUnity::PlayerUnity(GameObject& associated, Vec2 position, TileMap<TileInfo>* tileMap):
    Component(associated),
    clicked(false),
    selected(false),
    characterStatus(* (new CharacterStatus(associated, tileMap)) ),
    barraVida( *(new GameObject("BarraVida", associated.GetContext())) ),
    barraCoolDown( *(new GameObject("BarraCoolDown", associated.GetContext())) ),
    playerUnityMenu(nullptr),
    tileMap(tileMap)
{
    DEBUG_CONSTRUCTOR("inicio");
    Vec2 pos = tileMap->MapToPixel(position);
    destination.x = associated.box.x = pos.x;
    destination.y = associated.box.y = pos.y;
    tileMap->At(position.x, position.y).PutCharacter(associated);

    /*
        CharacterStatus
    */
    associated.AddComponent(new CharacterStatus(associated, tileMap));

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

    (dynamic_cast<Bar&>(barraCoolDown.GetComponent(BAR))).SetRefilAuto(10);
    (dynamic_cast<Bar&>(barraCoolDown.GetComponent(BAR))).SetPoints(0);

    playerUnityMenu = new GameObject("UnityMenu", associated.GetContext());
    playerUnityMenu->SetParent(associated);
    PlayerUnityMenu* playerUnityMenuComponent = new PlayerUnityMenu(*playerUnityMenu);
    playerUnityMenu->AddComponent(playerUnityMenuComponent);

    associated.CreateNewObject(playerUnityMenu);
    playerUnityMenu->debug = true;

    movingPath = new GameObject("Path", associated.GetContext());
    movingPath->SetParent(associated);
    PlayerUnityPath* roboPathComponent = new PlayerUnityPath(*movingPath, tileMap, destination);
    movingPath->AddComponent(roboPathComponent);
    associated.CreateNewObject(movingPath);

    //roboPathComponent contem uma função que será atribuida a um botão do menu
    playerUnityMenuComponent->AddButton(BOTAO1, roboPathComponent);

    //O menu reage a um evento do roboPath:
    //Quando terminar de criar o caminho, os listeners serão chamados
    playerUnityMenuComponent->SubscribeToPath(*roboPathComponent);

    DEBUG_CONSTRUCTOR("box:{" <<
                      associated.box.x << ", " <<
                      associated.box.y << ", " <<
                      associated.box.w << ", " <<
                      associated.box.h << "}");
    DEBUG_CONSTRUCTOR("fim");
}

PlayerUnity::~PlayerUnity()
{
}

void PlayerUnity::Update(float dt)
{
    Vec2 currentPosition(associated.box.x, associated.box.y);
    if(destination != currentPosition){
        characterStatus.Walk(destination);//UpdateState();
    }
}

void PlayerUnity::Render() const
{
}

bool PlayerUnity::Is(unsigned int type)const
{
    return (type == PLAYER_UNITY);
}

void PlayerUnity::EarlyUpdate(float dt) {}
void PlayerUnity::LateUpdate(float dt) {}

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
    return destination;
}

GameObject* PlayerUnity::GetMenu(){
    return playerUnityMenu;
}

#include "Error_footer.h"
