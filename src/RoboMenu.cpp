#include "RoboMenu.h"

RoboMenu::RoboMenu(GameObject& associated):
    Component(associated)
{
    associated.box.x = associated.parent->box.x + associated.parent->box.w;
    associated.box.y = associated.parent->box.y + associated.parent->box.h;

    //for(int i = 0; i < 4; i++){
        buttons.push_back(new Sprite(associated, BOTAO4, true) );
        associated.AddComponent( buttons.back() );
    //}
}

RoboMenu::~RoboMenu()
{
    //dtor
}

void RoboMenu::EarlyUpdate(float dt){
}

void RoboMenu::Update(float dt){
    DEBUG_UPDATE("RoboMenu", "inicio");
    DEBUG_UPDATE("RoboMenu", "fim");
}

void RoboMenu::LateUpdate(float dt){
}

void RoboMenu::Render(){
}

bool RoboMenu::Is(ComponentType type) const{
    return (type == ROBOMENU);
}
