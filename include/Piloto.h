#ifndef PILOTO_H
#define PILOTO_H

#include <string>
#include <vector>

#include "Component.h"
#include "State.h"
#include "Sprite.h"
#include "InputManager.h"
#include "GameObject.h"
#include "TileMap.h"
#include "TileInfo.h"

#include "PlayerUnity.h"
#include "PlayerUnityMenu.h"
#include "PlayerUnityPath.h"

using std::string;
using std::vector;

#define PILOTO_SHEET_LINES        4
#define PILOTO_SHEET_FRAMES       4
#define PILOTO_SHEET_FRAME_TIME   4.0*1.0/24.0


class Piloto: public Component
{
    public:
        Piloto(GameObject& associated, State* stage, string file, Vec2 position, TileMap<TileInfo>* tileMap);
        virtual ~Piloto();
        bool Is(unsigned int comp) const;
        void EarlyUpdate(float dt);
        void Update(float dt);
        void LateUpdate(float dt);
        void Render() const;
        void OnClick();
        Vec2& Destination();
        void SetPosition(int x, int y);
        void ShowOnScreen();
        void BoardPilot(void*);

    protected:

    private:
        Sprite* sp;
        TileMap<BaseTile>* tileMap;
        vector<int> buttons;
};

#endif // PILOTO_H
