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

using std::string;
using std::vector;

#define ROBO_SHEET_LINES        4
#define ROBO_SHEET_FRAMES       4
#define ROBO_SHEET_FRAME_TIME   4.0*1.0/24.0
void Eject (void*);
class Robo: public Component{
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
    Robo(GameObject& associated, State* stage, float x, float y, string file);
    ~Robo();
    void Update(float dt);
    void Render();
    bool Is(ComponentType type) const;
    void onClick();
    void TryMove();
    void SetPosition(float x, float y);

    void EarlyUpdate(float dt);
	void LateUpdate(float dt);
	void Move(Direction dir);
	void MenuOpen();
	void MenuClose();

	void debug();

protected:

private:
    void UpdateState();
    GameObject& associated;
    GameObject& barraVida;
    GameObject& barraCoolDown;
    GameObject* button;
    State* stage;
    Sprite* sp;
    bool clicked;
    bool selected;
    RoboState roboState;
    Direction direction;
    Vec2 destination;
    vector<Vec2*> *movingPath;
};

#endif // ROBO_H
