#include "../include/StageState.h"

#include "Game.h"
#include "RectTransform.h"
#include "Sprite.h"
#include "Text.h"
#include "Tileset.h"
#include "PlayerUnity.h"
#include "resources_path.h"
#include "Robo.h"
#include "Piloto.h"
#include "Cursor.h"
#include "Enemy.h"

#include "Error.h"

using std::find;
using std::stringstream;
using std::to_string;

#define STAGE_BACKGROUND_FILE   "resources/img/bg/ocean.jpg"

#define STAGE_TILESET_FILE      "resources/maps/mapSprites.txt"
#define STAGE_TILE_WIDTH          64
#define STAGE_TILE_HEIGHT         64

#define STAGE_TILEMAP_FILE           "resources/maps/tileMap20x20.txt"
#define STAGE_BACKGROUND_MUSIC_FILE  "resources/audio/Tema_Boss_01.wav"

#define ENEMY_1     "resources/img/enemies/enemy1.png"
#define CAMERA_SPEED    1

StageState::StageState():
    showDEBUG(false),
    backGroundMusic(STAGE_BACKGROUND_MUSIC_FILE)
{
    DEBUG_CONSTRUCTOR("inicio");
    Camera::pos.x = 0;
    Camera::pos.y = 0;

    /*
        Constroi cenario
    */
    GameObject* backGround = new GameObject("BackGround", this);
    backGround->box.x = 0;
    backGround->box.y = 0;
    backGround->box.w = 1024;
    backGround->box.h = 600;
    backGround->AddComponent(new Sprite(*backGround, STAGE_BACKGROUND_FILE, true));
    AddObject(backGround);

    GameObject* tileMapObject = new GameObject("TileMap", this);
    tileMap = new TileMap<TileInfo>(*tileMapObject, STAGE_TILEMAP_FILE, new TileSet(STAGE_TILESET_FILE, *tileMapObject));
    tileMapObject->AddComponent(tileMap);
    AddObject(tileMapObject);

    /*
        Coloca a musica
    */
    backGroundMusic.Play(-1);

    /*
        Coloca os personagens
    */

    GameObject* robo = new GameObject("Robo", this);
    AddObject(robo);
    Robo* roboComponent = new Robo(*robo, ROBO_SP1, Vec2(3,3), tileMap);
    robo->AddComponent(roboComponent);


    GameObject* piloto = new GameObject("Piloto", this);
    piloto->showOnScreen = false;
    AddObject(piloto);
    piloto->AddComponent(new Piloto(*piloto, PILOTO_SP1, Vec2(3,4), tileMap));
    //roboComponent->BoardPilot(piloto);


    GameObject* enemy = new GameObject("Enemy", this);
    AddObject(enemy);
    Enemy* enemyComponent = new Enemy(*enemy, ENEMY_1, Vec2(10,3), tileMap);
    enemyComponent->AddPatrolPoint(Vec2(15,3));
    enemy->AddComponent(enemyComponent);


    GameObject* cursor = new GameObject("Cursor", this);
    cursor->AddComponent(new Cursor(*cursor, "resources/img/misc/cursor.png"));
    AddObject(cursor);


    DEBUG_CONSTRUCTOR("CameraPos: " << Camera::pos.x << ", " << Camera::pos.y);
    DEBUG_CONSTRUCTOR("fim");
}

StageState::~StageState()
{
    backGroundMusic.Stop();
    objectArray.clear();
}

void StageState::Update(float dt)
{
    DEBUG_UPDATE("inicio");
    Input(dt);
    State::Update(dt);

    Camera::Update(Game::GetInstance().GetDeltaTime());
    DEBUG_UPDATE("fim");
}

void StageState::Render() const
{
    DEBUG_RENDER("inicio");
    State::Render();
    DEBUG_RENDER("fim");
}

void StageState::Input(float dt) {
    //Debug
    Vec2 mouseOnGrid = tileMap->PixelToMap(InputManager::GetInstance().GetMousePos());
    if(InputManager::GetInstance().KeyPress(SDLK_SPACE)){
        DEBUG_PRINT( tileMap->At(mouseOnGrid.x, mouseOnGrid.y).IsFree() );
    }

    if( InputManager::GetInstance().QuitRequested() == true ){
            quitRequested = true;
    }
    if( InputManager::GetInstance().KeyPress(SDLK_ESCAPE) == true ){
            backGroundMusic.Stop();
            popRequested = true;
    }
    if( InputManager::GetInstance().KeyPress(SDLK_0) == true ){
            showDEBUG = !showDEBUG;
            DEBUG_PRINT("showDEBUG: " << showDEBUG);
    }


//    if( InputManager::GetInstance().IsKeyDown(SDLK_KP_EQUALS)){
//        backGroundMusic.VolumeUpdate(-50);
//    }
//    if( InputManager::GetInstance().IsKeyDown(SDLK_KP_MINUS)){
//        backGroundMusic.VolumeUpdate(+50);
//    }
//    if( InputManager::GetInstance().IsKeyDown(UP_ARROW_KEY) == true ){
//            //arbitrario por enquanto
//            if(Camera::pos.y > -tilemap.GetTileHeight()*2)
//                Camera::pos.y -= CAMERA_SPEED;
//    }
//    if( InputManager::GetInstance().IsKeyDown(DOWN_ARROW_KEY) == true ){
//            //arbitrario por enquanto
//            if(Camera::pos.y + Game::GetInstance().GetWindowHeight() < tilemap.GetMapHeight() + tilemap.GetTileHeight()*2)
//                Camera::pos.y += CAMERA_SPEED;
//    }
//    if( InputManager::GetInstance().IsKeyDown(LEFT_ARROW_KEY) == true ){
//            //arbitrario por enquanto
//            if(Camera::pos.x > -tilemap.GetTileWidth()*2)
//                Camera::pos.x -= CAMERA_SPEED;
//    }
//    if( InputManager::GetInstance().IsKeyDown(RIGHT_ARROW_KEY) == true ){
//            //arbitrario por enquanto
//            if(Camera::pos.x + Game::GetInstance().GetWindowWidth() < tilemap.GetMapWidth() + tilemap.GetTileWidth()*2)
//                Camera::pos.x += CAMERA_SPEED;
//    }
}

void StageState::SetOnGrid(GameObject& gameObject, int x, int y){
//    gameObject.box.x = x * tilemap->GetTileWidth();
//    gameObject.box.y = y * tilemap->GetTileHeight();
}

void StageState::Pause(){
}

void StageState::Resume(){
}

void StageState::LoadAssets() const{
}

#include "Error_footer.h"
