#ifndef PATHMARKER_H
#define PATHMARKER_H

#include <string>

#include "Component.h"
#include "GameObject.h"
#include "Sprite.h"

using std::string;

class PathMarker : public Component
{
    public:
        PathMarker(GameObject& associated, string spritePath);
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
