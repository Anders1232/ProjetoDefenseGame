#include "PlayerUnityPath.h"

#include "Sprite.h"
#include "PlayerUnity.h"
#include "PathMarker.h"
#include "resources_path.h"

#include "Error.h"

using std::vector;
using std::multimap;

PlayerUnityPath::PlayerUnityPath(GameObject& associated, TileMap<TileInfo>* tileMap, Vec2* destination):
    Component(associated),
    pathFinished(this),
    parentSelected(false),
    tileMap(tileMap),
    destination(&destination)
{
    associated.showOnScreen = false;
    //ctor
}

PlayerUnityPath::~PlayerUnityPath()
{
    //dtor
}

void PlayerUnityPath::CreatePath(){
    Vec2 lastMarkerPosition;
    if(pathMarkers.size() > 0){
        associated.showOnScreen = true;
        lastMarkerPosition = tileMap->PixelToMap( (*pathMarkers.back()).box.Center());
    }else{
        lastMarkerPosition = tileMap->PixelToMap(associated.box.Center()) ;
    }
    Vec2 mouseOnGrid = tileMap->PixelToMap(InputManager::GetInstance().GetMousePos());
    if(tileMap->At(mouseOnGrid.x, mouseOnGrid.y).IsPassable() &&
       tileMap->At(mouseOnGrid.x, mouseOnGrid.y).IsFree(associated) ){

        if(mouseOnGrid.x > lastMarkerPosition.x){
            AddMarker(Vec2(mouseOnGrid.x, lastMarkerPosition.y));
        }else if(mouseOnGrid.x < lastMarkerPosition.x){
            AddMarker(Vec2(mouseOnGrid.x, lastMarkerPosition.y));
        }
        if(mouseOnGrid.y > lastMarkerPosition.y){
            AddMarker(Vec2(lastMarkerPosition.x, mouseOnGrid.y));
        }else if(mouseOnGrid.y < lastMarkerPosition.y){
            AddMarker(Vec2(lastMarkerPosition.x, mouseOnGrid.y));
        }
    }
}

void PlayerUnityPath::AddMarker(Vec2 position){
    GameObject* pathMarker = new GameObject("PathMarker", associated.GetContext());
    /*
        O Path não deve ser colocado como filho do PlayerUnity.
        Caso contrário, o path (e seus filhos) vão se mover conforme PlayerUnity se movimenta.
    */
    DEBUG_PRINT("Position: " << position.x << ", " << position.y);
    DEBUG_PRINT("cellCenter: " << tileMap->CellCenterToPixel(position).x << ", " << tileMap->CellCenterToPixel(position).y);
    pathMarker->AddComponent(new PathMarker(*pathMarker, MARKER_SPRITE));
    pathMarker->SetCenterPosition(tileMap->CellCenterToPixel(position));
    associated.CreateNewObject(pathMarker);
    pathMarkers.push_back(pathMarker);
}

bool PlayerUnityPath::HasPoints(){
    return (pathMarkers.size() > 0);
}

Vec2 PlayerUnityPath::GetNext(){
    if(pathMarkers.size() > 0){
        Vec2 v( tileMap->PixelToMap( (*pathMarkers.front()).box.Center()) );
        return v;
    }else{
        return Vec2(-1,-1);
    }
}

bool PlayerUnityPath::Is(unsigned int type) const{
    return (type == GameComponentType::PLAYER_UNITY_PATH);
}

void PlayerUnityPath::Update(float dt){
    DEBUG_UPDATE("inicio");

    OnClick();
    if(!parentSelected && pathMarkers.size() > 0){
        if(associated.parent->box.Center().x == pathMarkers.front()->box.Center().x &&
           associated.parent->box.Center().y == pathMarkers.front()->box.Center().y){
            //delete(pathMarkers.front());
            pathMarkers.front()->RequestDelete();
            pathMarkers.erase(pathMarkers.begin());
        }
    }
    DEBUG_UPDATE("fim");
}

void PlayerUnityPath::OnClick(){
    DEBUG_UPDATE("inicio");
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
    DEBUG_UPDATE("fim");
}
#include "Error_footer.h"
