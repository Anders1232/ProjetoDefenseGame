#include "PlayerUnityPath.h"
#include "GameComponentType.h"

#include "Error.h"
PlayerUnityPath::PlayerUnityPath(GameObject& associated, TileMap<TileInfo>* tileMap, Vec2& destination):
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

PlayerUnityPath::~PlayerUnityPath()
{
    //dtor
}

void PlayerUnityPath::CreatePath(){
    Vec2 lastMarkerPosition;
    if(movingPath.size() > 0){
        associated.showOnScreen = true;
        lastMarkerPosition = *movingPath.back();
    }else{
        lastMarkerPosition = Vec2(associated.parent->box.x, associated.parent->box.y) ;
    }
    Vec2 mousePosition = InputManager::GetInstance().GetMousePos();
    Vec2 mouseOnGrid = tileMap->PixelToMap(mousePosition);
    if(tileMap->At(mouseOnGrid.x, mouseOnGrid.y).IsPassable() &&
       tileMap->At(mouseOnGrid.x, mouseOnGrid.y).IsFree() ){
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
}

void PlayerUnityPath::AddMarker(Vec2 position){
    Vec2* v = new Vec2();
    *v = tileMap->AdjustToMap(position);
    movingPath.push_back(v);
    GameObject* pathMarker = new GameObject("PathMarker", associated.GetContext());
    /*
        O Path não deve ser colocado como filho do PlayerUnity.
        Caso contrário, o path (e seus filhos) vão se mover conforme PlayerUnity se movimenta.
    */
    //pathMarker->SetParent(associated);
    pathMarker->SetPosition(movingPath.back()->x, movingPath.back()->y);
    pathMarker->AddComponent(new PathMarker(*pathMarker, MARKER_SPRITE));
    associated.CreateNewObject(pathMarker);
    pathMarkers.push_back(pathMarker);
}

bool PlayerUnityPath::HasPoints(){
    return (movingPath.size() > 0);
}

Vec2 PlayerUnityPath::GetNext(){
    Vec2 v = *(movingPath.front());
    return v;
}

bool PlayerUnityPath::Is(unsigned int type) const{
    return (type == GameComponentType::PLAYER_UNITY_PATH);
}

void PlayerUnityPath::Update(float dt){
    DEBUG_UPDATE("inicio");
    OnClick();
    if(!parentSelected && movingPath.size() > 0){
        if(associated.parent->box.x == pathMarkers.front()->box.x &&
           associated.parent->box.y == pathMarkers.front()->box.y){
               delete(movingPath.front());
               movingPath.erase(movingPath.begin());
               associated.RemoveComponent(SPRITE);
               pathMarkers.erase(pathMarkers.begin());

               Vec2 pos = GetNext();
               Vec2 onGrid = tileMap->PixelToMap(pos);
               if(tileMap->At(onGrid.x, onGrid.y).IsPassable() &&
                  tileMap->At(onGrid.x, onGrid.y).IsFree() ){
                    tileMap->At(onGrid.x, onGrid.y).PutCharacter(*(associated.parent));
                    destination = pos;
                    DEBUG_PRINT("Novo destination: " << onGrid.x << "," << onGrid.y);
                }else{
                    //tem alguma coisa no lugar que era pra ir
                }

        }else{

        }
    }else{
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

void PlayerUnityPath::ButtonObserver(Component* btn){
    if(movingPath.size() > 0){
        destination = GetNext();
    }
}

#include "Error_footer.h"
