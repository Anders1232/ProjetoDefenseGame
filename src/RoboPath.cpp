#include "RoboPath.h"

#include "Error.h"
RoboPath::RoboPath(GameObject& associated, Vec2 first):
    Component(associated)
{
    movingPath.push_back(new Vec2(first.x, first.y));
    //ctor
}

RoboPath::~RoboPath()
{
    //dtor
}

void RoboPath::CreatePath(){
        if(InputManager::GetInstance().GetMousePos().x > movingPath.back()->x + associated.parent->box.w ||
           InputManager::GetInstance().GetMousePos().x < movingPath.back()->x - associated.parent->box.w){
            DEBUG_PRINT("Robo", "adicionado ponto(" << movingPath.back()->x + associated.parent->box.w << ", " << movingPath.back()->y << ")");
            movingPath.push_back(new Vec2(InputManager::GetInstance().GetMousePos().x, movingPath.back()->y) );
            pathMarkers.push_back(new Sprite(associated, PATH_MARKER, true));
            pathMarkers.back()->SetPosition(movingPath.back()->x, movingPath.back()->y);
            associated.AddComponent(pathMarkers.back());
        }
        if(InputManager::GetInstance().GetMousePos().y > movingPath.back()->y + associated.parent->box.h ||
           InputManager::GetInstance().GetMousePos().y < movingPath.back()->y - associated.parent->box.h ){
            DEBUG_PRINT("Robo", "adicionado ponto(" << movingPath.back()->x << ", " << InputManager::GetInstance().GetMousePos().y << ")");
            movingPath.push_back(new Vec2(movingPath.back()->x, InputManager::GetInstance().GetMousePos().y) );
            pathMarkers.push_back(new Sprite(associated, PATH_MARKER, true));
            pathMarkers.back()->SetPosition(movingPath.back()->x, movingPath.back()->y);
            associated.AddComponent(pathMarkers.back());
        }
}

bool RoboPath::HasPoints(){
    return (movingPath.size() > 0);
}

Vec2 RoboPath::GetNext(){
    DEBUG_PRINT("RoboPath", "pathSize antes: " << movingPath.size());
    Vec2 v = *(movingPath.front());
    delete(movingPath.front());
    movingPath.erase(movingPath.begin());
    DEBUG_PRINT("RoboPath", "pathSize depois: " << movingPath.size());
    return v;
}

bool RoboPath::Is(ComponentType type) const{
    return (type == ROBOPATH);
}

void RoboPath::Update(float dt){
    DEBUG_UPDATE("RoboPath", "inicio");
    if(pathMarkers.size() > 0){
        if(associated.parent->box.x == pathMarkers.front()->GetScreenX() &&
           associated.parent->box.y == pathMarkers.front()->GetScreenY()){
                associated.RemoveComponent(SPRITE);
                //delete(pathMarkers.front());
                pathMarkers.erase(pathMarkers.begin());
        }
    }
    DEBUG_UPDATE("RoboPath", "fim");
}
#include "Error_footer.h"
