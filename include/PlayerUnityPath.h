#ifndef ROBOPATH_H
#define ROBOPATH_H

#include <vector>

#include "Component.h"
#include "Vec2.h"
#include "Sprite.h"
#include "resources_path.h"
#include "PlayerUnity.h"
using std::vector;

class RoboPath: public Component
{
    public:
        RoboPath(GameObject& associated, Vec2& destination);
        virtual ~RoboPath();
        void EarlyUpdate(float dt){};
        void Update(float dt);
        void LateUpdate(float dt){};
        void Render() const {};
        bool Is(ComponentType type)const;


        void CreatePath();
        Vec2 GetNext();
        bool HasPoints();
        void OnClick();


    protected:

    private:
        Vec2& destination;
        bool parentSelected;
        vector<Vec2*> movingPath;
        vector<Sprite*> pathMarkers;
};

#endif // ROBOPATH_H
