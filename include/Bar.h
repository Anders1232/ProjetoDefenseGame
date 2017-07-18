#ifndef BAR_H
#define BAR_H
#include "StillAnimation.h"
#include "resources_path.h"
#include "Camera.h"

class Bar: public Component
{
public:
    Bar(int points, GameObject& associated);
    ~Bar(){};
    bool Is(ComponentType comp) const;
    void EarlyUpdate(float dt);
    void Update(float dt);
    void LateUpdate(float dt);
    void Render();
    void SetX(float x);
    void SetY(float y);
    void SetPoints(int points);
    int GetPoints();
    float GetPercentPoints();
    bool IsFull();
    void SetRefilAuto(bool refilAuto);
    void SetRefilPace(int refilPace);
    //void Open(GameObject* alvo, int vidaMaxima);
//    bool IsDead();
//    void SetVida(int vidaNova);
//    int GetVida();
//    float GetPorcentagemVida();
//    bool IsFull();

protected:

private:
    Rect box;
    Sprite fluid;
    Sprite frame;
    int maxPoints;
    int currPoints;
    bool refilAuto;
    int refilPace;
};

#endif // BAR_H
