#ifndef ROBO_H
#define ROBO_H

#include <iostream>
#include <string>

#include "Ally.h"
#include "Piloto.h"
#include "Camera.h"

using std::string;

#define ROBO_SHEET_LINES        4
#define ROBO_SHEET_FRAMES       4
#define ROBO_SHEET_FRAME_TIME   4.0*1.0/24.0

class Robo: public Ally{
public:
    Robo(float x, float y, TileMap* mapRef, bool lider, string nome);
    ~Robo();
    void Render();
    bool Is(string type);
    bool Ejetar();
    void Update(float dt);
    bool Embarcar(Ally* alvo);
    void InserePiloto(Piloto* piloto);
    void Morrer();
    void Danificar(float dano);

protected:
    /*vazio*/
private:
    std::vector<Piloto*> pilotoArray;
};

#endif // ROBO_H
