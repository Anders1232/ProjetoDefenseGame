#ifndef ROBO_H
#define ROBO_H

#include <iostream>
#include <string>

#include "Camera.h"
#include "Component.h"
#include "resources_path.h"
#include "Bar.h"
#include "Walkable.h"

using std::string;

#define ROBO_SHEET_LINES        4
#define ROBO_SHEET_FRAMES       4
#define ROBO_SHEET_FRAME_TIME   4.0*1.0/24.0

class Robo: public Component{//public GameObject{
public:
    Robo(GameObject& associated, float x, float y, string file);
    ~Robo();
    void Update(float dt);
    void Render();
    bool Is(ComponentType type) const;

    void EarlyUpdate(float dt);
	void LateUpdate(float dt);

protected:
private:
    GameObject& associated;
    bool selected;
};

#endif // ROBO_H
