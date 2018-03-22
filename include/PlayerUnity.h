#ifndef PLAYER_UNITY_H
#define PLAYER_UNITY_H

#include <iostream>
#include <string>
#include <vector>

#include "Component.h"
#include "TileMap.h"
#include "TileInfo.h"
#include "CharacterStatus.h"

class GameObject;
class PlayerUnityPath;
class PlayerUnity: public CharacterStatus{

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
	void ButtonObserver(Component* btn);
	void ReceiveDamage(int damage) override;
	void Walk()override;
	void Attack(CharacterType other);

protected:

private:
    GameObject& barraVida;
    GameObject& barraCoolDown;
    GameObject* piloto;
    PlayerUnityPath* movingPath;
    GameObject* playerUnityMenu;
    bool clicked;
    bool selected;
    bool walkPressed;
    TileMap<TileInfo>* tileMap;
};

#endif // PLAYER_UNITY_H
