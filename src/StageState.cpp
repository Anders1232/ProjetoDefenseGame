#include "../include/StageState.h"

#include "Error.h"
StageState::StageState():
    backGroundMusic(STAGE_BACKGROUND_MUSIC_FILE)
    ,showDEBUG(false)
{
    DEBUG_CONSTRUCTOR("inicio");
    Camera::pos.x = 0;
    Camera::pos.y = 0;

    //mousePosition(new Text(FONT2, 10, Text::BLENDED, {0, 0, 0, 0} );

    /*
        Constroi cenario
    */
    GameObject* ambient = new GameObject("Ambient");
    ambient->AddComponent(new RectTransform(*ambient, nullptr));
    ambient->AddComponent((Component*)new Sprite(*ambient, STAGE_BACKGROUND_FILE, true));
    (dynamic_cast<RectTransform&>(ambient->GetComponent(RECT_TRANSFORM))).SetAnchors(0,0,1,1);
    ambient->box.y = 0;
    AddObject(ambient);
    ambient->AddComponent(new TileMap<BaseTile>(*ambient, STAGE_TILEMAP_FILE, new TileSet(STAGE_TILESET_FILE, *ambient)));

    /*
        Coloca a musica
    */
    backGroundMusic.Play(-1);

    /*
        Coloca os personagens
    */
    GameObject* robo = new GameObject("Robo");
    AddObject(robo);
    DEBUG_PRINT("endereco de stageState: " << this);
    Robo* roboComponent = new Robo(*robo, this, ROBO_SP1);
    robo->AddComponent(roboComponent);


    GameObject* piloto = new GameObject("Piloto");
    piloto->showOnScreen = false;
    AddObject(piloto);
    piloto->AddComponent(new Piloto(*piloto, this, PILOTO_SP1));
    roboComponent->BoardPilot(piloto);

    GameObject* cursor = new GameObject("Cursor");
    cursor->AddComponent(new Cursor(*cursor, "resources/img/misc/cursor.png"));
    AddObject(cursor);


    DEBUG_CONSTRUCTOR("fim");
}

StageState::~StageState()
{
    backGroundMusic.Stop();
    objectArray.clear();
    //Sprite::Clear();
}

void StageState::Update(float dt)
{
    DEBUG_UPDATE("StageState::Update()- inicio");
    Input(dt);
    State::Update(dt);

    /*
    if(showDEBUG){
        mousePosition.SetText(to_string((int)(InputManager::GetInstance().GetMouseX() + Camera::pos.x))+"x"
                             +to_string((int)(InputManager::GetInstance().GetMouseY() + Camera::pos.y)));
    }
    */
    Camera::Update(Game::GetInstance().GetDeltaTime());
    DEBUG_UPDATE("StageState::Update()- fim");
}

void StageState::Render() const
{
    DEBUG_RENDER("inicio");
    State::Render();
    /*
    if(showDEBUG){
        mousePosition.Render(0, 0);
    }
    */
	DEBUG_RENDER("fim");
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
