#include "PlayerUnityPath.h"
#include "GameComponentType.h"

#include "Error.h"
RoboPath::RoboPath(GameObject& associated, Vec2& destination):
    Component(associated),
    parentSelected(false),
    destination(destination),
    listenerId(0),
    pathFinished(this)
{
    listeners = StartMapping();
    associated.showOnScreen = false;
    //ctor
}

RoboPath::~RoboPath()
{
    //dtor
}

void RoboPath::CreatePath(){
    int auxX, auxY;
    if(movingPath.size() > 0){
        associated.showOnScreen = true;
        auxX = movingPath.back()->x;
        auxY = movingPath.back()->y;
    }else{
        auxX = associated.parent->box.x;
        auxY = associated.parent->box.y;
    }
    if(InputManager::GetInstance().GetMousePos().x > auxX + associated.parent->box.w ||
       InputManager::GetInstance().GetMousePos().x < auxX - associated.parent->box.w){
        DEBUG_PRINT("adicionado ponto(" << auxX + associated.parent->box.w << ", " << auxY << ")");
        movingPath.push_back(new Vec2(InputManager::GetInstance().GetMousePos().x, auxY) );

        pathMarkers.push_back(new Sprite(associated, PATH_MARKER, true));
        pathMarkers.back()->SetPosition(movingPath.back()->x, movingPath.back()->y);
        associated.AddComponent(pathMarkers.back());
    }
    if(InputManager::GetInstance().GetMousePos().y > auxY + associated.parent->box.h ||
       InputManager::GetInstance().GetMousePos().y < auxY - associated.parent->box.h ){
        DEBUG_PRINT("adicionado ponto(" << auxX << ", " << InputManager::GetInstance().GetMousePos().y << ")");
        movingPath.push_back(new Vec2(auxX, InputManager::GetInstance().GetMousePos().y) );

        pathMarkers.push_back(new Sprite(associated, PATH_MARKER, true));
        pathMarkers.back()->SetPosition(movingPath.back()->x, movingPath.back()->y);
        associated.AddComponent(pathMarkers.back());
    }
}

bool RoboPath::HasPoints(){
    return (movingPath.size() > 0);
}

Vec2 RoboPath::GetNext(){
    DEBUG_PRINT("pathSize antes: " << movingPath.size());
    Vec2 v = *(movingPath.front());
    DEBUG_PRINT("pathSize depois: " << movingPath.size());
    return v;
}

bool RoboPath::Is(unsigned int type) const{
    return (type == GameComponentType::ROBOPATH);
}

void RoboPath::Update(float dt){
    DEBUG_UPDATE("inicio");
    OnClick();
    if(!parentSelected && movingPath.size() > 0){
        if(associated.parent->box.x == pathMarkers.front()->GetScreenX() &&
           associated.parent->box.y == pathMarkers.front()->GetScreenY()){
               delete(movingPath.front());
               movingPath.erase(movingPath.begin());

               associated.RemoveComponent(SPRITE);
               pathMarkers.erase(pathMarkers.begin());
               destination = GetNext();
        }else{

        }
    }else{
    }
    DEBUG_UPDATE("fim");
}

void RoboPath::OnClick(){
    if(InputManager::GetInstance().GetMousePos().IsInRect(associated.parent->box) &&
       !parentSelected &&
       InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON)){
           DEBUG_PRINT("selecionado");
           parentSelected = true;
    }
    if(parentSelected){
        CreatePath();
    }
    if(parentSelected &&
       InputManager::GetInstance().MouseRelease(LEFT_MOUSE_BUTTON)){
        parentSelected = false;
        DEBUG_PRINT("solto");
        int i = 0;
        pathFinished.FireEvent(i);
    }
}

void RoboPath::ButtonObserver(Component* btn){
    if(movingPath.size() > 0){
        destination = GetNext();
    }
}

#include "Error_footer.h"
