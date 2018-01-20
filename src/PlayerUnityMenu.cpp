#include "PlayerUnityMenu.h"

PlayerUnityMenu::PlayerUnityMenu(GameObject& associated, State* stage):
    Component(associated),
    stage(stage),
    active(false)
{
    DEBUG_CONSTRUCTOR("inicio");
    Reposition();
    associated.showOnScreen = false;
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
    DEBUG_PRINT("Passou no meu Is");
    return (type == PLAYER_UNITY_MENU);
}

void PlayerUnityMenu::Toogle(){
    DEBUG_UPDATE("inicio");
    if(associated.parent->Released()){
        active = !active;
        for(unsigned int i = 0; i < buttons.size(); i++){
            buttons[i]->SetActive(active);
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
    GameObject* buttonObject = new GameObject("Button");

    //  TODO: organizar apresentação do menu
    buttonObject->SetParent(associated, 100, 100 + buttons.size()*30);//distância fora da box do playerUnity; um botao abaixo do outro
    //
    buttonObject->SetActive(false);

    buttonObject->AddComponent(new Sprite(*buttonObject, buttonSpritePath, true));

    //  componente Button
    Button* buttonComponent = new Button(*buttonObject);
    buttonComponent->AddObserver(this);
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

GameObject* PlayerUnityMenu::GetButton(unsigned int i){
    if(buttons.size() && i < buttons.size()){
        return buttons[i];
    }else{
        return nullptr;
    }
}

int PlayerUnityMenu::GetButtons(){
    return buttons.size();
}

void PlayerUnityMenu::ButtonObserver(Component* btn){
    for(unsigned int i = 0; i < buttons.size(); i++){
            buttons[i]->SetActive(false);
    }
}


void PlayerUnityMenu::OnPathFinished(RoboPath* eventSource, int& unused, void* context){
    PlayerUnityMenu* pum = static_cast<PlayerUnityMenu*>(context);
    for(int i = 0; i < pum->GetButtons(); i++){
        (pum->GetButton(i))->SetActive(true);
    }
}


void PlayerUnityMenu::SubscribeToPath(RoboPath& roboPath){
    roboPath.pathFinished.Subscribe(OnPathFinished, this);
}

