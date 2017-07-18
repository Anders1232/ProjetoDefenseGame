#include "../include/Bar.h"

#define DEBUG
#ifdef DEBUG
    #define DEBUG_PRINT(x) do{ cout << x <<  endl; }while(0)
#else
    #define DEBUG_PRINT(x)
#endif // DEBUG

Bar::Bar(int points, GameObject &associated): fluid(BARRA_VIDA), frame(BARRA_VIDA_MOLDURA)
{
    DEBUG_PRINT("Bar::Bar()-inicio");
    box.x = associated.box.x;
    box.y = associated.box.y;
    maxPoints = currPoints = points;
    box.w = frame.GetWidth();
    box.h = frame.GetHeight();
    refilAuto = false;
    DEBUG_PRINT("Bar::Bar()-fim");
}

bool Bar::Is(ComponentType comp) const{
    return (ComponentType::BAR == comp);
}

void Bar::EarlyUpdate(float dt){
}

void Bar::Update(float dt)
{
    //Nessas buscas que a barra de vida faz, dá erro quando o personagem morre!!
    float porCento = 100*currPoints/maxPoints;
    if(porCento > 100) porCento = 100;
    fluid.SetClip(0, 0, box.w*porCento/100, box.h);
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
    fluid.Render(box.x - Camera::pos.x, box.y - Camera::pos.y);
    frame.Render(box.x - Camera::pos.x, box.y - Camera::pos.y);
}

void Bar::SetX(float x){
    box.SetRectCenterX(x);
}

void Bar::SetY(float y){
    box.SetRectCenterY(y);
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
    if(currPoints/maxPoints == 1){
        return true;
    }
    return false;
}

void Bar::SetRefilAuto(bool refilAuto){
    this->refilAuto = refilAuto;
}

void Bar::SetRefilPace(int refilPace){
    this->refilPace = refilPace;
}

#ifdef DEBUG
    #undef DEBUG
#endif

