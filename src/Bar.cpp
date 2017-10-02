#include "../include/Bar.h"

//#define DEBUG
#include "Error.h"
Bar::Bar(GameObject &associated, int points, string frameFile, string fluidFile):
    Component(associated),
    associated(associated),
    fluid(*(new Sprite(associated, fluidFile) ) ),
    frame(*(new Sprite(associated, frameFile) ) ),
    maxPoints(points),
    currPoints(points),
    refilAuto(false)
{
    DEBUG_PRINT("Bar::Bar()-inicio");
    associated.AddComponent(new RectTransform(associated, nullptr));
    /*
        Inicialmente, a box de Bar tem o tamanho do sprite da moldura
    */
    box.w = frame.GetWidth();
    box.h = frame.GetHeight();
    Centralize(0, associated.box.h);

    associated.AddComponent(&fluid);
    associated.AddComponent(&frame);

    DEBUG_PRINT("Bar::Bar()-fim");
}

bool Bar::Is(ComponentType comp) const{
    return (ComponentType::BAR == comp);
}

void Bar::EarlyUpdate(float dt){
}

void Bar::Update(float dt)
{
    Reposition();
    if(refilAuto){
        if(currPoints < maxPoints){
            currPoints += refilPace*dt;
            if(currPoints > maxPoints) currPoints = maxPoints;
            fluid.SetClip(0, 0, box.w * (currPoints/maxPoints), box.h);
        }
    }
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
    box.x = x;
}

void Bar::SetY(float y){
    box.y = y + associated.box.y;
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
    float centerX = associated.box.x + associated.box.w/2;
    float centerY = associated.box.y + associated.box.h/2;

    xRelative = centerX - box.w/2 + x;
    yRelative = centerY - box.h/2 + y;

    frame.SetPosition(xRelative, yRelative);
    fluid.SetPosition(xRelative, yRelative);

}

void Bar::SetPosition(float x, float y){
    xRelative = x;
    yRelative = y;
    box.x = xRelative + associated.box.x;
    box.y = yRelative + associated.box.y;
//    frame.SetPosition(box.x, box.y);
//    fluid.SetPosition(box.x, box.y);
}

void Bar::Reposition(){
    box.x = xRelative + associated.box.x;
    box.y = yRelative + associated.box.y;
//    frame.SetPosition(box.x, box.y);
//    fluid.SetPosition(box.x, box.y);
}

int Bar::GetX(){
    return box.x;
}

int Bar::GetY(){
    return box.y;
}

#include "Error_footer.h"
