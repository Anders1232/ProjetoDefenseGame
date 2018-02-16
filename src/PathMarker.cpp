#include "PathMarker.h"
#include "GameObject.h"
#include "Sprite.h"


using std::string;

PathMarker::PathMarker(GameObject& associated, string spritePath):
    Component(associated)
{
    associated.AddComponent(new Sprite(associated, spritePath, true));
}

PathMarker::~PathMarker()
{
    //dtor
}

void PathMarker::EarlyUpdate(float dt){}
void PathMarker::Update(float dt){}
void PathMarker::LateUpdate(float dt){}
void PathMarker::Render(){}
bool PathMarker::Is(unsigned int type)const{
    return type == PATH_MARKER;
}
