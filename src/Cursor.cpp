#include "Cursor.h"

Cursor::Cursor(GameObject& associated, string spriteFile):
    Component(associated)
{
    associated.AddComponent(new Sprite(associated, spriteFile, true));
    //ctor
}

Cursor::~Cursor()
{
    //dtor
}

void Cursor::EarlyUpdate(float dt){
    associated.box.x = InputManager::GetInstance().GetMouseX();
    associated.box.y = InputManager::GetInstance().GetMouseY();
}

void Cursor::Update(float dt){
}

void Cursor::LateUpdate(float dt){
}

void Cursor::Render(){
}

bool Cursor::Is(ComponentType type) const{
    return type == CURSOR;
}
