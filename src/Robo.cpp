#include "../include/Robo.h"

#include "Error.h"
Robo::Robo(GameObject& associated, State* stage, float x, float y, string file):
    Component(associated),
    associated(associated),
    stage(stage),
    selected(false)
{
    DEBUG_CONSTRUCTOR("Robo", "inicio");
//    RectTransform* rt = new RectTransform(associated, nullptr);
//    rt->debugRender = true;
//    associated.AddComponent(rt);

    /*
        Ao criar o Robo, ele que organiza como ser� o GameObject
    */
    associated.box.x = x;
    associated.box.y = y;

    /*
        Coloca a image do robo
    */
    sp = new Sprite(associated, file, true, ROBO_SHEET_FRAME_TIME, ROBO_SHEET_FRAMES);
    sp->SetAnimationLines(4);
    associated.AddComponent(sp);

    /*
        box.w e box.h de Robo s�o usados para dar referencia aos outros
        objetos que ele vier a criar
    */
    associated.box.h = sp->GetHeight();
    associated.box.w = sp->GetWidth();

    /*
        Barra de vida
    */
    barraVida =  new Bar(associated, 200, BARRA_VIDA_MOLDURA, BARRA_VIDA);
    barraVida->Centralize(0, (5/8.0)*associated.box.h);// (int)5/8.0(float) spritesheet mal diagramada
    associated.AddComponent(barraVida);

    /*
        Barra de cooldown
    */
    barraCoolDown = new Bar(associated, 10, BARRA_COOLDDOWN_MOLDURA, BARRA_COOLDOWN);
    associated.AddComponent(barraCoolDown);

    barraCoolDown->Centralize(0,(5/8.0)*associated.box.h + 10);// 5/8.0 spritesheet mal diagramada
    barraCoolDown->SetRefilAuto(10);
    barraCoolDown->SetPoints(0);

    DEBUG_CONSTRUCTOR("Robo", "box:{" <<
                      associated.box.x << ", " <<
                      associated.box.y << ", " <<
                      associated.box.w << ", " <<
                      associated.box.h << "}");
    DEBUG_CONSTRUCTOR("Robo", "fim");
}

Robo::~Robo(){
}

void Robo::Update(float dt){
    onClick();
}

void Robo::Render(){
}

bool Robo::Is(ComponentType type)const{
    return type == ROBO;
}

void Robo::EarlyUpdate(float dt){}
void Robo::LateUpdate(float dt){}

void Robo::onClick(){
    if(InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON)){
        DEBUG_PRINT("Robo", "associated.box:{" <<
                      associated.box.x << ", " <<
                      associated.box.y << ", " <<
                      associated.box.w << ", " <<
                      associated.box.h << "}");
        DEBUG_PRINT("Robo", "IsInRect: " << InputManager::GetInstance().GetMousePos().IsInRect(associated.box));
       if(InputManager::GetInstance().GetMousePos().IsInRect(associated.box)){
       DEBUG_PRINT("Robo", "Click em Robo");
       /*
            Mostra os bot�es do menu
        */
            GameObject* buttonObject = new GameObject();            //Cria o objeto
            buttonObject->box.x = associated.box.x + associated.box.w;
            buttonObject->box.y = associated.box.y + associated.box.h;
            buttonObject->box.w = associated.box.w;
            buttonObject->box.h = associated.box.h;
            stage->AddObject(buttonObject);                         //adiciona objeto ao state
            buttonObject->AddComponent(new RectTransform(*buttonObject, &associated));
            buttonObject->AddComponent(new Sprite(*buttonObject, BOTAO4, true));

            Button* btnComponent = new Button(*buttonObject);
            Button::Callback callbackFunction;
            callbackFunction.callbackFunc = Eject;
            callbackFunction.caller = this;

            btnComponent->SetReleaseCallback(callbackFunction);
            buttonObject->AddComponent(btnComponent);
       }else{
       }
    }
}

void Eject(void*){
    DEBUG_PRINT("Eject", "Olha eu");
}

#include "Error_footer.h"
