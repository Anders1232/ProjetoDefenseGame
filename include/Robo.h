#ifndef ROBO_H
#define ROBO_H

#include <string>
#include <vector>

#include "Component.h"
#include "TileMap.h"
#include "TileInfo.h"

#include "PlayerUnity.h"
class GameObject;
class Sprite;

class Robo : public PlayerUnity
{
    public:
        Robo(GameObject& associated, std::string file, Vec2 position, TileMap<TileInfo>* tileMap);
        virtual ~Robo();
        void EarlyUpdate(float dt);
        void LateUpdate(float dt);
        void Update(float dt);
        void Render() const;
        bool Is(unsigned int) const;
        void EjectPilot(void*);
        void BoardPilot(GameObject* piloto);
        void ButtonObserver(Component* btn);
        void Attack();

    protected:

    private:
        Sprite* sp;
        std::vector<GameObject*> pilotos;
        std::vector<int> buttons;
};

#endif // ROBO_H
