#ifndef PLAYER_UNITY_MENU_H
#define PLAYER_UNITY_MENU_H

#include <vector>

#include "Component.h"

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
        //O menu adiciona bot�es de acordo com interesses de outras classes
        //no caso, para andar, robopath adiciona o bot�o Andar.
        int AddButton(std::string buttonSpritePath, Component* observer);
        void ButtonObserver(Component* btn);

        //Se inscreve no evento de RoboPath, para quando o caminho for completado,
        //o menu abrir
        void SubscribeToPath(PlayerUnityPath& roboPath);
        static void OnPathFinished(PlayerUnityPath* eventSource, int& unused, void* context);

    protected:

    private:
        bool active;
        std::vector<GameObject*> buttons;
};

#endif // PLAYER_UNITY_MENU_H
