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
    public:
        Enemy(GameObject& associated, string spritePath, Vec2 position, TileMap<TileInfo>* tileMap);
        virtual ~Enemy();
        void EarlyUpdate(float dt);
        void Update(float dt);
        void LateUpdate(float dt);
        void Render();
        bool Is(unsigned int type) const;
        void AddPatrolPoint(Vec2 patrolPoint);
        //void Walk(Vec2 destination);
        //void ChangeDirection(Direction dir);

    protected:

    private:
        CharacterStatus& characterStatus;

        int nextPointIndex;
        TileMap<TileInfo>* tileMap;
        vector<Vec2> patrolPoints;
};

#endif // ENEMY_H
