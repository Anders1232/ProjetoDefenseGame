#ifndef CHARACTERSTATUS_H
#define CHARACTERSTATUS_H

#include <vector>
#include "Component.h"
#include "GameObject.h"
#include "Sprite.h"
#include "TileMap.h"

#include "TileInfo.h"
using std::vector;

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
        ATTAKCING
    };

    public:
        CharacterStatus(GameObject& associated,
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
        void Walk(Vec2 destination);
        void ChangeDirection(Direction dir);
        void debug();
        vector<Vec2> CellsInRange();

    protected:

    private:
        TileMap<TileInfo>* tileMap;
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
        State state;
        Direction direction;

};

#endif // CHARACTERSTATUS_H
