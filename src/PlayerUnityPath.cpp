#include "PlayerUnityPath.h"

#include "Error.h"
RoboPath::RoboPath(GameObject& associated, Vec2& destination):
    Component(associated),
    parentSelected(false),
    destination(destination)
{
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
        DEBUG_PRINT("Robo", "adicionado ponto(" << auxX + associated.parent->box.w << ", " << auxY << ")");
        movingPath.push_back(new Vec2(InputManager::GetInstance().GetMousePos().x, auxY) );

        pathMarkers.push_back(new Sprite(associated, PATH_MARKER, true));
        pathMarkers.back()->SetPosition(movingPath.back()->x, movingPath.back()->y);
        associated.AddComponent(pathMarkers.back());
    }
    if(InputManager::GetInstance().GetMousePos().y > auxY + associated.parent->box.h ||
       InputManager::GetInstance().GetMousePos().y < auxY - associated.parent->box.h ){
        DEBUG_PRINT("Robo", "adicionado ponto(" << auxX << ", " << InputManager::GetInstance().GetMousePos().y << ")");
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
    DEBUG_PRINT("RoboPath", "pathSize antes: " << movingPath.size());

    Vec2 v = *(movingPath.front());
    DEBUG_PRINT("RoboPath", "pathSize depois: " << movingPath.size());
    return v;
}

bool RoboPath::Is(ComponentType type) const{
    return (type == ROBOPATH);
}

void RoboPath::Update(float dt){
    DEBUG_UPDATE("RoboPath", "inicio");
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
    DEBUG_UPDATE("RoboPath", "fim");
}

void RoboPath::OnClick(){
    if(InputManager::GetInstance().GetMousePos().IsInRect(associated.parent->box) &&
       !parentSelected &&
       InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON)){
           DEBUG_PRINT("RoboPath", "selecionado");
           parentSelected = true;
    }
    if(parentSelected){
        CreatePath();
    }
    if(parentSelected &&
       InputManager::GetInstance().MouseRelease(LEFT_MOUSE_BUTTON)){
        parentSelected = false;
        DEBUG_PRINT("RoboPath", "solto");

        //TODO: Cria botão GO!
        //TODO: Se o botão for clicado, confirma a ação. Se clicar fora do botão, elimina botão e caminho.


        destination = GetNext();
    }
}

#include "Error_footer.h"
