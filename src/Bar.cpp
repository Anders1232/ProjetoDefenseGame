#include "../include/Bar.h"

//#define DEBUG
#include "Error.h"
Bar::Bar(GameObject &associated, int points, string frameFile, string fluidFile):
    Component(associated),
    fluid(*(new Sprite(associated, fluidFile, true) ) ),
    frame(*(new Sprite(associated, frameFile, true) ) ),
    maxPoints(points),
    currPoints(points),
    refilAuto(false),
    relative(0,0)
{
    DEBUG_CONSTRUCTOR("Bar", "inicio");
    //associated.AddComponent(new RectTransform(associated, nullptr));
    /*
        Inicialmente, a box de Bar tem o tamanho do sprite da moldura
    */
    associated.box.w = frame.GetWidth();
    associated.box.h = frame.GetHeight();

    associated.AddComponent(&fluid);
    associated.AddComponent(&frame);

    DEBUG_CONSTRUCTOR("Bar", "fim");
}

bool Bar::Is(ComponentType comp) const{
    return (ComponentType::BAR == comp);
}

void Bar::EarlyUpdate(float dt){
}

void Bar::Update(float dt)
{
    DEBUG_UPDATE("Bar", "inicio");
    if(refilAuto){
        DEBUG_UPDATE("Bar", "currPoints: " << currPoints);
        DEBUG_UPDATE("Bar", "maxPoints: " << maxPoints);
        if(currPoints < maxPoints){
            currPoints += refilPace*dt;
            if(currPoints > maxPoints) currPoints = maxPoints;
            fluid.SetScreenRect(0, 0, associated.box.w * (currPoints/maxPoints), associated.box.h); //SetClip(0, 0, associated.box.w * (currPoints/maxPoints), associated.box.h);
        }
    }
    associated.box.x = associated.parent->box.x + relative.x;
    associated.box.y = associated.parent->box.y + relative.y;
    DEBUG_UPDATE("Bar", "fim");
}

void Bar::LateUpdate(float dt){
}

/*
bool Bar::IsDead()
{
    if(currPoints <= 0) return true;
    return false;
}
*/

void Bar::Render()
{
}

void Bar::SetX(float x){
    associated.box.x = x + associated.parent->box.x;
}

void Bar::SetY(float y){
    associated.box.y = y + associated.parent->box.y;
}

void Bar::SetPoints(int points)
{
    if(points > maxPoints){
        currPoints = maxPoints;
    }else{
        currPoints = points;
    }
}

int Bar::GetPoints()
{
    return currPoints;
}

float Bar::GetPercentPoints()
{
    return 100*currPoints/maxPoints;
}

bool Bar::IsFull(){
    if(currPoints == maxPoints){
        return true;
    }
    return false;
}

void Bar::SetRefilAuto(float time){
    this->refilAuto = true;
    this->refilPace = maxPoints/time;
}

void Bar::Centralize(int x, int y){
    relative.x = associated.parent->box.w/2 - associated.box.w/2 + x;
    relative.y = associated.parent->box.h/2 - associated.box.h/2 + y;
    associated.box.x = associated.parent->box.x + relative.x;
    associated.box.y = associated.parent->box.y + relative.y;
}

void Bar::SetPosition(float x, float y){
    associated.box.x = associated.box.x + associated.parent->box.x;
    associated.box.y = associated.box.y + associated.parent->box.y;
}

int Bar::GetX(){
    return associated.box.x;
}

int Bar::GetY(){
    return associated.box.y;
}

#include "Error_footer.h"
