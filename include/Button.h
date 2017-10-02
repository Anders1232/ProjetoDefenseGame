#ifndef BUTTON_H
#define BUTTON_H

#include "Component.h"
#include "GameObject.h"
#include "Sprite.h"
#include <string>

class Button: public Component
{
    public:
        Button(GameObject& associated, string path);
        ~Button();
        void Render(){};
        void Update(float dt){};
        void EarlyUpdate(float dt){};
		void LateUpdate(float dt){};
		bool Is(ComponentType type) const;


    protected:

    private:
        Sprite* sp;
};

#endif // BUTTON_H
