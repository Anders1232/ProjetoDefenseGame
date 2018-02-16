#include "Robo.h"

#include "GameObject.h"
#include "Sprite.h"

#include "PlayerUnity.h"
#include "PlayerUnityMenu.h"
#include "CharacterStatus.h"

using std::vector;
using std::string;

#define ROBO_SHEET_LINES        4
#define ROBO_SHEET_FRAMES       4
#define ROBO_SHEET_FRAME_TIME   4.0*1.0/24.0

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
    PlayerUnityMenu& playerUnityMenu = (dynamic_cast<PlayerUnityMenu&>(unityMenu->GetComponent(GameComponentType::PLAYER_UNITY_MENU)));
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
    if(InputManager::GetInstance().KeyPress(SDLK_0)){
        Attack();
    }
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

void Robo::Attack(){
    //Posi��o no grid
    //Component& charStatus = associated.GetComponent(CHARACTER_STATUS);
    try{
        CharacterStatus& charStatus = dynamic_cast<CharacterStatus&>(associated.GetComponent(CHARACTER_STATUS));
        vector<Vec2> range = charStatus.CellsInRange();
        DEBUG_PRINT("Celulas no alcance:");
        for(int i = 0; i < range.size(); i++){
            DEBUG_PRINT("c" << i << ": " << range[i].x << "," << range[i].y);
        }
    }catch(std::bad_cast& e){
        DEBUG_PRINT("Deu merda no dynamic_cast: " << e.what() );
    }
}
