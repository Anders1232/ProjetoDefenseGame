#include "Robo.h"

#include "GameObject.h"
#include "Sprite.h"

#include "PlayerUnity.h"
#include "PlayerUnityMenu.h"
#include "CharacterStatus.h"
#include "Button.h"

using std::vector;
using std::string;

#define ROBO_SHEET_LINES        4
#define ROBO_SHEET_FRAMES       4
#define ROBO_SHEET_FRAME_TIME   4.0*1.0/24.0

Robo::Robo(GameObject& associated, string file, Vec2 position, TileMap<TileInfo>* tileMap):
    PlayerUnity(associated, position, tileMap)
{
    DEBUG_CONSTRUCTOR("inicio");
    DEBUG_CONSTRUCTOR("position: " << position.x << ", " << position.y);
    attackSound.Open("resources/audio/TIRO_04.wav");
    sp = new Sprite(associated, file, true, ROBO_SHEET_FRAME_TIME, ROBO_SHEET_FRAMES);
    sp->SetAnimationLines(4);
    associated.AddComponent(sp);
    associated.SetCenterPosition(tileMap->CellCenterToPixel(position));
    //associated.box.w = sp->GetWidth();
    //associated.box.h = sp->GetHeight();

    GameObject* unityMenu = associated.GetChildWithTag("UnityMenu");
    PlayerUnityMenu& playerUnityMenu = unityMenu->GetComponent<PlayerUnityMenu>();
    playerUnityMenu.AddButton(BOTAO4, "Ejetar", this);

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
    DEBUG_UPDATE("inicio");
    PlayerUnity::Update(dt);
    DEBUG_UPDATE("fim");
}

void Robo::EarlyUpdate(float dt){
    PlayerUnity::EarlyUpdate(dt);
}

void Robo::LateUpdate(float dt){
    PlayerUnity::LateUpdate(dt);
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
    DEBUG_PRINT("inicio");
    DEBUG_PRINT("button clicked: " << (dynamic_cast<Button&>(*btn)).name );
    PlayerUnity::ButtonObserver(btn);
    if((dynamic_cast<Button&>(*btn)).name == "Ejetar"){
        if(pilotos.size()){
            pilotos.back()->SetActive(true);
            pilotos.pop_back();
        }
    }
    DEBUG_PRINT("fim");
}

bool Robo::Attack(CharacterType other){
    //Posição no grid
    if(PlayerUnity::Attack(other)){
        attackSound.Play(1);
        return true;
    }else{
        return false;
    }
}
