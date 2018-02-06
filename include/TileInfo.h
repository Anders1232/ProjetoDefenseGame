#ifndef TILEINFO_H
#define TILEINFO_H

#include "GameObject.h"
#include "BaseTile.h"

class TileInfo : public BaseTile
{
    public:
        TileInfo(int index);
        virtual ~TileInfo();
        void PutCharacter(GameObject* object);
        void RemoveCharacter();
        GameObject* GetCharacter();
    protected:

    private:
        bool passable;
        GameObject* characterInside;
};

#endif // TILEINFO_H
