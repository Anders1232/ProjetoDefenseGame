#include "../include/StageState.h"

#include "Error.h"
StageState::StageState():
    backGroundMusic(STAGE_BACKGROUND_MUSIC_FILE)
    ,mousePosition(FONT2, 10, BLENDED, {0, 0, 0, 0})
    ,showDEBUG(false)
{
    DEBUG_CONSTRUCTOR("StageState", "inicio");
    Camera::pos.x = 0;
    Camera::pos.y = 0;

    /*
        Constroi cenario
    */
    GameObject* ambient = new GameObject();
    ambient->AddComponent(new RectTransform(*ambient, nullptr));
    ambient->AddComponent((Component*)new Sprite(*ambient, STAGE_BACKGROUND_FILE, true));
    ambient->box.x = 0;
    ambient->box.y = 0;
    AddObject(ambient);

    /*
        Coloca a musica
    */
    backGroundMusic.Play(-1);

    /*
        Coloca os personagens
    */
    GameObject* robo = new GameObject();
    DEBUG_PRINT("StageState", "endereco de stageState: " << this);
    robo->AddComponent(new Robo(*robo, this, 50, 50, ROBO_SP1));
    AddObject(robo);

    DEBUG_CONSTRUCTOR("StageState", "fim");
}

StageState::~StageState()
{
    backGroundMusic.Stop();
    objectArray.clear();
    //Sprite::Clear();
}

void StageState::Update(float dt)
{
    //DEBUG_PRINT("StageState::Update()- inicio");
    Input(dt);
    if(showDEBUG){
        mousePosition.SetText(to_string((int)(InputManager::GetInstance().GetMouseX() + Camera::pos.x))+"x"
                             +to_string((int)(InputManager::GetInstance().GetMouseY() + Camera::pos.y)));
    }
    State::UpdateArray(dt);
    Camera::Update(Game::GetInstance().GetDeltaTime());
    //DEBUG_PRINT("StageState::Update()- fim");
}

void StageState::Render() const
{
    DEBUG_RENDER("StageState", "inicio");
    State::RenderArray();
    if(showDEBUG){
        mousePosition.Render(0, 0);
    }
	DEBUG_RENDER("StageState", "fim");
}

void StageState::Input(float dt) {
    if( InputManager::GetInstance().QuitRequested() == true ){
            quitRequested = true;
    }
    if( InputManager::GetInstance().KeyPress(SDLK_ESCAPE) == true ){
            backGroundMusic.Stop();
            popRequested = true;
    }
    if( InputManager::GetInstance().KeyPress(SDLK_0) == true ){
            showDEBUG = !showDEBUG;
            DEBUG_PRINT("StageState", "showDEBUG: " << showDEBUG);
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
