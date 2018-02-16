#ifndef CURSOR_H
#define CURSOR_H

#include <string>

#include "Component.h"
#include "GameObject.h"
#include "InputManager.h"
#include "Sprite.h"

class Cursor : public Component
{
    public:
        Cursor(GameObject& associated, std::string spriteFile);
        virtual ~Cursor();

        void EarlyUpdate(float dt);
        void Update(float dt);
        void LateUpdate(float dt);
        void Render();
        bool Is(unsigned int type) const;

    protected:

    private:
        GameObject* dragged;
};

#endif // CURSOR_H
