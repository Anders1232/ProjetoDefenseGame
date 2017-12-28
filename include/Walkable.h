#ifndef WALKABLE_H
#define WALKABLE_H

#include <iostream>
#include <vector>

#include "GameObject.h"
#include "InputManager.h"
#include "Vec2.h"
#include "GameComponentType.h"

using std::cout;
using std::endl;
using std::vector;

class Walkable: public Component
{
    public:
        Walkable(GameObject& associated);
        ~Walkable();
        void Update(float dt);
		bool Is(GameComponentType type) const;
		void Render(){};
		void EarlyUpdate(float dt);
		void LateUpdate(float dt);
		void SetControlable(bool control);

		int PixelToGrid(int x, int tileW);
        void AddPath(int x, int y);

    protected:

    private:
        GameObject& associated;
        bool controlable;
        bool selected;
        Vec2 destination;
        vector<Vec2*> pathPoints;
        bool hasToWalk;
};

#endif // WALKABLE_H
