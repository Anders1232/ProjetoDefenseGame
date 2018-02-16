#ifndef BAR_H
#define BAR_H

#include "Component.h" //Base
#include "Timer.h"
#include "Vec2.h"

#include "resources_path.h"

class Sprite; //reference only

class Bar: public Component
{
public:
    Bar(GameObject& associated, int points, std::string frameFile, std::string fluidFile);
    ~Bar(){};
    bool Is(unsigned int comp) const;
    void EarlyUpdate(float dt);
    void Update(float dt);
    void LateUpdate(float dt);
    void Render() const;
    void SetX(float x);
    void SetY(float y);

    int GetX();
    int GetY();

    void SetPoints(int points);
    int GetPoints();
    float GetPercentPoints();
    bool IsFull();
    void SetRefilAuto(float time = 1);
    void Centralize(int x = 0, int y = 0);
    void SetPosition(float x, float y);
    //void Open(GameObject* alvo, int vidaMaxima);
//    bool IsDead();
//    void SetVida(int vidaNova);
//    int GetVida();
//    float GetPorcentagemVida();
//    bool IsFull();

protected:

private:

    Sprite& fluid;
    Sprite& frame;

    int maxPoints;
    float currPoints;
    bool refilAuto;
    float refilPace;
    Timer timer;
    Vec2 relative;
};

#endif // BAR_H
