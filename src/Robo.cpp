#include "Robo.h"

Robo::Robo(GameObject& associated, string file, Vec2 position, TileMap<TileInfo>* tileMap):
    Component(associated),
    tileMap(tileMap)
{
    DEBUG_CONSTRUCTOR("inicio");
    DEBUG_CONSTRUCTOR("position: " << position.x << ", " << position.y);
    PlayerUnity& playerUnity = *(new PlayerUnity(associated, position, tileMap ) );
    associated.AddComponent(&playerUnity);
    DEBUG_CONSTRUCTOR("Player Unity adicionado");
    sp = new Sprite(associated, file, true, ROBO_SHEET_FRAME_TIME, ROBO_SHEET_FRAMES);
    sp->SetAnimationLines(4);
    associated.AddComponent(sp);
    associated.box.w = sp->GetWidth();
    associated.box.h = sp->GetHeight();

    //ctor
    GameObject* unityMenu = associated.GetChildWithTag("UnityMenu");
    PlayerUnityMenu& playerUnityMenu = (dynamic_cast<PlayerUnityMenu&>(unityMenu->GetComponent(PLAYER_UNITY_MENU)));
    playerUnityMenu.AddButton(BOTAO4, this);

    DEBUG_CONSTRUCTOR("fim");
}

Robo::~Robo()
{
    //dtor
}

bool Robo::Is(unsigned int type) const{
    return (type == ROBO);
}

void Robo::Update(float dt){
}

void Robo::EarlyUpdate(float dt){
}

void Robo::LateUpdate(float dt){
}

void Robo::Render() const{
}

void Robo::EjectPilot(void* entry){
    DEBUG_PRINT("inicio");
    if(pilotos.size() > 0){
        GameObject* desembarcado = pilotos[0];
        desembarcado->box.x = associated.box.x + associated.box.w;
        desembarcado->box.y = associated.box.y;
        pilotos.erase(pilotos.begin());
        desembarcado->SetActive(true);
    }
    DEBUG_PRINT("fim");
}

void Robo::BoardPilot(GameObject* piloto){
    piloto->SetActive(false);
    pilotos.push_back(piloto);
}

void Robo::ButtonObserver(Component* btn){
    if(pilotos.size()){
        pilotos.back()->SetActive(true);
        pilotos.pop_back();
    }
}
