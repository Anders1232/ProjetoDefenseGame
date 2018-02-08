#include "Enemy.h"
#include "Error.h"

Enemy::Enemy(GameObject& associated, string spritePath, Vec2 position, TileMap<TileInfo>* tileMap):
    Component(associated),
    characterStatus(* (new CharacterStatus(associated)) ),
    tileMap(tileMap),
    nextPointIndex(0)
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
        Vec2 destination(patrolPoints[nextPointIndex]);
        Vec2 currentPosition(associated.box.x, associated.box.y);
        if(currentPosition == destination){
            nextPointIndex++;
            if(nextPointIndex == patrolPoints.size()) nextPointIndex = 0;
            destination = patrolPoints[nextPointIndex];
        }
        characterStatus.Walk(destination);
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
