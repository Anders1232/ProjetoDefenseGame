#include "Enemy.h"
#include "GameObject.h"
#include "Sprite.h"

#include "Error.h"

using std::string;
using std::vector;

Enemy::Enemy(GameObject& associated, string spritePath, Vec2 position, TileMap<TileInfo>* tileMap):
    CharacterStatus(associated, position, tileMap),
    nextPointIndex(0),
    attackSound("resources/audio/boom.wav")
{
    DEBUG_CONSTRUCTOR("inicio");
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
            Walk();
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
    if(attackTimer.Get() > attackCoolDown){
        attackTimer.Restart();
        if( charactersInRange.size() > 0){
            for(unsigned int i = 0; i < charactersInRange.size(); i++){
                if(charactersInRange[i]->charType == other){
                   charState = CharacterState::ATTAKCING;
                   CharacterStatus::Attack(charactersInRange[i]);
                }
            }
        }else{
            charState = CharacterState::IDLE;
        }
    }
    attackSound.Play(1);
    //DEBUG_PRINT("fim");
}

void Enemy::Walk(){
    //DEBUG_PRINT("inicio");
    if(destination == nullptr){
        charState = CharacterState::IDLE;
    }else{
        CharacterStatus::Walk();
    }
    //DEBUG_PRINT("fim");

}
