#include "Piloto.h"

Piloto::Piloto(GameObject& associated):
    Component(associated)
{
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
