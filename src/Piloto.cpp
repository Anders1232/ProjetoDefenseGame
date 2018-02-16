#include "Piloto.h"
#include "GameComponentType.h"

using std::string;
using std::vector;

#define PILOTO_SHEET_LINES        4
#define PILOTO_SHEET_FRAMES       4
#define PILOTO_SHEET_FRAME_TIME   4.0*1.0/24.0


Piloto::Piloto(GameObject& associated, string file, Vec2 position, TileMap<TileInfo>* tileMap):
    Component(associated)
{
    DEBUG_CONSTRUCTOR("inicio");
    PlayerUnity& playerUnity = *(new PlayerUnity(associated, position, tileMap));
    associated.AddComponent(&playerUnity);

    sp = new Sprite(associated, file, true, PILOTO_SHEET_FRAME_TIME, PILOTO_SHEET_FRAMES);
    sp->SetAnimationLines(4);
    associated.AddComponent(sp);
    associated.box.w = sp->GetWidth();
    associated.box.h = sp->GetHeight();

    //buttons.push_back((dynamic_cast<PlayerUnityMenu&>(playerUnity.GetMenu()->GetComponent(PLAYER_UNITY_MENU))).AddButton(BOTAO5, this, BoardPilot));
    //DEBUG_CONSTRUCTOR("indice do botao: " << buttons.back());
    DEBUG_CONSTRUCTOR("fim");
}

Piloto::~Piloto()
{
    //dtor
}

bool Piloto::Is(unsigned int comp) const{
    return (comp == GameComponentType::PILOTO);
}

void Piloto::EarlyUpdate(float dt){
}

void Piloto::Update(float dt){
    OnClick();

}

void Piloto::LateUpdate(float dt){
}

void Piloto::Render() const{
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
