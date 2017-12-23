#include "PlayerUnityMenu.h"
#define CLASS "PlayerUnityMenu"

PlayerUnityMenu::PlayerUnityMenu(GameObject& associated, State* stage):
    Component(associated),
    stage(stage)
{
    DEBUG_CONSTRUCTOR("inicio");
    Reposition();
    associated.showOnScreen = false;
    AddButton(BOTAO1, this);
    DEBUG_CONSTRUCTOR("fim");
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
    }
    DEBUG_UPDATE("fim");
}

void PlayerUnityMenu::LateUpdate(float dt){
}

void PlayerUnityMenu::OnClick(){
    DEBUG_UPDATE("inicio");
    DEBUG_UPDATE("fim");
}

void PlayerUnityMenu::Render() const{
}

bool PlayerUnityMenu::Is(ComponentType type) const{
    return (type == PLAYER_UNITY_MENU);
}

void PlayerUnityMenu::Toogle(){
    DEBUG_UPDATE("inicio");
    if(associated.parent->Released()){
        for(int i = 0; i < buttons.size(); i++){
            buttons[i]->SetActive(true);
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

int PlayerUnityMenu::AddButton(string buttonSpritePath, Component* observer){
    DEBUG_PRINT("inicio");
    //  GameObject recipiente
    GameObject* buttonObject = new GameObject();
    buttonObject->parent = &associated;
    buttonObject->SetActive(false);

    buttonObject->AddComponent(new RectTransform(*buttonObject, &associated));
    buttonObject->AddComponent(new Sprite(*buttonObject, buttonSpritePath, true));

    //  componente Button
    Button* buttonComponent = new Button(*buttonObject);
    buttonComponent->AddObserver(observer);

    //  equipando componente
    buttonObject->AddComponent(buttonComponent);

    //  colocando objeto no vetor do mainGameLoop
    stage->AddObject(buttonObject);

    //  colocando no vetor do menu
    buttons.push_back(buttonObject);

    DEBUG_PRINT("fim");
    return buttons.size() - 1;
}

void PlayerUnityMenu::ButtonObserver(Component* btn){
    for(int i = 0; i < buttons.size(); i++){
            buttons[i]->SetActive(false);
    }
}
