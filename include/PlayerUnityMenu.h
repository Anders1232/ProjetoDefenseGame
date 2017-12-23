#ifndef PLAYER_UNITY_MENU_H
#define PLAYER_UNITY_MENU_H

#include <vector>

#include "Component.h"
#include "RectTransform.h"
#include "Button.h"
#include "Sprite.h"
#include "State.h"

#include "resources_path.h"

using std::vector;
class PlayerUnityMenu: public Component
{
    public:
        PlayerUnityMenu(GameObject& associated, State* stage);
        virtual ~PlayerUnityMenu();
        void EarlyUpdate(float dt);
        void Update(float dt);
        void LateUpdate(float dt);
        void Render() const;
        bool Is(ComponentType type) const;
        void OnClick();
        void Toogle();
        void Reposition();
        int AddButton(string buttonSpritePath, Component* observer);
        void ButtonObserver(Component* btn);

    protected:

    private:
        State* stage;
        vector<GameObject*> buttons;
};

#endif // PLAYER_UNITY_MENU_H
