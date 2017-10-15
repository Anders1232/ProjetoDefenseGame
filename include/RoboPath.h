#ifndef ROBOPATH_H
#define ROBOPATH_H

#include <vector>

#include "Component.h"
#include "Vec2.h"
#include "Sprite.h"
#include "resources_path.h"

using std::vector;

class RoboPath: public Component
{
    public:
        RoboPath(GameObject& associated, Vec2 first);
        virtual ~RoboPath();
        void EarlyUpdate(float dt){}
        void Update(float dt);
        void LateUpdate(float dt){}
        void Render(){}
        bool Is(ComponentType type)const;


        void CreatePath();
        Vec2 GetNext();
        bool HasPoints();


    protected:

    private:
        vector<Vec2*> movingPath;
        vector<Sprite*> pathMarkers;
};

#endif // ROBOPATH_H
