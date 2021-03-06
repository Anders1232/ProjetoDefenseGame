//colocar vetor dos personagens
#ifndef STAGESTATE_H
#define STAGESTATE_H

#include <sstream>

#include "Game.h"
#include "State.h"
#include "Sprite.h"
#include "Music.h"
#include "Text.h"
#include "Robo.h"
#include "resources_path.h"
#include "TileMap.h"

#define STAGE_BACKGROUND_FILE   "resources/img/bg/ocean.jpg"

#define STAGE_TILESET_FILE      "resources/img/tileset/tileset.jpg"
#define STAGE_TILE_WIDTH          64
#define STAGE_TILE_HEIGHT         64

#define STAGE_TILEMAP_FILE           "resources/maps/tileMap20x20.txt"
#define STAGE_BACKGROUND_MUSIC_FILE  "resources/audio/Tema_Boss_01.wav"

#define CAMERA_SPEED    1


using std::find;
using std::stringstream;

class StageState : public State
{
    public:
        //StageState(CharacterData characters);
        StageState();
        //void InicializaPersonagens(CharacterData characters, InfoMenu *infoMenu);
        ~StageState();
        void Update(float dt);
        void Render() const;
        void Pause();
        void Resume();
        void LoadAssets() const;

        void SetOnGrid(GameObject& gameObject, int x, int y);

    protected:
    private:
        void Input(float dt);
        //Sprite bg;
        Music backGroundMusic;
        Timer vitoriaTime;
        TileMap* tilemap;//verificar o que significa a warning reorder
        GameObject ambient;
        GameObject robo;
};

#endif // STAGESTATE_H
