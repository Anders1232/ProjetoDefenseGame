//colocar vetor dos personagens
#ifndef STAGESTATE_H
#define STAGESTATE_H

#include <sstream>

#include "Game.h"
#include "State.h"
#include "RectTransform.h"
#include "Sprite.h"
#include "Music.h"
#include "Text.h"
#include "TileMap.h"
#include "Tileset.h"
#include "TileInfo.h"

#include "PlayerUnity.h"
#include "resources_path.h"
#include "Robo.h"
#include "Piloto.h"
#include "Cursor.h"
#include "Enemy.h"

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
        bool showDEBUG;
        void Input(float dt);
        Music backGroundMusic;
        Timer vitoriaTime;
        TileMap<TileInfo>* tileMap;
        //Text mousePosition;
        //TileMap* tilemap;//verificar o que significa a warning reorder
};

#endif // STAGESTATE_H
