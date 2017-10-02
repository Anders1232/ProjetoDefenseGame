#include "../include/Bar.h"

//#define DEBUG
#ifdef DEBUG
    #define DEBUG_PRINT(x) do{ cout << x <<  endl; }while(0)
#else
    #define DEBUG_PRINT(x)
#endif // DEBUG

Bar::Bar(int points, string frameFile, string fluidFile, GameObject &associated):
    associated(associated),
    fluid(*(new Sprite(associated, fluidFile) ) ),
    frame(*(new Sprite(associated, frameFile) ) ),
    maxPoints(points),
    currPoints(points),
    refilAuto(false)
{
    DEBUG_PRINT("Bar::Bar()-inicio");
    xRelative = this->associated.box.x;
    yRelative = this->associated.box.y;

    //fluid.SetPosition(box.x, box.y);
    //frame.SetPosition(box.x, box.y);

    associated.AddComponent(&fluid);
    associated.AddComponent(&frame);

    box.w = frame.GetWidth();
    box.h = frame.GetHeight();
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
    //fluid.Render();
    //frame.Render();
}

void Bar::SetX(float x){
    box.x = x;
    //frame.SetPosition(box.x, box.y);
    //fluid.SetPosition(box.x, box.y);
}

void Bar::SetY(float y){
    box.y = y + associated.box.y;
    //frame.SetPosition(box.x, box.y);
    //fluid.SetPosition(box.x, box.y);
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

#ifdef DEBUG
    #undef DEBUG
#endif

