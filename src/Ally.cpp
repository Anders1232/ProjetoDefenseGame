#include "../include/Ally.h"

void Ally::SetStatus(int vidaMaxima, float ataque, int range, float defesa, int speed, int distance, int coolDown)
{
//    vida.Open(this, vidaMaxima);
//    barraCooldown.Open(coolDown, this->box.RectCenterX(), this->box.RectCenterY());
    this->defesa = defesa;
    this->ataque = ataque;
    this->range = range;
    this->distance = distance;
    this->speed = speed;
    this->atackCoolDown = this->coolDown = coolDown;
}

//gerencia as modificacoes e os estados  do ally
void Ally::Update(float dt)
{
        StateMachine(dt);
    Input(dt);
    IdentifyOpponent();
    CloseEnemiesUpdate();
    //if(timer.Get() < coolDown) timer.Update(dt);
    sp.Update(dt);
    if(IsDead() == true){
        cout << this->nome <<": Fui destruido!! Noooooooo.... D: " << endl;
        mapReference->At( currentPosition.x, currentPosition.y ).state = FREE;
        mapReference->At( currentPosition.x , currentPosition.y ).occuper = NULL;
    }
}

void Ally::Input(float dt)
{
    if(box.IsInside(InputManager::GetInstance().GetMouseX() + Camera::pos.x,
                    InputManager::GetInstance().GetMouseY() + Camera::pos.y) == true){
                    if(InputManager::GetInstance().KeyPress(SDLK_d) == true ){
                        //vidaAtual = 0;
                    }
                    if(InputManager::GetInstance().KeyPress(SDLK_t) == true ){
                        //vidaAtual -= 5;
                    }
                    if(InputManager::GetInstance().KeyPress(SDLK_h) == true ){
                        //vidaAtual += 5;
                    }
                    if(InputManager::GetInstance().KeyPress(SDLK_q) == true){
                        //barraCooldown.SetTimer(this->coolDown);
                    }
    }
    if(InputManager::GetInstance().IsMouseDown(LEFT_MOUSE_BUTTON) == true &&
       box.IsInside(InputManager::GetInstance().GetMouseX() + Camera::pos.x,
                    InputManager::GetInstance().GetMouseY() + Camera::pos.y) == true){
                        /*if( inputTimer.Get() > 0.3 && barraCooldown.IsFull()){
                            if(menuAberto == true){
                                menuAberto = false;
                            }
                            //cout << this->nome << ": estou sendo selecionado para andar!" << endl;
                            charState = AGUARDANDO_ANDAR;
                        }else inputTimer.Update(dt);*/
    }
    //if(InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON) == true)
    if(InputManager::GetInstance().MouseRelease(LEFT_MOUSE_BUTTON) == true){
        Sound soundFX("images/audio/TIRO_02.wav");
        soundFX.Play(0);

        //se o mouse estiver dentro do personagem, o menu é aberto e recebe true se nao existir.
        //se o menu ja existir, recebe falso, pois sera fechado mais para frente.
        if(this->box.IsInside(InputManager::GetInstance().GetMouseX() + Camera::pos.x,
                              InputManager::GetInstance().GetMouseY() + Camera::pos.y)){
                                            if(menuAberto == false){
                                                Camera::Follow(this);
                                                Abrir_Menu();
                                                menuAberto = true;
                                            }else{
                                                menuAberto = false;
                                            }
        //se o clique for fora do personagem, menu recebe falso para ser fechado mais a frente
        }else{
            menuAberto = false;
        }
        for(int i = 0; i < buttonArray.size(); i++){
            //verifica qual o botao que foi clicado, se algum deles for clicado.
            if(buttonArray[i].box.IsInside(InputManager::GetInstance().GetMouseX() + Camera::pos.x,
                                           InputManager::GetInstance().GetMouseY() + Camera::pos.y)){
                Sound soundFX("images/audio/TIRO_01.wav");
                soundFX.Play(0);

                switch(i){
//                    case(0):
//                    //ESSE BOTAO NAO EXISTE MAIS!
//                       cout << "esse botao pede para andar" << endl;
//                       charState = AGUARDANDO_ANDAR;
//                       break;
                case(1):
                        /*cout << "esse botao pede para usar especial" << endl;
                        if(barraCooldown.IsFull()){
                            charState = AGUARDANDO_ALVO;
                        }*/
                        break;
                case(2):
                       cout << "esse botao pede para usar item" << endl;
                       charState = AGUARDANDO_ITEM;
                       break;
                case(3):
                    cout << "esse botao pede para ejetar" << endl;
                    Ejetar();
                    break;
               }
            }
        }
        if (menuAberto == false){
            Fechar_Menu();
        }
    }
}


void Ally::StateMachine(float dt)
{
    switch(charState){
        case MOVENDO:
            if( path.empty() == true){
                charState = REPOUSO;
                break;
            }else{
                Andar(tileNumber);
            }
            break;

        case DEFENDENDO:
            break;

        case INATIVO:
            break;
        case AGUARDANDO_ALVO:
            alvoEspecial = EncontrarRobo();
            if(alvoEspecial != NULL){
                charState = ESPECIAL;
                //barraCooldown.Esvazia();
            }
            if(InputManager::GetInstance().MousePress(SDL_BUTTON_RIGHT) == true){
                charState = REPOUSO;
            }
            break;

        case ESPECIAL:
            especialTime.Update(dt);
            if(especialTime.Get() > 1.5){
                alvoEspecial->Curar(10);
                especialTime.Restart();
            }
            if(alvoEspecial->VidaCheia() == true){
                charState = REPOUSO;
            }
            break;

        case ATACANDO:
            atackTimer.Update(dt);
            if(atackTimer.Get() > atackCoolDown){
                Atacar();
                atackTimer.Restart();
            }
            if(closeEnemies.size() == 0){
                cout << this->nome <<": Vencemos! \\o/" << endl;
                charState = REPOUSO;
            }
            break;

        case REPOUSO:
            if(closeEnemies.size() > 0){
                cout << this->nome << ": Inimigos proximos!! Atacaaaaar! >xO" << endl;
                charState = ATACANDO;
            }
            break;
        case AGUARDANDO_ANDAR:
            MakePath(tileNumber);
            //if(InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON) == true)
            if(InputManager::GetInstance().MouseRelease(LEFT_MOUSE_BUTTON) == true){
                    inputTimer.Restart();
                    if(ValidPath() == true){
                            charState = MOVENDO;
                    }else{
                            while(path.empty() == false) path.pop();
                            charState = REPOUSO;
                    }
                    //barraCooldown.Esvazia();
            }
            break;
    }
}

Ally* Ally::EncontrarRobo()
{
    Ally* alvo = NULL;
    if(InputManager::GetInstance().MousePress(SDL_BUTTON_LEFT) == true){
        int mapX = mapReference->PixelPositionToMapPosition(InputManager::GetInstance().GetMouseX() + Camera::pos.x);
        int mapY = mapReference->PixelPositionToMapPosition(InputManager::GetInstance().GetMouseY() + Camera::pos.y);
        //cout << "MAPX: " << mapX << " | MAPY: " << mapY << endl;
        int roboX = mapReference->PixelPositionToMapPosition(box.RectCenterX());
        int roboY = mapReference->PixelPositionToMapPosition(box.RectCenterY());
        //cout << "PILOTOX: " << pilotoX << " | PILOTOY: " << pilotoY << endl;

        if( (mapX >= roboX - 1) &&
                (mapX <= roboX + 1) ){
            if( (mapY >= roboY - 1) && (mapY <= roboY + 1) ) {
                if(mapReference->At( mapX, mapY ).state == ALLY){
                    if(mapReference->At( mapX, mapY ).occuper->Is("Robo")){
                        Ally* robo = (Ally*) mapReference->At( mapX, mapY ).occuper;
                        alvo = robo;
                    }
                }
            }
        }
    }

    if(alvo != NULL){
        if(mapReference->PixelPositionToMapPosition(alvo->box.RectCenterX()) > mapReference->PixelPositionToMapPosition(box.RectCenterX())){
            allyPosition = RIGHT;
        }else if(mapReference->PixelPositionToMapPosition(alvo->box.RectCenterX()) < mapReference->PixelPositionToMapPosition(box.RectCenterX())){
            allyPosition = LEFT;
        }else if(mapReference->PixelPositionToMapPosition(alvo->box.RectCenterY()) > mapReference->PixelPositionToMapPosition(box.RectCenterY())){
            allyPosition = FRONT;
        }else{
            allyPosition = BACK;
        }
        OrientarSprite();
    }
    return alvo;
}

//verifica se ally esta morto
bool Ally::IsDead(){
/*
    if(vida.GetVida() <= 0){
        if(Camera::GetFocus() == this) Camera::Unfollow();
        return true;
    }
    */
    return false;
}

bool Ally::Is(string type)
{
    //cout << "Is(" << type << ") == Ally?" << endl;
    if(type == "Ally") return true;
    else return false;
}

//movimenta o ally pelo mapa.
void Ally::Andar(int tileNumber){

        Sound soundFX("images/audio/TIRO_03.wav");
        //cout << "inicio allyPosition: " << allyPosition << endl;
        if( abs(box.RectCenterX() - mapReference->TileCenter( path.front().x, tileNumber) ) < 5 &&
            abs(box.RectCenterY() - mapReference->TileCenter( path.front().y, tileNumber) ) < 5){
                box.SetRectCenterX( mapReference->TileCenter( path.front().x, tileNumber) );
                box.SetRectCenterY( mapReference->TileCenter( path.front().y, tileNumber) );
                path.pop();
                //teste de posicionamento de som
                soundFX.Play(0);

        }else{
        Point pastPosition( currentPosition.x, currentPosition.y );
        if( mapReference->TileCenter( path.front().x, tileNumber) > box.RectCenterX() ){
            box.SetRectCenterX(box.RectCenterX() + speed);
            allyPosition = RIGHT;
        }else if( mapReference->TileCenter( path.front().x, tileNumber) < box.RectCenterX() ){
            box.SetRectCenterX(box.RectCenterX() - speed);
            allyPosition = LEFT;
        }
        if( mapReference->TileCenter( path.front().y, tileNumber) > box.RectCenterY() ){
            box.SetRectCenterY(box.RectCenterY() + speed);
            allyPosition = FRONT;
        }else if( mapReference->TileCenter( path.front().y, tileNumber) < box.RectCenterY() ){
            box.SetRectCenterY(box.RectCenterY() - speed);
            allyPosition = BACK;
        }
        currentPosition.SetPoint( mapReference->PixelPositionToMapPosition( box.RectCenterX(), tileNumber),
                                  mapReference->PixelPositionToMapPosition( box.RectCenterY(), tileNumber));
                if(pastPosition.x != currentPosition.x ||
                   pastPosition.y != currentPosition.y){
                            mapReference->SetTileState(pastPosition, FREE, tileNumber);
                            //mapReference->At(pastPosition.x, pastPosition.y).state = FREE;
                            mapReference->SetTileOccuper(pastPosition, NULL, tileNumber);
                            //mapReference->At(pastPosition.x, pastPosition.y).occuper = NULL;

                            mapReference->SetTileState(currentPosition, ALLY, tileNumber);
                            //mapReference->At(currentPosition.x, currentPosition.y).state = ALLY;
                            mapReference->SetTileOccuper(currentPosition, this, tileNumber);
                            //mapReference->At(currentPosition.x, currentPosition.y).occuper = this;
                            //teste de posicionamento de som
                            soundFX.Play(0);

                            #ifdef DEBUG
                            cout << "pasPosition: " << endl;
                            cout << "mapStateAt( " << pastPosition.x << ", " << pastPosition.y << "): " << mapReference->At(pastPosition.x, pastPosition.y).state << endl;
                            cout << "currentPosition: " << endl;
                            cout << "mapStateAt( " << currentPosition.x << ", " << currentPosition.y << "): " << mapReference->At(currentPosition.x, currentPosition.y).state << endl;
                            #endif // DEBUG
                            if(currentPosition.x - pastPosition.x == 1){
                                RangeAreaUpdate( 1, 0);
                            }else if(currentPosition.x - pastPosition.x == -1){
                                RangeAreaUpdate(-1, 0);
                            }
                            if(currentPosition.y - pastPosition.y == 1){
                                RangeAreaUpdate( 0,  1);
                            }else if(currentPosition.y - pastPosition.y == -1){
                                RangeAreaUpdate( 0, -1);
                            }
                }
            OrientarSprite();
            }
}

//para a movimentacao do ally caso este encontre um obstaculo pelo caminho.
void Ally::Parar(){

}

//reduz a vida do ally
//void Ally::Danificar(float dano)
//{
//    this->vidaAtual -= dano - defesa/10;
//}

//notifica as colisoes de ally
void Ally::NotifyCollision(GameObject &other)
{

}

//anima o personagem com seu ataque basico.
void Ally::Atacar()
{
    /*
    if(closeEnemies.size() > 0){
        cout << this->nome <<": Yaah! >=O" << endl;
        Enemy* enemyTarget = (Enemy*) closeEnemies.begin()->first;
        enemyTarget->Danificar( ataque );
        //teste de posicionamento de som
        Sound soundFX("images/audio/boom.wav");
        soundFX.Play(0);
        if(mapReference->PixelPositionToMapPosition(enemyTarget->box.RectCenterX()) > mapReference->PixelPositionToMapPosition(box.RectCenterX())){
            allyPosition = RIGHT;
        }else if(mapReference->PixelPositionToMapPosition(enemyTarget->box.RectCenterX()) < mapReference->PixelPositionToMapPosition(box.RectCenterX())){
            allyPosition = LEFT;
        }else if(mapReference->PixelPositionToMapPosition(enemyTarget->box.RectCenterY()) > mapReference->PixelPositionToMapPosition(box.RectCenterY())){
            allyPosition = FRONT;
        }else{
            allyPosition = BACK;
        }
        OrientarSprite();
    }*/
}

//gerencia o ally em seu modo de defesa.
void Ally::Defender()
{
    charState = DEFENDENDO;
}

//abre o menu de personagem


//fecha o menu de personagem
void Ally::Fechar_Menu()
{
    buttonArray.clear();
}

//coloca um item no vetor de itens do ally
void Ally::Alocar_Item()
{

}

void Ally::Usar_Item()
{

}

bool Ally::IsLeader()
{
    return lider;
}

//gerencia o uso de especial
void Ally::Especial()
{

}

void Ally::MakePath(int tileNumber)
{
    Point newPoint;
    newPoint.x = mapReference->PixelPositionToMapPosition( InputManager::GetInstance().GetMouseX() + Camera::pos.x, tileNumber );
    newPoint.y = mapReference->PixelPositionToMapPosition( InputManager::GetInstance().GetMouseY() + Camera::pos.y, tileNumber );
    cout << "novo ponto: " << newPoint.x << ", " << newPoint.y << endl;
    if(path.size() < distance && //ainda pode andar E
       newPoint.x + (tileNumber - 1) < mapReference->GetHeight()  && //está dentro das linhas do mapa E
       newPoint.y + (tileNumber - 1) < mapReference->GetWidth()){ //está dentro das colunas do mapa

//        if(mapReference->At(line, row).state == FREE ||
//           mapReference->At(line, row).state == ALLY){
        if(mapReference->CheckTileState(newPoint, FREE, tileNumber) ||
           mapReference->CheckTileState(newPoint, ALLY, tileNumber) ){


           //cout << "ponto ( " << line << ", " << row << ") adicionado" << endl;
           //cout << "mapStateAt( " << line << ", " << row << "): " << mapReference->At(line, row).state << endl;

           //se a lista de pontos estiver vazia ou
           //se o novo ponto for vizinho do ponto anterior
           //Point newPoint(line, row);

           if( path.empty() == true){
               path.push( newPoint );
               //cout << "ponto ( " << newPoint.x << ", " << newPoint.y << ") adicionado" << endl;
           }else if( (newPoint.x == path.back().x && abs(newPoint.y - path.back().y) == 1) ||
                     (newPoint.y == path.back().y && abs(newPoint.x - path.back().x) == 1) ){
               //se o novo ponto for diferente do ponto anterior
               if(newPoint.x != path.back().x ||
                  newPoint.y != path.back().y){
                    //cout << "ENTREEEEEI" << endl;
                    path.push( newPoint );
                    //cout << "ponto ( " << newPoint.x << ", " << newPoint.y << ") adicionado" << endl;
                }
            }
        }
    }
}


bool Ally::ValidPath(int tileNumber)
{
    if(mapReference->CheckTileState(path.back(), FREE, tileNumber) ) return true;
                   //At(path.back().x, path.back().y).state == FREE
    else return false;
}

void Ally::OrientarSprite()
{
    switch(allyPosition){
        case FRONT:
            //cout << "Fica de frente" << endl;
            sp.SetAnimation(0, 4);
            break;
        case BACK:
            //cout << "Fica de costas" << endl;
            sp.SetAnimation(3, 4);
            break;
        case LEFT:
            //cout << "Fica pra esquerda" << endl;
            sp.SetAnimation(1, 4);
            break;
        case RIGHT:
            //cout << "Fica pra direita" << endl;
            sp.SetAnimation(2, 4);
            break;
    }
}

void Ally::Abrir_Menu(){
    float offSet = 125;
    float angulo = 0;
    Sprite botao(BOTAO1);
    Sprite botao2(BOTAO2);
    Sprite botao3(BOTAO3);
    Sprite botao4(BOTAO4);
    /*
    StillAnimation* botaoAnim = new StillAnimation(box.RectCenterX() + cos(angulo*M_PI/180)*offSet,
                                                   box.RectCenterY() + sin(angulo*M_PI/180)*offSet,
                                                   rotation, botao, 50, false);
    buttonArray.emplace_back(*botaoAnim);
    angulo += 90;

    StillAnimation* botaoAnim2 = new StillAnimation(box.RectCenterX() + cos(angulo*M_PI/180)*offSet,
                                                   box.RectCenterY() + sin(angulo*M_PI/180)*offSet,
                                                   rotation, botao2, 50, false);
    buttonArray.emplace_back(*botaoAnim2);
    angulo += 90;

    StillAnimation* botaoAnim3 = new StillAnimation(box.RectCenterX() + cos(angulo*M_PI/180)*offSet,
                                                   box.RectCenterY() + sin(angulo*M_PI/180)*offSet,
                                                   rotation, botao3, 50, false);
    buttonArray.emplace_back(*botaoAnim3);
    angulo += 90;

    StillAnimation* botaoAnim4 = new StillAnimation(box.RectCenterX() + cos(angulo*M_PI/180)*offSet,
                                                   box.RectCenterY() + sin(angulo*M_PI/180)*offSet,
                                                   rotation, botao4, 50, false);
    buttonArray.emplace_back(*botaoAnim4);
    angulo += 90;
    */
}

bool Ally::IsLider()
{
    return lider;
}

string Ally::GetNome()
{
    return this->nome;
}

bool Ally::AreaRespiro()
{
//    if((box.RectCenterX() > 500 && box.RectCenterX() < 770) && (box.RectCenterY() > 100 && box.RectCenterY() < 300)){
//        return true;
//    }

    return false;
}

bool Ally::AreaMapa()
{
    if(box.RectCenterX() > 730){
        return false;
    }

    return true;
}

int Ally::GetVida()
{
    return 1;//vida.GetVida();
}

float Ally::GetPorcentagemVida()
{
    return 100;//vida.GetPorcentagemVida();
}


CharacterPosition Ally::GetAllyPosition()
{
    return allyPosition;
}

void Ally::Curar(int cura){
    /*int vidaNova = vida.GetVida() + cura;
    vida.SetVida(vidaNova);*/
}

bool Ally::VidaCheia(){
    /*if(vida.IsFull() == true){
        return true;
    }*/
    return true;
}
