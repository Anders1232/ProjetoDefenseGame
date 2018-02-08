#ifndef ENEMY_H
#define ENEMY_H

#include <string>
#include <vector>

#include "Component.h"
#include "GameComponentType.h"
#include "GameObject.h"
#include "Sprite.h"
#include "Vec2.h"
#include "TileMap.h"

#include "TileInfo.h"
#include "CharacterStatus.h"

using std::string;
using std::vector;

class Enemy : public Component
{
private:
    enum Direction{
        UP = 0,
        DOWN,
        LEFT,
        RIGHT
    };
    enum EnemyState{
        IDLE = 0,
        MOVING,
    };
    public:
        Enemy(GameObject& associated, string spritePath, Vec2 position, TileMap<TileInfo>* tileMap);
        virtual ~Enemy();
        void EarlyUpdate(float dt);
        void Update(float dt);
        void LateUpdate(float dt);
        void Render();
        bool Is(unsigned int type) const;
        void AddPatrolPoint(Vec2 patrolPoint);
        void Walk();
        void ChangeDirection(Direction dir);

    protected:

    private:
        Component& characterStatus;
        EnemyState enemyState;
        Direction direction;

        int nextPointIndex;
        TileMap<TileInfo>* tileMap;
        vector<Vec2> patrolPoints;
};

#endif // ENEMY_H
