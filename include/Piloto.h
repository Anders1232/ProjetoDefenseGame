#ifndef PILOTO_H
#define PILOTO_H

#include <string>
#include <vector>

#include "Component.h"
#include "State.h"
#include "Sprite.h"
#include "PlayerUnityMenu.h"
#include "PlayerUnityPath.h"
#include "InputManager.h"
#include "GameObject.h"

using std::string;
using std::string;

#define PILOTO_SHEET_LINES        4
#define PILOTO_SHEET_FRAMES       4
#define PILOTO_SHEET_FRAME_TIME   4.0*1.0/24.0


class Piloto: public Component
{
    public:
        Piloto(GameObject& associated);
        virtual ~Piloto();
        bool Is(ComponentType comp) const;
        void EarlyUpdate(float dt);
        void Update(float dt);
        void LateUpdate(float dt);
        void Render();
        void OnClick();
        Vec2& Destination();
        void SetPosition(int x, int y);
        void ShowOnScreen();
        void BoardPilot(void*);

    protected:

    private:
        vector<int> buttons;
};

#endif // PILOTO_H
