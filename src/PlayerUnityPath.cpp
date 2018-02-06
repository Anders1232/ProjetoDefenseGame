#include "PlayerUnityPath.h"
#include "GameComponentType.h"

#include "Error.h"
RoboPath::RoboPath(GameObject& associated, TileMap<TileInfo>* tileMap, Vec2& destination):
    Component(associated),
    parentSelected(false),
    destination(destination),
    listenerId(0),
    pathFinished(this),
    tileMap(tileMap)
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
    Vec2 lastMarkerPosition;
    if(movingPath.size() > 0){
        associated.showOnScreen = true;
        lastMarkerPosition = *movingPath.back();
    }else{
        lastMarkerPosition = Vec2(associated.parent->box.x, associated.parent->box.y) ;
    }
    Vec2 mousePosition = InputManager::GetInstance().GetMousePos();

    if(mousePosition.x > lastMarkerPosition.x + tileMap->GetTileSize().x){
        AddMarker(Vec2(mousePosition.x, lastMarkerPosition.y));
    }else if(mousePosition.x < lastMarkerPosition.x){
        AddMarker(Vec2(lastMarkerPosition.x - tileMap->GetTileSize().x, lastMarkerPosition.y));
    }

    if(mousePosition.y > lastMarkerPosition.y + tileMap->GetTileSize().y){
        AddMarker(Vec2(lastMarkerPosition.x, mousePosition.y));
    }else if(mousePosition.y < lastMarkerPosition.y){
        AddMarker(Vec2(lastMarkerPosition.x, lastMarkerPosition.y - tileMap->GetTileSize().y));
    }
}

void RoboPath::AddMarker(Vec2 position){
    Vec2* v = new Vec2();
    *v = tileMap->AdjustToMap(position);
    DEBUG_PRINT("position Added: " << v->x << "," << v->y );
    movingPath.push_back(v);

    pathMarkers.push_back(new Sprite(associated, PATH_MARKER, true));
    pathMarkers.back()->SetPosition(movingPath.back()->x, movingPath.back()->y);
    associated.AddComponent(pathMarkers.back());
}

bool RoboPath::HasPoints(){
    return (movingPath.size() > 0);
}

Vec2 RoboPath::GetNext(){
    Vec2 v = *(movingPath.front());
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
