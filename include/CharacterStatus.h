#ifndef CHARACTERSTATUS_H
#define CHARACTERSTATUS_H

#include <vector>
#include <string>
#include "Component.h" //Base
#include "Vec2.h"

#include "TileMap.h"
#include "TileInfo.h"

class GameObject; //reference only

class CharacterStatus : public Component
{
    protected:
        enum Direction{
            UP = 0,
            DOWN,
            LEFT,
            RIGHT
        };
        enum CharacterState{
            IDLE = 0,
            WALKING,
            ATTAKCING,
            DEAD
        };

    public:
        CharacterStatus(GameObject& associated,
                        Vec2 position,
                        TileMap<TileInfo>* tileMap,
                        float hp = 10, float mp = 10,
                        float speed = 1, int range = 1,
                        float attack = 1, float defense = 0,
                        float magic = 1, float resistence = 0);
        virtual ~CharacterStatus();
        void EarlyUpdate(float dt);
        void Update(float dt);
        void LateUpdate(float dt);
        void Render();
        bool Is(unsigned int type) const;
        void Walk();
        void ChangeDirection(Direction dir);
        void debug();
        std::vector<Vec2> CellsInRange();
        std::vector<CharacterStatus*> CharactersInRange();

        void Attack(CharacterStatus* character);
        void ReceiveDamage(int damage);
        void Die();
        std::string is;


    protected:
        TileMap<TileInfo>* tileMap;
        Vec2* destination;
        Vec2* walkDirection;
        Vec2* lastGridPosition;
        std::vector<CharacterStatus*> charactersInRange;

        /*
            Status
        */
        float hp;
        float mp;

        float speed;
        int range;
        float attack;
        float defense;
        float magic;
        float resistence;
        CharacterState charState;
        Direction direction;
        bool pathVerifyed;
        void SetDestination(Vec2 destination);
        void StopWalking();
    private:
        float delta;
};

#endif // CHARACTERSTATUS_H
