#ifndef CHARACTERSTATUS_H
#define CHARACTERSTATUS_H

#include <vector>
#include <string>
#include "Component.h" //Base
#include "Vec2.h"
#include "Sound.h"

#include "TileMap.h"
#include "TileInfo.h"
#include "Timer.h"

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
        enum CharacterType{
            PLAYER_UNITY,
            ENEMY
        };
        struct Status{
            /*
                Status
            */
            float hp;
            float mp;

            float speed;
            int range;
            float attack;
            float attackCoolDown;
            float defense;
            float magic;
            float resistence;
            float coolDown;
        };

    public:
        CharacterType charType;
        CharacterStatus(GameObject& associated,
                        Vec2 position,
                        TileMap<TileInfo>* tileMap);
        virtual ~CharacterStatus();
        void EarlyUpdate(float dt);
        void Update(float dt);
        void LateUpdate(float dt);
        void Render();
        bool Is(unsigned int type) const;
        virtual void Walk(float dt);
        void ChangeDirection(Direction dir);
        void debug();
        std::vector<Vec2> CellsInRange();
        std::vector<CharacterStatus*> CharactersInRange();

        virtual bool Attack(CharacterStatus* character);
        virtual void ReceiveDamage(int damage);
        virtual void Die();
        void SetStatus(float hp = 10, float mp = 10, float speed = 1, int range = 1,
                       float attack = 1, float defense = 0, float magic = 1, float resistence = 0,
                       float coolDown = 5, float attackCoolDown = 3);

    protected:
        TileMap<TileInfo>* tileMap;
        Vec2* destination;
        Vec2* walkDirection;
        Vec2* lastGridPosition;
        std::vector<CharacterStatus*> charactersInRange;

        Status status;
        Sound attackSound;
        Sound dieSound;
        Timer attackTimer;
        CharacterState charState;
        Direction direction;
        bool pathVerifyed;
        void SetDestination(Vec2 destination);
        void StopWalking();
    private:
        float delta;
};

#endif // CHARACTERSTATUS_H
