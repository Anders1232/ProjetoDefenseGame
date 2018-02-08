#ifndef ROBO_H
#define ROBO_H

#include <string>
#include <vector>

#include "Component.h"
#include "GameObject.h"
#include "Sprite.h"
#include "TileMap.h"
#include "PlayerUnity.h"
#include "PlayerUnityMenu.h"
#include "BaseTile.h"

using std::vector;
using std::string;

class Robo : public Component
{
    public:
        Robo(GameObject& associated, string file, Vec2 position, TileMap<TileInfo>* tileMap);
        virtual ~Robo();
        void EarlyUpdate(float dt);
        void LateUpdate(float dt);
        void Update(float dt);
        void Render() const;
        bool Is(unsigned int) const;
        void EjectPilot(void*);
        void BoardPilot(GameObject* piloto);
        void ButtonObserver(Component* btn);

    protected:

    private:
        Sprite* sp;
        TileMap<TileInfo>* tileMap;
        vector<GameObject*> pilotos;
        vector<int> buttons;
};

#endif // ROBO_H
