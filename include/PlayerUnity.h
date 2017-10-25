#ifndef ROBO_H
#define ROBO_H

#include <iostream>
#include <string>
#include <vector>

#include "Camera.h"
#include "Component.h"
#include "resources_path.h"
#include "Bar.h"
#include "Button.h"
#include "GameObject.h"
#include "State.h"
#include "RectTransform.h"
#include "PlayerUnityPath.h"
#include "PlayerUnityMenu.h"
#include "Piloto.h"

using std::string;
using std::vector;

#define ROBO_SHEET_LINES        4
#define ROBO_SHEET_FRAMES       4
#define ROBO_SHEET_FRAME_TIME   4.0*1.0/24.0

class PlayerUnity: public Component{
private:
    enum Direction{
        UP = 0,
        DOWN,
        LEFT,
        RIGHT
    };
    enum RoboState{
        IDLE = 0,
        MOVING,
    };

public:
    PlayerUnity(GameObject& associated, State* stage, float x, float y, string file);
    ~PlayerUnity();
    void Update(float dt);
    void Render();
    bool Is(ComponentType type) const;
    void onClick();
    void TryMove();
    void SetPosition(float x, float y);

    void EarlyUpdate(float dt);
	void LateUpdate(float dt);
	void ChangeDirection(Direction dir);
	void MenuOpen();
	void MenuClose();
	Vec2& Destination();

	void debug();

protected:

private:
    void UpdateState();
    GameObject& barraVida;
    GameObject& barraCoolDown;
    GameObject* piloto;
    GameObject* movingPath;
    GameObject* roboMenu;
    State* stage;
    Sprite* sp;
    bool clicked;
    bool selected;
    RoboState roboState;
    Direction direction;
    Vec2 destination;
};

#endif // ROBO_H
