#include "PlayerUnityMenu.h"
#define CLASS "PlayerUnityMenu"

PlayerUnityMenu::PlayerUnityMenu(GameObject& associated, State* stage):
    Component(associated),
    stage(stage)
{
    Reposition();
    associated.showOnScreen = false;
}

PlayerUnityMenu::~PlayerUnityMenu()
{
    //dtor
}

void PlayerUnityMenu::EarlyUpdate(float dt){
}

void PlayerUnityMenu::Update(float dt){
    DEBUG_UPDATE("inicio");
    Toogle();
    if(associated.showOnScreen){
        Reposition();
        OnClick();
    }
    DEBUG_UPDATE("fim");
}

void PlayerUnityMenu::LateUpdate(float dt){
}

void PlayerUnityMenu::OnClick(){
    DEBUG_UPDATE("inicio");
    if(InputManager::GetInstance().MouseRelease(LEFT_MOUSE_BUTTON)){

    }
    DEBUG_UPDATE("fim");
}

void PlayerUnityMenu::Render(){
}

bool PlayerUnityMenu::Is(ComponentType type) const{
    return (type == PLAYER_UNITY_MENU);
}

void PlayerUnityMenu::Toogle(){
    DEBUG_UPDATE("inicio");
    SDL_Rect parentRect = {associated.parent->box.x, associated.parent->box.y,
                           associated.parent->box.w, associated.parent->box.h};
    if(InputManager::GetInstance().GetMousePos().IsInRect(parentRect)){
        if(InputManager::GetInstance().MouseRelease(LEFT_MOUSE_BUTTON)){
            associated.showOnScreen = !associated.showOnScreen;
            for(int i = 0; i < buttons.size(); i++){
                buttons[i]->showOnScreen = associated.showOnScreen;

//                So pra lembrar oq tava fazendo
//
//                template<typename T>
//                void ToogleButtons(){
//                    (dynamic_cast<Button<T>&>(associated.GetComponent(BUTTON))).SetState(Button<T>::State::ENABED);
//              s  }
            }
            DEBUG_PRINT("clicado");
        }
    }
    DEBUG_UPDATE("fim");
}

void PlayerUnityMenu::Reposition(){
    associated.box.x = associated.parent->box.x + associated.parent->box.w;
    associated.box.y = associated.parent->box.y + associated.parent->box.h;
    associated.box.w = 100;
    associated.box.h = 100;
}
