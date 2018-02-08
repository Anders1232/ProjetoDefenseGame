#ifndef CHARACTERSTATUS_H
#define CHARACTERSTATUS_H

#include "Component.h"
#include "GameObject.h"
#include "Sprite.h"


class CharacterStatus : public Component
{
    enum Direction{
        UP = 0,
        DOWN,
        LEFT,
        RIGHT
    };
    enum State{
        IDLE = 0,
        MOVING,
    };

    public:
        CharacterStatus(GameObject& associated,
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
        void Walk(Vec2 destination);
        void ChangeDirection(Direction dir);
        void debug();

    protected:

    private:
        float hp;
        float mp;

        float speed;
        int range;
        float attack;
        float defense;
        float magic;
        float resistence;
        State state;
        Direction direction;

};

#endif // CHARACTERSTATUS_H
