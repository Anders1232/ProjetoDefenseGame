#include "../include/StageState.h"

//#define DEBUG
#ifdef DEBUG
    #define DEBUG_PRINT(x) do{cout << x << endl;}while(0)
#else
    #define DEBUG_PRINT(x)
#endif // DEBUG

StageState::StageState():
    //bg(STAGE_BACKGROUND_FILE),
    backGroundMusic(STAGE_BACKGROUND_MUSIC_FILE)
//    ,tilemap(new TileMap(STAGE_TILEMAP_FILE, new TileSet(STAGE_TILE_WIDTH, STAGE_TILE_WIDTH, STAGE_TILESET_FILE)))
{
    DEBUG_PRINT("StageState::StageState()-inicio");
    Sprite* bg = new Sprite(ambient, STAGE_BACKGROUND_FILE);
    //bg->SetCameraRelative(false);

    //Sempre lembrando que a ordem é importante!!
    //BG é renderizado primeiro, tilemap é desenhado logo acima, e assim sucessivamente
    ambient.AddComponent(bg);
    //ambient.AddComponent((Component*)tilemap);

    backGroundMusic.Play(-1);

    robo.AddComponent(new Robo(robo, 10, 10, ROBO_SP1));
    SetOnGrid(robo, 3 , 5);

    //AddObject(ambient);
    AddObject(&robo);
    DEBUG_PRINT("StageState::StageState()-fim");
}

StageState::~StageState()
{
    backGroundMusic.Stop();
    objectArray.clear();
    //Sprite::Clear();
}

void StageState::Update(float dt)
{
    DEBUG_PRINT("StageState::Update()- inicio");
    //Tranqueira-----
    Input(dt);
    stringstream aux;
    //---------------


    for(auto it = objectArray.begin(); it != objectArray.end(); it++){
        (*it)->Update(dt);
    }
    Camera::Update(Game::GetInstance().GetDeltaTime());
    DEBUG_PRINT("StageState::Update()- fim");
}

void StageState::Render() const
{
    DEBUG_PRINT("StageState::Render()- inicio");
    for(auto it = objectArray.begin(); it != objectArray.end(); it++){
	    if( (*it)->IsDead() == true) continue;
	    (*it)->Render();
    }
	DEBUG_PRINT("StageState::Render()- fim");
}

void StageState::Input(float dt) {
    if( InputManager::GetInstance().QuitRequested() == true ){
            quitRequested = true;
    }
    if( InputManager::GetInstance().KeyPress(SDLK_ESCAPE) == true ){
            backGroundMusic.Stop();
            popRequested = true;
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

#ifdef DEBUG
#undef DEBUG
#endif // DEBUG
