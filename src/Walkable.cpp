#include "Walkable.h"

#define DEBUG
#ifdef DEBUG
    #define DEBUG_PRINT(x) do{ cout << x <<  endl; }while(0);
#else
    #define DEBUG_PRINT(x)
#endif // DEBUG


Walkable::Walkable(GameObject& associated):
    associated(associated),
    controlable(false),
    hasToWalk(false)
{
    //ctor
}

void Walkable::Update(float dt){
    if(controlable){
        //Ao clicar, marca como selecionado e coloca a posição de origem no vetor
        if(InputManager::GetInstance().MousePress(SDL_BUTTON_LEFT) &&
           InputManager::GetInstance().IsMouseInside(associated.box)){

            selected = true;
            pathPoints.push_back(new Point(PixelToGrid(associated.box.x, associated.box.w),
                                           PixelToGrid(associated.box.y, associated.box.h)));
        }

        //Enquanto estiver com o mouse clicado, forma o caminho
        if(selected && InputManager::GetInstance().IsMouseDown(SDL_BUTTON_LEFT)){
            AddPath(InputManager::GetInstance().GetMouseX(), InputManager::GetInstance().GetMouseY());
        }

        //Quando soltar o botão do mouse, desmarca a seleção
        if(selected && InputManager::GetInstance().MouseRelease(SDL_BUTTON_LEFT)){
           if(!InputManager::GetInstance().IsMouseInside(associated.box)){
                hasToWalk = true;
           }
           selected = false;
        }

        while( hasToWalk ){
                cout << "Deveria andar" << endl;
                cout << "Pontos: " << endl;
                for(auto it = pathPoints.begin(); it != pathPoints.end(); it++){
                    cout << (*it)->x << "x" << (*it)->y << endl;
                }

                auto it = pathPoints.begin();
                if(associated.box.x < (*it)->x * associated.box.w) associated.box.x += 1;
                else if(associated.box.x > (*it)->x * associated.box.w) associated.box.x -= 1;
                else{
                    pathPoints.erase(pathPoints.begin());
                    if(pathPoints.empty()){
                        hasToWalk = false;
                        break;
                    }
                }
                if(associated.box.y < (*it)->y * associated.box.h) associated.box.y += 1;
                else if(associated.box.y > (*it)->y * associated.box.h) associated.box.y -= 1;
                else{
                    pathPoints.erase(pathPoints.begin());
                    if(pathPoints.empty()) hasToWalk = false;
                }
           }
    }
}

Walkable::~Walkable()
{
    //dtor
}

bool Walkable::Is(ComponentType type) const{
    return type == WALKABLE;
}

int Walkable::PixelToGrid(int x, int tileW){
    return x/tileW;
}

void Walkable::AddPath(int x, int y){
    if(pathPoints.back()->x !=
       PixelToGrid(x, associated.box.w) ){
    //se o ponto atual for diferente do ultimo ponto colocado (isso deve ser modificado para "se o ponto ainda não foi colocado)
        pathPoints.push_back(new Point(PixelToGrid(x, associated.box.w), pathPoints.back()->y ));
    }
    if(pathPoints.back()->y !=
       PixelToGrid(y, associated.box.h) ){
    //se o ponto atual for diferente do ultimo ponto colocado (isso deve ser modificado para "se o ponto ainda não foi colocado)
        pathPoints.push_back(new Point(pathPoints.back()->x, PixelToGrid(y, associated.box.h )));
    }
}

void Walkable::LateUpdate(float dt){}

void Walkable::EarlyUpdate(float dt){}

void Walkable::SetControlable(bool control){
    this->controlable = control;
}

#ifdef DEBUG
    #undef DEBUG
#endif
