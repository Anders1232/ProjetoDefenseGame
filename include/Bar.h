#ifndef BAR_H
#define BAR_H

#include "Sprite.h"
#include "Camera.h"
#include "Timer.h"

#include "resources_path.h"

class Bar: public Component
{
public:
    Bar(int points, string frameFile, string fluidFile, GameObject& associated);
    ~Bar(){};
    bool Is(ComponentType comp) const;
    void EarlyUpdate(float dt);
    void Update(float dt);
    void LateUpdate(float dt);
    void Render();
    void SetX(float x);
    void SetY(float y);

    int GetX();
    int GetY();

    void SetPoints(int points);
    int GetPoints();
    float GetPercentPoints();
    bool IsFull();
    void SetRefilAuto(float time = 1);
    void SetPosition(float x, float y);
    void Reposition();
    //void Open(GameObject* alvo, int vidaMaxima);
//    bool IsDead();
//    void SetVida(int vidaNova);
//    int GetVida();
//    float GetPorcentagemVida();
//    bool IsFull();

protected:

private:
    GameObject& associated;
    Rect box;
    //Sprite fluid;
    //Sprite frame;
    Sprite& fluid;
    Sprite& frame;

    int maxPoints;
    float currPoints;
    bool refilAuto;
    float refilPace;
    Timer timer;
    int xRelative;
    int yRelative;
};

#endif // BAR_H
