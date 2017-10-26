#include "../include/PlayerUnity.h"

#include "Error.h"
PlayerUnity::PlayerUnity(GameObject& associated, State* stage, float x, float y):
    Component(associated),
    stage(stage),
    clicked(false),
    selected(false),
    barraVida( *(new GameObject()) ),
    barraCoolDown( *(new GameObject()) ),
    direction(DOWN),
    roboState(IDLE),
    playerUnityMenu(nullptr)
{
    DEBUG_CONSTRUCTOR("inicio");
    /*
        Coloca a image no playerUnity
    */
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

    playerUnityMenu = new GameObject();
    playerUnityMenu->parent = &associated;
    playerUnityMenu->AddComponent(new PlayerUnityMenu(*playerUnityMenu, stage));
    stage->AddObject(playerUnityMenu);
    playerUnityMenu->debug = true;

    movingPath = new GameObject();
    movingPath->parent = &associated;
    movingPath->AddComponent(new RoboPath(*movingPath, destination));
    stage->AddObject(movingPath);

    DEBUG_CONSTRUCTOR("box:{" <<
                      associated.box.x << ", " <<
                      associated.box.y << ", " <<
                      associated.box.w << ", " <<
                      associated.box.h << "}");
    DEBUG_CONSTRUCTOR("fim");
}

PlayerUnity::~PlayerUnity()
{
}

void PlayerUnity::Update(float dt)
{
    debug();
    TryMove();
    onClick();
    UpdateState();
}

void PlayerUnity::Render()
{
}

bool PlayerUnity::Is(ComponentType type)const
{
    return (type == PLAYER_UNITY);
}

void PlayerUnity::EarlyUpdate(float dt) {}
void PlayerUnity::LateUpdate(float dt) {}

void PlayerUnity::onClick()
{
    if(InputManager::GetInstance().MouseRelease(LEFT_MOUSE_BUTTON))
    {
        if(InputManager::GetInstance().GetMousePos().IsInRect(associated.box))
        {
            DEBUG_PRINT("Click em PlayerUnity");
        }
        else
        {
        }
    }
}

void PlayerUnity::UpdateState()
{
    switch(roboState)
    {
    case IDLE:
        break;
    case MOVING:
        //TODO: Condição fraca, melhorar depois
        if(destination.x == associated.box.x &&
                destination.y == associated.box.y)
        {
            roboState = IDLE;
        }
        else
        {
            if(destination.x > associated.box.x)
            {
                if(direction != RIGHT) ChangeDirection(RIGHT);
                associated.box.x += 1;
            }
            else if(destination.x < associated.box.x)
            {
                if(direction != LEFT) ChangeDirection(LEFT);
                associated.box.x -= 1;
            }
            if(destination.y > associated.box.y)
            {
                if(direction != DOWN) ChangeDirection(DOWN);
                associated.box.y += 1;
            }
            else if(destination.y < associated.box.y)
            {
                if(direction != UP) ChangeDirection(UP);
                associated.box.y -= 1;
            }
        }
        break;
    }
}

void PlayerUnity::TryMove()
{
    Vec2 aux(associated.box.x, associated.box.y);
    if(roboState != MOVING && destination.DistanceTo(aux) > 0 )
    {
        roboState = MOVING;
    }
}

void PlayerUnity::MenuOpen()
{
}

void PlayerUnity::MenuClose()
{
    playerUnityMenu->RequestDelete();
    playerUnityMenu = nullptr;
}

void PlayerUnity::SetPosition(float x, float y)
{
    associated.box.x = x;
    associated.box.y = y;
}

void PlayerUnity::ChangeDirection(Direction dir)
{
    switch(dir)
    {
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

Vec2& PlayerUnity::Destination()
{
    return destination;
}

void PlayerUnity::debug()
{
    if(associated.debug)
    {
        if(InputManager::GetInstance().KeyPress(SDLK_LEFT))
        {
            ChangeDirection(LEFT);
        }
        if(InputManager::GetInstance().KeyPress(SDLK_UP))
        {
            ChangeDirection(UP);
        }
        if(InputManager::GetInstance().KeyPress(SDLK_RIGHT))
        {
            ChangeDirection(RIGHT);
        }
        if(InputManager::GetInstance().KeyPress(SDLK_DOWN))
        {
            ChangeDirection(DOWN);
        }
    }
    if(InputManager::GetInstance().KeyPress(SDLK_0))
    {
        associated.debug = !associated.debug;
    }
}

GameObject* PlayerUnity::GetMenu(){
    return playerUnityMenu;
}

#include "Error_footer.h"
