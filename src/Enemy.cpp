#include "Enemy.h"
#include "GameObject.h"
#include "Sprite.h"

#include "Error.h"

using std::string;
using std::vector;

Enemy::Enemy(GameObject& associated, string spritePath, Vec2 position, TileMap<TileInfo>* tileMap):
    CharacterStatus(associated, position, tileMap),
    nextPointIndex(0)
{
    DEBUG_CONSTRUCTOR("inicio");
    attackSound.Open("resources/audio/cartoon-punch-04.ogg");
    dieSound.Open("resources/audio/boom.wav");
    SetStatus(20, 10, 10, 1, 5, 1, 0, 0, 1);
    charType = CharacterType::ENEMY;
    CharacterStatus::charState = CharacterState::WALKING;

    Sprite* sp = new Sprite(associated, spritePath, true, 0.2, 2);
    sp->SetAnimationLines(4);
    associated.AddComponent(sp);
    associated.SetCenterPosition(tileMap->CellCenterToPixel(position));
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
    DEBUG_UPDATE("inicio");
    CharacterStatus::Update(dt);
    switch(charState){
        case CharacterState::IDLE:
            if(charactersInRange.size() > 0){
                for(unsigned int i = 0; i < charactersInRange.size(); i++){
                    DEBUG_UPDATE("[" << charactersInRange[i] << "] Esta proximo!");
                    if(charactersInRange[i]->charType == CharacterType::PLAYER_UNITY){
                        charState = CharacterState::ATTAKCING;
                    }
                }
            }else if(patrolPoints.size() > 1){
                SetDestination(patrolPoints[nextPointIndex]);
                if(destination){
                    DEBUG_UPDATE("Novo destination: " << destination->x << ", " << destination->y);
                }
                nextPointIndex++;
                if(nextPointIndex == patrolPoints.size()) nextPointIndex = 0;
                charState = CharacterState::WALKING;
            }
            break;
        case CharacterState::WALKING:
            Walk(dt);
            break;
        case CharacterState::ATTAKCING:
            attackTimer.Update(dt);
            Attack(CharacterType::PLAYER_UNITY);
            break;
        case CharacterState::DEAD:
            break;
        default:
            break;
    }
    DEBUG_UPDATE("fim");
}
void Enemy::LateUpdate(float dt){}
void Enemy::Render(){}
bool Enemy::Is(unsigned int type) const{
    return type == ENEMY;
}

void Enemy::AddPatrolPoint(Vec2 patrolPoint){
    patrolPoints.push_back(patrolPoint);
}

void Enemy::Attack(CharacterType other){
    //DEBUG_PRINT("inicio");
    if(attackTimer.Get() > status.attackCoolDown){
        attackTimer.Restart();
        if( charactersInRange.size() > 0){
            for(unsigned int i = 0; i < charactersInRange.size(); i++){
                if(charactersInRange[i]->charType == other){
                   charState = CharacterState::ATTAKCING;
                   CharacterStatus::Attack(charactersInRange[i]);
                   attackSound.Play(1);
                }
            }
        }else{
            charState = CharacterState::IDLE;
        }
    }
    //DEBUG_PRINT("fim");
}

void Enemy::Walk(float dt){
    //DEBUG_PRINT("inicio");
    if(destination == nullptr){
        charState = CharacterState::IDLE;
    }else{
        CharacterStatus::Walk(dt);
    }
    //DEBUG_PRINT("fim");
}

void Enemy::Die(){
    CharacterStatus::Die();
    dieSound.Play(1);
    associated.RequestDelete();
}
