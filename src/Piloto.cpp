#include "Piloto.h"

Piloto::Piloto(GameObject& associated):
    Component(associated)
{
    DEBUG_CONSTRUCTOR("inicio");
    //ctor
    PlayerUnity& playerUnity = (dynamic_cast<PlayerUnity&>(associated.GetComponent(PLAYER_UNITY)));
    buttons.push_back((dynamic_cast<PlayerUnityMenu&>(playerUnity.GetMenu()->GetComponent(PLAYER_UNITY_MENU))).AddButton(BOTAO5, this, BoardPilot));
    DEBUG_CONSTRUCTOR("indice do botao: " << buttons.back());
    DEBUG_CONSTRUCTOR("fim");
}

Piloto::~Piloto()
{
    //dtor
}

bool Piloto::Is(ComponentType comp) const{
    return (comp == PILOTO);
}

void Piloto::EarlyUpdate(float dt){
}

void Piloto::Update(float dt){
    OnClick();

}

void Piloto::LateUpdate(float dt){
}

void Piloto::Render(){
}

void Piloto::OnClick(){
    if(InputManager::GetInstance().MouseRelease(LEFT_MOUSE_BUTTON)){
        if(InputManager::GetInstance().GetMousePos().IsInRect(associated.box)){
       }else{
       }
    }
}

Vec2& Piloto::Destination(){
}

void Piloto::SetPosition(int x, int y){
    associated.box.x = x;
    associated.box.y = y;
}

void Piloto::ShowOnScreen(){
    associated.showOnScreen = true;
}

void Piloto::BoardPilot(void*){

}
