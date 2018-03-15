#include "Enemy.h"
#include "GameObject.h"
#include "Sprite.h"

#include "Error.h"

using std::string;
using std::vector;

Enemy::Enemy(GameObject& associated, string spritePath, Vec2 position, TileMap<TileInfo>* tileMap):
    CharacterStatus(associated, position, tileMap),
    nextPointIndex(0),
    tileMap(tileMap)
{
    DEBUG_CONSTRUCTOR("inicio");
    CharacterStatus::charState = CharacterState::WALKING;

    Sprite* sp = new Sprite(associated, spritePath, true, 0.2, 2);
    sp->SetAnimationLines(4);
    associated.AddComponent(sp);
    patrolPoints.push_back( position );
    DEBUG_CONSTRUCTOR("fim");
    //ctor
}

Enemy::~Enemy()
{
    //dtor
}

void Enemy::EarlyUpdate(float dt){}
void Enemy::Update(float dt){
    CharacterStatus::Update(dt);
    switch(charState){
    case CharacterState::IDLE:
        if(patrolPoints.size() > 1){
            SetDestination(patrolPoints[nextPointIndex]);
            if(destination){
                DEBUG_PRINT("Novo destination: " << destination->x << ", " << destination->y);
            }
            nextPointIndex++;
            if(nextPointIndex == patrolPoints.size()) nextPointIndex = 0;
            charState = CharacterState::WALKING;
        }
        break;
    case CharacterState::WALKING:
        if(destination == nullptr){
            charState = IDLE;
        }else{
            Walk();
        }
        break;
    }


}
void Enemy::LateUpdate(float dt){}
void Enemy::Render(){}
bool Enemy::Is(unsigned int type) const{
    return type == ENEMY;
}

void Enemy::AddPatrolPoint(Vec2 patrolPoint){
    patrolPoints.push_back(patrolPoint);
}
