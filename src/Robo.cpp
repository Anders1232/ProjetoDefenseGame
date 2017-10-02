#include "../include/Robo.h"

//#define DEBUG
#ifdef DEBUG
    #define DEBUG_PRINT(x) do{ cout << x <<  endl; }while(0);
#else
    #define DEBUG_PRINT(x)
#endif // DEBUG

Robo::Robo(GameObject& associated, float x, float y, string file):
    associated(associated),
    selected(false)
{
    DEBUG_PRINT("Robo::Robo()-inicio");
    /*
        Ao criar o Robo, ele que organiza como será o GameObject
    */
    associated.box.x = x;
    associated.box.y = y;

    /*
        Coloca a image do robo
    */
    Sprite* sp = new Sprite(associated, file, ROBO_SHEET_FRAME_TIME, ROBO_SHEET_FRAMES);
    sp->SetAnimationLines(4);
    associated.AddComponent(sp);

    /*
        box.w e box.h de Robo só são usados por comodidade/praticidade
        o Width e Height que realmente importam são os de sp.
    */
    associated.box.h = sp->GetHeight();
    associated.box.w = sp->GetWidth();

    /*
        Barra de vida
    */
    Bar* barraVida =  new Bar(associated, 200, BARRA_VIDA_MOLDURA, BARRA_VIDA);
    barraVida->Centralize(0, (5/8.0)*associated.box.h);// (int)5/8.0(float) spritesheet mal diagramada
    associated.AddComponent(barraVida);

    /*
        Barra de cooldown
    */
    Bar* coolDownBar = new Bar(associated, 10, BARRA_COOLDDOWN_MOLDURA, BARRA_COOLDOWN);
    coolDownBar->Centralize(0,(5/8.0)*associated.box.h + 10);// 5/8.0 spritesheet mal diagramada

    coolDownBar->SetRefilAuto(10);
    coolDownBar->SetPoints(0);

    associated.AddComponent(coolDownBar);

    DEBUG_PRINT("Robo::Robo()-fim");
}

Robo::~Robo(){
}

void Robo::Update(float dt){
}

void Robo::Render(){
}

bool Robo::Is(ComponentType type)const{
    return type == ROBO;
}

void Robo::EarlyUpdate(float dt){}
void Robo::LateUpdate(float dt){}

#ifdef DEBUG
    #undef DEBUG
#endif
