#include "../include/Robo.h"

#include "Error.h"
Robo::Robo(GameObject& associated, State* stage, float x, float y, string file):
    Component(associated),
    stage(stage),
    clicked(false),
    selected(false),
    barraVida( *(new GameObject()) ),
    barraCoolDown( *(new GameObject()) ),
    direction(DOWN),
    roboState(IDLE),
    roboMenu(nullptr)
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
    TryMove();
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
        break;
    case MOVING:
        //TODO: Condição fraca, melhorar depois
        if(destination.x == associated.box.x &&
           destination.y == associated.box.y){
               DEBUG_PRINT("Robo", "chegou em (" << destination.x << "," << destination.y << ")");
               if( (dynamic_cast<RoboPath&>(movingPath->GetComponent(ROBOPATH))).HasPoints() ){
                    DEBUG_PRINT("Robo", "pega proximo ponto");
                    destination = (dynamic_cast<RoboPath&>(movingPath->GetComponent(ROBOPATH))).GetNext();
               }else{
                    DEBUG_PRINT("Robo", "encerrou o vetor");
                    roboState = IDLE;
                    movingPath->RequestDelete();
               }
        }
        if(destination.x > associated.box.x){
            if(direction != RIGHT) ChangeDirection(RIGHT);
            associated.box.x += 1;
        }else if(destination.x < associated.box.x){
            if(direction != LEFT) ChangeDirection(LEFT);
            associated.box.x -= 1;
        }
        if(destination.y > associated.box.y){
            if(direction != DOWN) ChangeDirection(DOWN);
            associated.box.y += 1;
        }else if(destination.y < associated.box.y){
            if(direction != UP) ChangeDirection(UP);
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
           movingPath = new GameObject();
           movingPath->parent = &associated;

           Vec2 temp(associated.box.x, associated.box.y);
           movingPath->AddComponent(new RoboPath(*movingPath, temp));
           stage->AddObject(movingPath);
    }
    if(selected){
        (dynamic_cast<RoboPath&>(movingPath->GetComponent(ROBOPATH))).CreatePath();
    }
    if(selected &&
       !InputManager::GetInstance().GetMousePos().IsInRect(associated.box) &&
       InputManager::GetInstance().MouseRelease(LEFT_MOUSE_BUTTON)){
        selected = false;
        DEBUG_PRINT("Robo", "solto");
        if(movingPath != nullptr &&
           (dynamic_cast<RoboPath&>(movingPath->GetComponent(ROBOPATH))).HasPoints()){
                destination = (dynamic_cast<RoboPath&>(movingPath->GetComponent(ROBOPATH))).GetNext();
                roboState = MOVING;
        }
    }
}

void Robo::MenuOpen(){
    roboMenu = new GameObject();
    roboMenu->parent = &associated;

    roboMenu->AddComponent(new RoboMenu(*roboMenu));
    stage->AddObject(roboMenu);
}

void Robo::MenuClose(){
    roboMenu->RequestDelete();
    roboMenu = nullptr;
}

void Robo::SetPosition(float x, float y){
    associated.box.x = x;
    associated.box.y = y;
}

void Eject(void*){
    DEBUG_PRINT("Eject", "Olha eu");
}

void Robo::ChangeDirection(Direction dir){
    switch(dir){
    case UP:
        direction = UP;
        (dynamic_cast<Sprite&>(associated.GetComponent(SPRITE))).SetAnimationLine(3);
        break;
    case DOWN:
        direction = DOWN;
        (dynamic_cast<Sprite&>(associated.GetComponent(SPRITE))).SetAnimationLine(0);
        break;
    case LEFT:
        direction = LEFT;
        (dynamic_cast<Sprite&>(associated.GetComponent(SPRITE))).SetAnimationLine(1);
        break;
    case RIGHT:
        direction = RIGHT;
        (dynamic_cast<Sprite&>(associated.GetComponent(SPRITE))).SetAnimationLine(2);
        break;
    }
}

void Robo::debug(){
    if(associated.debug){
        if(InputManager::GetInstance().KeyPress(SDLK_LEFT)){
            ChangeDirection(LEFT);
        }
        if(InputManager::GetInstance().KeyPress(SDLK_UP)){
            ChangeDirection(UP);
        }
        if(InputManager::GetInstance().KeyPress(SDLK_RIGHT)){
            ChangeDirection(RIGHT);
        }
        if(InputManager::GetInstance().KeyPress(SDLK_DOWN)){
            ChangeDirection(DOWN);
        }
    }
    if(InputManager::GetInstance().KeyPress(SDLK_0)){
        associated.debug = !associated.debug;
    }
}

#include "Error_footer.h"
