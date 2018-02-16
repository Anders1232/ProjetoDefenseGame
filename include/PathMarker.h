#ifndef PATHMARKER_H
#define PATHMARKER_H

#include <string>

#include "Component.h"

class GameObject;

class PathMarker : public Component
{
    public:
        PathMarker(GameObject& associated, std::string spritePath);
        virtual ~PathMarker();
        void EarlyUpdate(float dt);
        void Update(float dt);
        void LateUpdate(float dt);
        void Render();
        bool Is(unsigned int type) const;
    protected:

    private:
};

#endif // PATHMARKER_H
