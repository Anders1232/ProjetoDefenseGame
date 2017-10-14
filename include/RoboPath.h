#ifndef ROBOPATH_H
#define ROBOPATH_H

#include <vector>

#include "Component.h"
#include "Vec2.h"
#include "Sprite.h"

using std::vector;

class RoboPath: public Component
{
    public:
        RoboPath(GameObject& associated, Vec2 first);
        virtual ~RoboPath();
        void EarlyUpdate(float dt){}
        void Update(float dt){}
        void LateUpdate(float dt){}
        void Render(){}
        bool Is(ComponentType type)const;


        void AddPoint();
        Vec2 GetNext();
        bool HasPoints();


    protected:

    private:
        GameObject& associated;
        vector<Vec2*> movingPath;
        vector<Sprite*> sprites;
};

#endif // ROBOPATH_H
