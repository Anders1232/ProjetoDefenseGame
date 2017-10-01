#include "../include/Robo.h"

//#define DEBUG
#ifdef DEBUG
    #define DEBUG_PRINT(x) do{ cout << x <<  endl; }while(0);
#else
    #define DEBUG_PRINT(x)
#endif // DEBUG

Robo::Robo(GameObject& associated, float x, float y, string file):
    associated(associated),
    sp(new Sprite(associated, file, ROBO_SHEET_FRAME_TIME, ROBO_SHEET_FRAMES)),//, ROBO_SHEET_LINES)),
    selected(false)
{
    DEBUG_PRINT("Robo::Robo()-inicio");

    associated.AddComponent(sp);
    associated.box.h = sp->GetHeight();
    associated.box.w = sp->GetWidth();
    associated.box.x = x;
    associated.box.y = y;


    //Barra de vida
    Bar* barraVida =  new Bar(200, BARRA_VIDA_MOLDURA, BARRA_VIDA, associated);
    barraVida->SetPosition(0,0);
    associated.AddComponent(barraVida);

    //barra de cooldown
    Bar* coolDownBar = new Bar(10, BARRA_COOLDDOWN_MOLDURA, BARRA_COOLDOWN, associated);
    coolDownBar->SetY(10);
    coolDownBar->SetRefilAuto(10);
    coolDownBar->SetPoints(0);
    coolDownBar->SetPosition(0,10);
    DEBUG_PRINT(coolDownBar.GetY() << "x" << coolDownBar.GetY());
    associated.AddComponent(coolDownBar);

//    Walkable* walkable = new Walkable(associated);
//    walkable->SetControlable(true);
//    associated.AddComponent(walkable);

    DEBUG_PRINT("Robo::Robo()-fim");
}

Robo::~Robo(){
}

void Robo::Update(float dt){
    DEBUG_PRINT("COMP - Robo::Update()-inicio");
    //sp->SetPosition(associated.box.x, associated.box.y);
    DEBUG_PRINT("COMP - Robo::Update()-fim");
}

void Robo::Render(){
//    DEBUG_PRINT("Robo::Render()-inicio");
//    sp.Render();
//    for(unsigned int i = 0; i < components.size(); i++){
//        components[i]->Render();
//    }
//    DEBUG_PRINT("Robo::Render()-fim");
}

bool Robo::Is(ComponentType type)const{
    return type == ROBO;
}

void Robo::EarlyUpdate(float dt){}
void Robo::LateUpdate(float dt){}

#ifdef DEBUG
    #undef DEBUG
#endif
