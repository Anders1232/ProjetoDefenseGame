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

        /*
        template<typename OBJ>
        int AddButton(string buttonSpritePath, OBJ* obj, void(OBJ::*buttonFunction)(void*)){

            GameObject* buttonObject = new GameObject();
            buttonObject->AddComponent(new RectTransform(*buttonObject, &associated));
            buttonObject->AddComponent(new Sprite(*buttonObject, buttonSpritePath, true));
            Button<OBJ>* buttonComponent = new Button<OBJ>(*buttonObject);
            typename Button<OBJ>::Callback callback;
            callback.obj = obj;
            callback.callbackFunc = buttonFunction;
            callback.caller = nullptr;
            buttonComponent->SetReleaseCallback(callback);

            buttonObject->AddComponent(buttonComponent);

            stage->AddObject(buttonObject);
            buttonObject->parent = &associated;
            buttonObject->showOnScreen = associated.showOnScreen;
            buttons.push_back(buttonObject);

            return buttons.size() - 1;
        }*/

    protected:

    private:
        State* stage;
        vector<GameObject*> buttons;
};

#endif // PLAYER_UNITY_MENU_H
