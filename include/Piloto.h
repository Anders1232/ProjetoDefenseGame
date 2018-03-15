#ifndef PILOTO_H
#define PILOTO_H

#include <string>
#include <vector>

#include "Component.h"
#include "Vec2.h"
#include "TileMap.h"
#include "TileInfo.h"

#include "PlayerUnity.h"

class GameObject;
class Piloto: public PlayerUnity
{
    public:
        Piloto(GameObject& associated, std::string file, Vec2 position, TileMap<TileInfo>* tileMap);
        virtual ~Piloto();
        bool Is(unsigned int comp) const;
        void EarlyUpdate(float dt);
        void Update(float dt);
        void LateUpdate(float dt);
        void Render() const;
        void OnClick();
        void ShowOnScreen();
        void BoardPilot(void*);

    protected:

    private:
        Sprite* sp;
        TileMap<BaseTile>* tileMap;
        std::vector<int> buttons;
};

#endif // PILOTO_H
