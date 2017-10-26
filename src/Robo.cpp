#include "Robo.h"

Robo::Robo(GameObject& associated, State* stage, string file):
    Component(associated)
{
    DEBUG_CONSTRUCTOR("inicio");
    sp = new Sprite(associated, file, true, ROBO_SHEET_FRAME_TIME, ROBO_SHEET_FRAMES);
    sp->SetAnimationLines(4);
    associated.AddComponent(sp);
    associated.box.w = sp->GetWidth();
    associated.box.h = sp->GetHeight();

    //ctor
    PlayerUnity& playerUnity = (dynamic_cast<PlayerUnity&>(associated.GetComponent(PLAYER_UNITY)));
    buttons.push_back((dynamic_cast<PlayerUnityMenu&>(playerUnity.GetMenu()->GetComponent(PLAYER_UNITY_MENU))).AddButton(BOTAO4, this, EjectPilot));
    DEBUG_CONSTRUCTOR("indice do botao: " << buttons.back());
    DEBUG_CONSTRUCTOR("fim");
}

Robo::~Robo()
{
    //dtor
}

bool Robo::Is(ComponentType type) const{
    return (type == ROBO);
}

void Robo::Update(float dt){
}

void Robo::EarlyUpdate(float dt){
}

void Robo::LateUpdate(float dt){
}

void Robo::Render(){
}

void Robo::EjectPilot(void* entry){
    DEBUG_PRINT("HAHA!!");
    if(pilotos.size() > 0){
        GameObject* desembarcado = pilotos[0];
        desembarcado->box.x = associated.box.x + associated.box.w;
        desembarcado->box.y = associated.box.y;
        pilotos.erase(pilotos.begin());
        desembarcado->showOnScreen = true;
    }
}

void Robo::BoardPilot(GameObject* piloto){
    pilotos.push_back(piloto);
}

