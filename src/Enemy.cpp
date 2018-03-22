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
    is = "Enemy";
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
            //DEBUG_PRINT("enemy: IDLE");
            if(charactersInRange.size() > 0){
                for(unsigned int i = 0; i < charactersInRange.size(); i++){
                    DEBUG_UPDATE("[" << charactersInRange[i] << "] Esta proximo!");
                    if(charactersInRange[i]->is == "PlayerUnity"){
                       attackTimer.Update(dt);
                       if(attackTimer.Get() > 3 ){
                           attackTimer.Restart();
                           charState = CharacterState::ATTAKCING;
                           //Attack(charactersInRange[i]);
                       }
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
            if(destination == nullptr){
                charState = IDLE;
            }else{
                Walk();
            }
            break;
        case CharacterState::ATTAKCING:
            attackTimer.Update(dt);
            if(attackTimer.Get() > 3){
                attackTimer.Restart();
                charState = CharacterState::IDLE;
                if( charactersInRange.size() > 0){
                    for(unsigned int i = 0; i < charactersInRange.size(); i++){
                        if(charactersInRange[i]->is == "PlayerUnity"){
                           charState = CharacterState::ATTAKCING;
                           Attack(charactersInRange[i]);
                        }
                    }
                }
            }
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
