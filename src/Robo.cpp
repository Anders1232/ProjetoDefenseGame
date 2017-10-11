#include "../include/Robo.h"

#include "Error.h"
Robo::Robo(GameObject& associated, State* stage, float x, float y, string file):
    Component(associated),
    associated(associated),
    stage(stage),
    selected(false),
    barraVida( *(new GameObject()) ),
    barraCoolDown( *(new GameObject()) )
{
    DEBUG_CONSTRUCTOR("Robo", "inicio");
    associated.AddComponent(new RectTransform(associated, nullptr));

    /*
        Ao criar o Robo, ele que organiza como será o GameObject
    */

    /*
        Coloca a image do robo
    */
    sp = new Sprite(associated, file, true, ROBO_SHEET_FRAME_TIME, ROBO_SHEET_FRAMES);
    sp->SetAnimationLines(4);
    associated.AddComponent(sp);
    (dynamic_cast<RectTransform&>(associated.GetComponent(RECT_TRANSFORM))).SetAnchors(0,0,1,1);

    /*
        Barra de vida
    */
//    barraVida.AddComponent(new RectTransform(barraVida, &associated));
//    (dynamic_cast<RectTransform&>(barraVida.GetComponent(RECT_TRANSFORM))).SetAnchors(0,0,1,1);
//    barraVida.AddComponent(new Bar(barraVida, 200, BARRA_VIDA_MOLDURA, BARRA_VIDA));
//    stage->AddObject(&barraVida);


    /*
        Barra de cooldown
    */
//    barraCoolDown.AddComponent(new RectTransform(barraCoolDown, &associated));
//    (dynamic_cast<RectTransform&>(barraCoolDown.GetComponent(RECT_TRANSFORM))).SetAnchors(0,0,1,1);
//    barraCoolDown.AddComponent(new Bar(associated, 10, BARRA_COOLDDOWN_MOLDURA, BARRA_COOLDOWN));
//    stage->AddObject(&barraCoolDown);

//    barraCoolDown->Centralize(0,(5/8.0)*associated.box.h + 10);// 5/8.0 spritesheet mal diagramada
//    barraCoolDown->SetRefilAuto(10);
//    barraCoolDown->SetPoints(0);

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
            Mostra os botões do menu
        */
            GameObject* buttonObject = new GameObject();            //Cria o objeto
            stage->AddObject(buttonObject);                         //adiciona objeto ao state
            buttonObject->AddComponent(new RectTransform(*buttonObject, &associated));
            buttonObject->AddComponent(new Sprite(*buttonObject, BOTAO4, true));
            (dynamic_cast<RectTransform&>(buttonObject->GetComponent(RECT_TRANSFORM))).SetAnchors(0, 0, 1, 1);
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
