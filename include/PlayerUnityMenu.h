#ifndef PLAYER_UNITY_MENU_H
#define PLAYER_UNITY_MENU_H

#include <vector>

#include "Component.h"
#include "RectTransform.h"
#include "Button.h"
#include "Sprite.h"
#include "State.h"

#include "PlayerUnityPath.h"

#include "resources_path.h"

class RoboPath;
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
        bool Is(uint type) const;
        void OnClick();
        void Toogle();
        void Reposition();
        GameObject* GetButton(int i);
        int GetButtons();
        //O menu adiciona bot�es de acordo com interesses de outras classes
        //no caso, para andar, robopath adiciona o bot�o Andar.
        int AddButton(string buttonSpritePath, Component* observer);
        void ButtonObserver(Component* btn);

        //Se inscreve no evento de RoboPath, para quando o caminho for completado,
        //o menu abrir
        void SubscribeToPath(RoboPath& roboPath);
        static void OnPathFinished(RoboPath* eventSource, int& unused, void* context);

    protected:

    private:
        State* stage;
        vector<GameObject*> buttons;
};

#endif // PLAYER_UNITY_MENU_H
