#include "../include/Robo.h"

#include "Error.h"
Robo::Robo(GameObject& associated, State* stage, float x, float y, string file):
    Component(associated),
    associated(associated),
    stage(stage),
    clicked(false),
    selected(false),
    barraVida( *(new GameObject()) ),
    barraCoolDown( *(new GameObject()) ),
    direction(DOWN),
    roboState(IDLE),
    button(nullptr)
{
    DEBUG_CONSTRUCTOR("Robo", "inicio");
    /*
        Coloca a image do robo
    */
    sp = new Sprite(associated, file, true, ROBO_SHEET_FRAME_TIME, ROBO_SHEET_FRAMES);
    sp->SetAnimationLines(4);
    associated.AddComponent(sp);
    associated.box.w = sp->GetWidth();
    associated.box.h = sp->GetHeight();

    SetPosition(50, 50);
    destination.x = associated.box.x;
    destination.y = associated.box.y;
    /*
        Barra de vida
    */
    barraVida.parent = &associated;
    barraVida.AddComponent(new Bar(barraVida, 200, BARRA_VIDA_MOLDURA, BARRA_VIDA));
    stage->AddObject(&barraVida);
    (dynamic_cast<Bar&>(barraVida.GetComponent(BAR))).Centralize(0,(5/8.0)*associated.box.h);

    /*
        Barra de cooldown
    */
    barraCoolDown.parent = &associated;
    barraCoolDown.AddComponent(new Bar(barraCoolDown, 10, BARRA_COOLDDOWN_MOLDURA, BARRA_COOLDOWN));
    stage->AddObject(&barraCoolDown);

    (dynamic_cast<Bar&>(barraCoolDown.GetComponent(BAR))).Centralize(0,(5/8.0)*associated.box.h + 10);// 5/8.0 spritesheet mal diagramada
    (dynamic_cast<Bar&>(barraCoolDown.GetComponent(BAR))).SetRefilAuto(10);
    (dynamic_cast<Bar&>(barraCoolDown.GetComponent(BAR))).SetPoints(0);

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
    debug();
    onClick();
    UpdateState();
}

void Robo::Render(){
}

bool Robo::Is(ComponentType type)const{
    return type == ROBO;
}

void Robo::EarlyUpdate(float dt){}
void Robo::LateUpdate(float dt){}

void Robo::onClick(){
    if(InputManager::GetInstance().MouseRelease(LEFT_MOUSE_BUTTON)){
        if(InputManager::GetInstance().GetMousePos().IsInRect(associated.box)){
            DEBUG_PRINT("Robo", "Click em Robo");
            clicked = !clicked;
            if(clicked) MenuOpen();
            if(!clicked) MenuClose();
       }else{
           if(clicked){
                clicked = false;
                MenuClose();
           }
       }
    }
}

void Robo::UpdateState(){
    switch(roboState){
    case IDLE:
        TryMove();
        break;
    case MOVING:
        if(destination.x == associated.box.x &&
           destination.y == associated.box.y){
               DEBUG_PRINT("Robo", "chegou em (" << destination.x << "," << destination.y << ")");
               if(movingPath->size() > 0){
                    DEBUG_PRINT("Robo", "pega proximo ponto");
                    destination = *(movingPath->front());
                    delete(movingPath->front());
                    movingPath->erase(movingPath->begin());
               }else{
                    DEBUG_PRINT("Robo", "encerrou o vetor");
                    roboState = IDLE;
                    delete(movingPath);
               }
           }
        if(destination.x > associated.box.x){
            if(direction != RIGHT) Move(RIGHT);
            associated.box.x += 1;
        }else if(destination.x < associated.box.x){
            if(direction != LEFT) Move(LEFT);
            associated.box.x -= 1;
        }
        if(destination.y > associated.box.y){
            if(direction != DOWN) Move(DOWN);
            associated.box.y += 1;
        }else if(destination.y < associated.box.y){
            if(direction != UP) Move(UP);
            associated.box.y -= 1;
        }
        break;
    }
}

void Robo::TryMove(){
    if(InputManager::GetInstance().GetMousePos().IsInRect(associated.box) &&
       !selected &&
       InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON)){
           DEBUG_PRINT("Robo", "selecionado");
           selected = true;
           movingPath = new vector<Vec2*>();
    }
    if(selected){
        if(InputManager::GetInstance().GetMousePos().x > destination.x + associated.box.w ||
           InputManager::GetInstance().GetMousePos().x < destination.x - associated.box.w){
            DEBUG_PRINT("Robo", "adicionado ponto(" << destination.x + associated.box.w << ", " << destination.y << ")");
            movingPath->push_back(new Vec2(InputManager::GetInstance().GetMousePos().x, destination.y) );
            destination.x = InputManager::GetInstance().GetMousePos().x;
        }
        if(InputManager::GetInstance().GetMousePos().y > destination.y + associated.box.h ||
           InputManager::GetInstance().GetMousePos().y < destination.y - associated.box.h ){
            DEBUG_PRINT("Robo", "adicionado ponto(" << destination.x << ", " << destination.y + associated.box.h << ")");
            movingPath->push_back(new Vec2(destination.x, InputManager::GetInstance().GetMousePos().y) );
            destination.y = InputManager::GetInstance().GetMousePos().y;
        }
    }
    if(selected &&
       InputManager::GetInstance().MouseRelease(LEFT_MOUSE_BUTTON)){
        selected = false;
        DEBUG_PRINT("Robo", "solto");
        if(movingPath != nullptr && movingPath->size() > 0){
            destination = *(movingPath->front());
            delete(movingPath->front());
            movingPath->erase(movingPath->begin());
            roboState = MOVING;
        }
    }
}

void Robo::MenuOpen(){
    button = new GameObject();            //Cria o objeto
    button->parent = &associated;
    stage->AddObject(button);                         //adiciona objeto ao state
    button->AddComponent(new Sprite(*button, BOTAO4, true));

    //            Button* btnComponent = new Button(*buttonObject);
    //            Button::Callback callbackFunction;
    //            callbackFunction.callbackFunc = Eject;
    //            callbackFunction.caller = this;

    //            btnComponent->SetReleaseCallback(callbackFunction);
    //            buttonObject->AddComponent(btnComponent);
}

void Robo::MenuClose(){
    button->RequestDelete();
    button = nullptr;
}

void Robo::SetPosition(float x, float y){
    associated.box.x = x;
    associated.box.y = y;
}

void Eject(void*){
    DEBUG_PRINT("Eject", "Olha eu");
}

void Robo::Move(Direction dir){
    switch(dir){
    case UP:
        (dynamic_cast<Sprite&>(associated.GetComponent(SPRITE))).SetAnimationLine(3);
        associated.box.y -= 1;
        break;
    case DOWN:
        (dynamic_cast<Sprite&>(associated.GetComponent(SPRITE))).SetAnimationLine(0);
        associated.box.y += 1;
        break;
    case LEFT:
        (dynamic_cast<Sprite&>(associated.GetComponent(SPRITE))).SetAnimationLine(1);
        associated.box.x -= 1;
        break;
    case RIGHT:
        (dynamic_cast<Sprite&>(associated.GetComponent(SPRITE))).SetAnimationLine(2);
        associated.box.x += 1;
        break;
    }
}

void Robo::debug(){
    if(InputManager::GetInstance().KeyPress(SDLK_LEFT)){
        Move(LEFT);
    }
    if(InputManager::GetInstance().KeyPress(SDLK_UP)){
        Move(UP);
    }
    if(InputManager::GetInstance().KeyPress(SDLK_RIGHT)){
        Move(RIGHT);
    }
    if(InputManager::GetInstance().KeyPress(SDLK_DOWN)){
        Move(DOWN);
    }
    if(InputManager::GetInstance().KeyPress(SDLK_0)){
        associated.debug = !associated.debug;
    }
}

#include "Error_footer.h"
