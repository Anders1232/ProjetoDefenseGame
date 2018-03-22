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
        void ReserveTo(GameObject* object);
        void RemoveCharacter();
        GameObject* GetCharacter();
        bool IsFree(GameObject& obj);
        bool IsPassable();
        void ReserveTo(GameObject& obj);
    protected:

    private:
        bool passable;
        bool isFree;
        GameObject* characterInside;
        GameObject* reservedTo;

};

#endif // TILEINFO_H
