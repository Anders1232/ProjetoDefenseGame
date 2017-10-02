#ifndef ROBO_H
#define ROBO_H

#include <iostream>
#include <string>
#include <vector>

#include "Camera.h"
#include "Component.h"
#include "resources_path.h"
#include "Bar.h"
#include "Button.h"
#include "GameObject.h"
#include "State.h"
#include "RectTransform.h"

using std::string;

#define ROBO_SHEET_LINES        4
#define ROBO_SHEET_FRAMES       4
#define ROBO_SHEET_FRAME_TIME   4.0*1.0/24.0

class Robo: public Component{
public:
    Robo(GameObject& associated, State* stage, float x, float y, string file);
    ~Robo();
    void Update(float dt);
    void Render();
    bool Is(ComponentType type) const;
    void onClick();

    void EarlyUpdate(float dt);
	void LateUpdate(float dt);

protected:
private:
    GameObject& associated;
    State* stage;
    Bar* barraVida;
    Bar* barraCoolDown;
    Sprite* sp;
    bool selected;
};

#endif // ROBO_H
