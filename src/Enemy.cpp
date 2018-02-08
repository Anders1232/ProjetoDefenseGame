#include "Enemy.h"
#include "Error.h"

Enemy::Enemy(GameObject& associated, string spritePath, Vec2 position, TileMap<TileInfo>* tileMap):
    Component(associated),
    characterStatus(* (new CharacterStatus(associated)) ),
    tileMap(tileMap),
    nextPointIndex(0),
    enemyState(IDLE),
    direction(DOWN)
{
    DEBUG_CONSTRUCTOR("inicio");
    Vec2 pixelPosition = tileMap->MapToPixel(position);
    tileMap->At(position.x, position.y).PutCharacter(associated);
    associated.SetPosition(pixelPosition);
    Sprite* sp = new Sprite(associated, spritePath, true, 0.2, 2);
    sp->SetAnimationLines(4);
    associated.AddComponent(sp);
    patrolPoints.push_back(pixelPosition);
    DEBUG_CONSTRUCTOR("fim");
    //ctor
}

Enemy::~Enemy()
{
    //dtor
}

void Enemy::EarlyUpdate(float dt){}
void Enemy::Update(float dt){
    if(patrolPoints.size() > 1){
        Walk();
    }
}
void Enemy::LateUpdate(float dt){}
void Enemy::Render(){}
bool Enemy::Is(unsigned int type) const{
    return type == ENEMY;
}

void Enemy::AddPatrolPoint(Vec2 patrolPoint){
    patrolPoints.push_back(tileMap->MapToPixel(patrolPoint));
}

void Enemy::Walk(){
    Vec2 currentPosition(associated.box.x, associated.box.y);
    Vec2 destination(patrolPoints[nextPointIndex]);
    if(currentPosition == destination){
        nextPointIndex++;
        if(nextPointIndex == patrolPoints.size()) nextPointIndex = 0;
        destination = patrolPoints[nextPointIndex];
    }
    else
    {
        if(destination.x > currentPosition.x)
        {
            if(direction != RIGHT) ChangeDirection(RIGHT);
            associated.box.x += 1;
        }
        else if(destination.x < currentPosition.x)
        {
            if(direction != LEFT) ChangeDirection(LEFT);
            associated.box.x -= 1;
        }
        if(destination.y > currentPosition.y)
        {
            if(direction != DOWN) ChangeDirection(DOWN);
            associated.box.y += 1;
        }
        else if(destination.y < currentPosition.y)
        {
            if(direction != UP) ChangeDirection(UP);
            associated.box.y -= 1;
        }
    }
}

void Enemy::ChangeDirection(Direction dir)
{
    DEBUG_PRINT("inicio");
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
        (dynamic_cast<Sprite&>(associated.GetComponent(SPRITE))).SetAnimationLine(2);
        break;
    case RIGHT:
        direction = RIGHT;
        (dynamic_cast<Sprite&>(associated.GetComponent(SPRITE))).SetAnimationLine(1);
        break;
    }
    DEBUG_PRINT("fim");
}

