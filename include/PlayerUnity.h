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

class PlayerUnity: public Component{

public:
    PlayerUnity(GameObject& associated, Vec2 position, TileMap<TileInfo>* tileMap);
    ~PlayerUnity();
    void Update(float dt);
    void Render() const;
    bool Is(uint type) const;
    void onClick();
    void SetPosition(float x, float y);

    void EarlyUpdate(float dt);
	void LateUpdate(float dt);
	void MenuOpen();
	void MenuClose();
	Vec2& Destination();
	GameObject* GetMenu();

protected:

private:
    CharacterStatus& characterStatus;
    GameObject& barraVida;
    GameObject& barraCoolDown;
    GameObject* piloto;
    GameObject* movingPath;
    GameObject* playerUnityMenu;
    bool clicked;
    bool selected;
    Vec2 destination;
    TileMap<TileInfo>* tileMap;
};

#endif // PLAYER_UNITY_H
