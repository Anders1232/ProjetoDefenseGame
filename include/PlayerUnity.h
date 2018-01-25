#ifndef PLAYER_UNITY_H
#define PLAYER_UNITY_H

#include <iostream>
#include <string>
#include <vector>

#include "GameObject.h"
#include "Component.h"
#include "State.h"
#include "Camera.h"
#include "Button.h"
#include "TileMap.h"
#include "BaseTile.h"

#include "PlayerUnityPath.h"
#include "PlayerUnityMenu.h"
#include "Bar.h"
#include "resources_path.h"


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
    enum PlayerUnityState{
        IDLE = 0,
        MOVING,
    };

public:
    PlayerUnity(GameObject& associated, State* stage, Vec2 position, TileMap<BaseTile>* tileMap);
    ~PlayerUnity();
    void Update(float dt);
    void Render() const;
    bool Is(uint type) const;
    void onClick();
    void TryMove();
    void SetPosition(float x, float y);

    void EarlyUpdate(float dt);
	void LateUpdate(float dt);
	void ChangeDirection(Direction dir);
	void MenuOpen();
	void MenuClose();
	Vec2& Destination();
	GameObject* GetMenu();

	void debug();

protected:

private:
    void UpdateState();
    GameObject& barraVida;
    GameObject& barraCoolDown;
    GameObject* piloto;
    GameObject* movingPath;
    GameObject* playerUnityMenu;
    State* stage;
    bool clicked;
    bool selected;
    PlayerUnityState playerUnityState;
    Direction direction;
    Vec2 destination;
    TileMap<BaseTile>* tileMap;
};

#endif // PLAYER_UNITY_H
