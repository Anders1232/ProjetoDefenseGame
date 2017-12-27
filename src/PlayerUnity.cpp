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
    playerUnityState(IDLE),
    playerUnityMenu(nullptr)
{
    associated.box.x = x;
    associated.box.y = y;
    DEBUG_CONSTRUCTOR("inicio");
    destination.x = associated.box.x;
    destination.y = associated.box.y;

    /*
        Barra de vida
    */
    barraVida.SetParent(associated, -16, 64);//Hardcoded = posicionando a barra em relação ao parent
    barraVida.AddComponent(new Bar(barraVida, 200, BARRA_VIDA_MOLDURA, BARRA_VIDA));
    stage->AddObject(&barraVida);

    /*
        Barra de cooldown
    */
    barraCoolDown.SetParent(associated, -14, 74);//Hardcoded = posicionando a barra em relação ao parent
    barraCoolDown.AddComponent(new Bar(barraCoolDown, 10, BARRA_COOLDDOWN_MOLDURA, BARRA_COOLDOWN));
    stage->AddObject(&barraCoolDown);

    (dynamic_cast<Bar&>(barraCoolDown.GetComponent(BAR))).SetRefilAuto(10);
    (dynamic_cast<Bar&>(barraCoolDown.GetComponent(BAR))).SetPoints(0);

    playerUnityMenu = new GameObject();
    playerUnityMenu->SetParent(associated);
    PlayerUnityMenu* playerUnityMenuComponent = new PlayerUnityMenu(*playerUnityMenu, stage);
    playerUnityMenu->AddComponent(playerUnityMenuComponent);
    stage->AddObject(playerUnityMenu);
    playerUnityMenu->debug = true;

    movingPath = new GameObject();
    movingPath->SetParent(associated);
    RoboPath* roboPathComponent = new RoboPath(*movingPath, destination);
    movingPath->AddComponent(roboPathComponent);
    stage->AddObject(movingPath);

    //roboPathComponent contem uma função que será atribuida a um botão do menu
    playerUnityMenuComponent->AddButton(BOTAO1, roboPathComponent);

    //O menu reage a um evento do roboPath:
    //Quando terminar de criar o caminho, os listeners serão chamados
    playerUnityMenuComponent->SubscribeToPath(*roboPathComponent);

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

void PlayerUnity::Render() const
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
    switch(playerUnityState)
    {
    case IDLE:
        break;
    case MOVING:
        //TODO: Condição fraca, melhorar depois
        if(destination.x == associated.box.x &&
                destination.y == associated.box.y)
        {
            playerUnityState = IDLE;
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
    if(playerUnityState != MOVING && destination.DistanceTo(aux) > 0 )
    {
        playerUnityState = MOVING;
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
