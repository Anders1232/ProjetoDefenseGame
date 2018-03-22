#ifndef ENEMY_H
#define ENEMY_H

#include <string>
#include <vector>

#include "Component.h"
#include "Vec2.h"
#include "Sound.h"

#include "TileMap.h"
#include "TileInfo.h"

#include "CharacterStatus.h"
/*
    Engine Classes
*/
class GameObject;
class Sprite;

/*
    Game Classes
*/
class CharacterStatus;

class Enemy : public CharacterStatus
{
private:
    public:
        Enemy(GameObject& associated, std::string spritePath, Vec2 position, TileMap<TileInfo>* tileMap);
        virtual ~Enemy();
        void EarlyUpdate(float dt);
        void Update(float dt);
        void LateUpdate(float dt);
        void Render();
        bool Is(unsigned int type) const;
        void AddPatrolPoint(Vec2 patrolPoint);
        void Attack(CharacterType other);
        void Walk() override;

    protected:
        Sound attackSound;

    private:
        unsigned int nextPointIndex;
        std::vector<Vec2> patrolPoints;
};

#endif // ENEMY_H
