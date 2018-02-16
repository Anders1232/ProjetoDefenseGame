#ifndef TILEINFO_H
#define TILEINFO_H

#include "BaseTile.h"

class GameObject;
class TileInfo : public BaseTile
{
    public:
        TileInfo(int index);
        virtual ~TileInfo();
        void PutCharacter(GameObject& object);
        void RemoveCharacter();
        GameObject* GetCharacter();
        bool IsFree();
        bool IsPassable();
    protected:

    private:
        bool passable;
        bool isFree;
        GameObject* characterInside;
};

#endif // TILEINFO_H
