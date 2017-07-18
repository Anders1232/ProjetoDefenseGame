#ifndef ALLY_H
#define ALLY_H

#include <queue>
#include <vector>
#include <list>

#include "GameObject.h"
#include "StillAnimation.h"
#include "Bar.h"
#include "TileMap.h"
#include "Timer.h"
#include "Character.h"
#include "Enemy.h"
#include "Bullet.h"
#include "BarraCooldown.h"
#include "InputManager.h"

#include "resources_path.h"

using std::vector;
using std::list;
using std::queue;
using std::stringstream;


class Ally:public Character{
public:

    //Ally();
    ~Ally(){};
    void Update(float dt);
    virtual void Render() = 0;

    void StateMachine(float dt);
    void Input(float dt);
    bool IsDead();
    void NotifyCollision(GameObject& other);
    bool Is(string type);


    bool AreaRespiro();
    bool AreaMapa();

    void SetStatus(int vidaMaxima, float ataque, int renge, float defesa, int speed, int distance, int coolDown);
    virtual void Danificar(float dano){};
    void Defender();
    void Andar(int tileNumber = 1);
    void Parar();
    void Abrir_Menu();
    void Fechar_Menu();
    void Usar_Item();
    void Alocar_Item();
    void Especial();
    void Atacar();
    virtual bool Ejetar() = 0;
    virtual bool Embarcar(Ally* alvo) = 0;
    void MakePath(int tileNumber = 1);
    void OrientarSprite();
    bool IsLider();
    bool ValidPath(int tileNumber = 1);
    int GetVida();
    string GetNome();

    float GetPorcentagemVida();
    CharacterPosition GetAllyPosition();
    Ally* EncontrarRobo();
    bool VidaCheia();
    void Curar(int cura);
    bool IsLeader();

protected:
    bool lider;
    CharacterPosition allyPosition;
    vector<StillAnimation> buttonArray;

    Ally* alvoEspecial;
    //alcance de ataque
    bool menuAberto;
    Timer atackTimer;
    Timer inputTimer;
    Timer especialTime;


    /**
        STATUS
    **/
    //herança de Character
    //int speed;//velocidade de movimentação no mapa
    //float ataque;//poder de ataque
    //float defesa;//poder de defesa
    //int range;//alcance de ataque
    //BarraVida vida;
    //BarraCooldown barraCooldown;
    //int distance;//quantas células do grid pode andar
    //alcance de ataque
private:
};

#endif // ALLY_H
