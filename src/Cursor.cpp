#include "Cursor.h"
#include "GameObject.h"
#include "InputManager.h"
#include "Sprite.h"

#include "Error.h"

using std::string;

Cursor::Cursor(GameObject& associated, string spriteFile):
    Component(associated)
{
    DEBUG_CONSTRUCTOR("inicio");
    associated.AddComponent(new Sprite(associated, spriteFile, true));
    //ctor
    DEBUG_CONSTRUCTOR("fim");
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

bool Cursor::Is(unsigned int type) const{
    return type == GameComponentType::CURSOR;
}
