#ifndef ROBO_H
#define ROBO_H

#include <vector>

#include "Component.h"
#include "GameObject.h"
#include "Sprite.h"
#include "PlayerUnity.h"
#include "PlayerUnityMenu.h"

using std::vector;
class Robo : public Component
{
    public:
        Robo(GameObject& associated, State* stage);
        virtual ~Robo();
        void EarlyUpdate(float dt);
        void LateUpdate(float dt);
        void Update(float dt);
        void Render();
        bool Is(ComponentType) const;
        void EjectPilot(void*);
        void BoardPilot(GameObject* piloto);

    protected:

    private:
        vector<GameObject*> pilotos;
        vector<int> buttons;
};

#endif // ROBO_H
