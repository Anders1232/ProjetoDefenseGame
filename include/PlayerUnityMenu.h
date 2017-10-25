#ifndef ROBOMENU_H
#define ROBOMENU_H

#include <vector>

#include "Component.h"
#include "Sprite.h"
#include "resources_path.h"

using std::vector;
class RoboMenu: public Component
{
    public:
        RoboMenu(GameObject& associated);
        virtual ~RoboMenu();
        void EarlyUpdate(float dt);
        void Update(float dt);
        void LateUpdate(float dt);
        void Render();
        bool Is(ComponentType type) const;
        void OnClick();
        void Toogle();

    protected:

    private:
        vector<Sprite*> buttons;
};

#endif // ROBOMENU_H
