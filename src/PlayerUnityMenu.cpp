#include "PlayerUnityMenu.h"

RoboMenu::RoboMenu(GameObject& associated):
    Component(associated)
{
    associated.box.x = associated.parent->box.x + associated.parent->box.w;
    associated.box.y = associated.parent->box.y + associated.parent->box.h;
    associated.showOnScreen = false;

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
    Toogle();
    if(associated.showOnScreen){
        OnClick();
    }
    DEBUG_UPDATE("RoboMenu", "fim");
}

void RoboMenu::LateUpdate(float dt){
}

void RoboMenu::OnClick(){
    DEBUG_UPDATE("RoboMenu", "inicio");
    if(InputManager::GetInstance().MouseRelease(LEFT_MOUSE_BUTTON)){
        if(InputManager::GetInstance().GetMousePos().IsInRect(buttons.back()->GetScreenRect() )){
            DEBUG_PRINT("RoboMenu", "Botao pressionado/solto. Menu sera fechado");
        }
    }
    DEBUG_UPDATE("RoboMenu", "fim");
}

void RoboMenu::Render(){
}

bool RoboMenu::Is(ComponentType type) const{
    return (type == ROBOMENU);
}

void RoboMenu::Toogle(){
    DEBUG_UPDATE("RoboMenu", "inicio");
    SDL_Rect parentRect = {associated.parent->box.x, associated.parent->box.y,
                           associated.parent->box.w, associated.parent->box.h};
    if(InputManager::GetInstance().GetMousePos().IsInRect(parentRect)){
        if(InputManager::GetInstance().MouseRelease(LEFT_MOUSE_BUTTON)){
            associated.showOnScreen = !associated.showOnScreen;
            DEBUG_PRINT("RoboMenu", "clicado");
        }
    }
    DEBUG_UPDATE("RoboMenu", "fim");
}
