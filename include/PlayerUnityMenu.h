#ifndef PLAYER_UNITY_MENU_H
#define PLAYER_UNITY_MENU_H

#include <vector>
#include <string>

#include "Component.h"
#include "Sound.h"

#include "resources_path.h"
class GameObject;
class PlayerUnityPath;

class PlayerUnityMenu: public Component
{
    public:
        PlayerUnityMenu(GameObject& associated);
        virtual ~PlayerUnityMenu();
        void EarlyUpdate(float dt);
        void Update(float dt);
        void LateUpdate(float dt);
        void Render() const;
        bool Is(unsigned int type) const;
        void OnClick();
        void Toogle();
        void Reposition();
        GameObject* GetButton(unsigned int i);
        int GetButtons();
        //O menu adiciona botões de acordo com interesses de outras classes
        //no caso, para andar, robopath adiciona o botão Andar.
        int AddButton(std::string buttonSpritePath, std::string name, Component* observer);
        void ButtonObserver(Component* btn);

        static void OnPathFinished(PlayerUnityPath* eventSource, int& unused, void* context);

    protected:

    private:
        Sound buttonClick;
        bool active;
        std::vector<GameObject*> buttons;
};

#endif // PLAYER_UNITY_MENU_H
