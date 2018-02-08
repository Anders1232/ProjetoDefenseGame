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
#include "TileInfo.h"

#include "PlayerUnityPath.h"
#include "PlayerUnityMenu.h"
#include "Bar.h"
#include "CharacterStatus.h"
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
    PlayerUnity(GameObject& associated, Vec2 position, TileMap<TileInfo>* tileMap);
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
    Component& characterStatus;
    GameObject& barraVida;
    GameObject& barraCoolDown;
    GameObject* piloto;
    GameObject* movingPath;
    GameObject* playerUnityMenu;
    bool clicked;
    bool selected;
    PlayerUnityState playerUnityState;
    Direction direction;
    Vec2 destination;
    TileMap<TileInfo>* tileMap;
};

#endif // PLAYER_UNITY_H
