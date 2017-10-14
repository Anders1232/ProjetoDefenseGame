#include "RoboPath.h"

#include "Error.h"
RoboPath::RoboPath(GameObject& associated, Vec2 first):
    Component(associated),
    associated(associated)
{
    movingPath.push_back(new Vec2(first.x, first.y));
    //ctor
}

RoboPath::~RoboPath()
{
    //dtor
}

void RoboPath::AddPoint(){
    if(InputManager::GetInstance().GetMousePos().x > movingPath.back()->x + associated.parent->box.w ||
           InputManager::GetInstance().GetMousePos().x < movingPath.back()->x - associated.parent->box.w){
            DEBUG_PRINT("Robo", "adicionado ponto(" << movingPath.back()->x + associated.parent->box.w << ", " << movingPath.back()->y << ")");
            movingPath.push_back(new Vec2(InputManager::GetInstance().GetMousePos().x, movingPath.back()->y) );
        }
        if(InputManager::GetInstance().GetMousePos().y > movingPath.back()->y + associated.parent->box.h ||
           InputManager::GetInstance().GetMousePos().y < movingPath.back()->y - associated.parent->box.h ){
            DEBUG_PRINT("Robo", "adicionado ponto(" << movingPath.back()->x << ", " << movingPath.back()->y + associated.parent->box.h << ")");
            movingPath.push_back(new Vec2(movingPath.back()->x, InputManager::GetInstance().GetMousePos().y) );
        }
}

bool RoboPath::HasPoints(){
    return (movingPath.size() > 0);
}

Vec2 RoboPath::GetNext(){
    Vec2 v = *(movingPath.front());
    delete(movingPath.front());
    movingPath.erase(movingPath.begin());
    return v;
}

bool RoboPath::Is(ComponentType type) const{
    return (type == ROBOPATH);
}
#include "Error_footer.h"
