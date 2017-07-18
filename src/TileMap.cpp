#include "../include/TileMap.h"

TileMap::TileMap(int mapWidth, int mapHeight, int layers, TileSet* tileSet)
{
    this->mapWidth = mapWidth;
    this->mapHeight = mapHeight;
    this->mapDepth = layers;
    tileMatrix.resize(mapWidth * mapHeight * mapDepth, -1);
    this->tileSet = tileSet;
}

TileMap::TileMap(string file, TileSet* tileSet)
{
    Load(file);
    this->tileSet = tileSet;
}

//TileMap::~TileMap()
//{
//    //dtor
//}

void TileMap::Load(string file)
{
    //uso de stdlib.h temporario
    FILE *arquivo = fopen(file.c_str(), "r");
    fscanf(arquivo, "%d", &mapWidth);
    fscanf(arquivo, "%*c");
    fscanf(arquivo, "%d", &mapHeight);
    fscanf(arquivo, "%*c");
    fscanf(arquivo, "%d", &mapDepth);
    fscanf(arquivo, "%*c");
    tileMatrix.resize( mapDepth * mapHeight * mapWidth , -1);
    int num;
    for(int k = 0, l = 0; k < mapDepth; k++){
        for(int i = 0; i < mapWidth; i++){
            for(int j = 0; j < mapHeight; j++, l++){
                            fscanf(arquivo, "%d", &num);
                            fscanf(arquivo, "%*c");
                            tileMatrix[ l ].tileType = num - 1;

                            if(tileMatrix[ l ].tileType == 1 ||
                               tileMatrix[ l ].tileType == -1){
                                    //cout << "tile bloqueado" << endl;
                                    tileMatrix[ l ].state = BLOCKED;
                            }
            }
                    //cout << endl;
        }
        //cout << endl;
    }
    //cout << endl;
    fclose(arquivo);
//    cout << endl;
//    for(int i = 0, l = 0; i < mapHeight ; i++){
//            for(int j = 0; j < mapWidth; j++, l++){
//                cout << tileMatrix[ l ].tileType << ":";
//            }
//            cout << endl;
//    }
//    cout << endl;
}

void TileMap::SetTileSet(TileSet* tileSet)
{
    this->tileSet = tileSet;
}

TileInfo& TileMap::At(int x, int y, int z)
{
    int posInVector = -1;
    TileInfo *endereco = NULL;
    if(x > mapWidth || y > mapHeight || z > mapDepth) return *endereco; //fora das dimens?es da matriz
    posInVector = z*(mapWidth * mapHeight) + mapWidth * y + x;
    //endereco = &(tileMatrix[posInVector].tileType);
    endereco = &(tileMatrix[posInVector]);
    return *endereco;
}
void TileMap::Render(int cameraX, int cameraY)
{
    for (int k = 0; k < mapDepth; k++){
        for(int j = 0; j < mapHeight; j++){
                for(int i = 0; i < mapWidth; i++){
                    tileSet->Render(At(i,j,k).tileType,
                                    i * tileSet->GetTileWidth() - cameraX,
                                    j * tileSet->GetTileHeight() - cameraY);
                }
        }
    }
}
void TileMap::RenderLayer(int layer, int cameraX, int cameraY)
{
    //Faz o mesmo que Render, mas para uma layer s?.
    for(int j = 0; j < mapHeight; j++){
            for(int i = 0; i < mapWidth; i++){
                tileSet->Render(At(i, j, layer).tileType,
                                i * tileSet->GetTileWidth() - cameraX,
                                j * tileSet->GetTileHeight() - cameraY);
            }
    }
}

int TileMap::GetSize()
{
    return tileMatrix.size();
}

int TileMap::GetTileSize()
{
    return tileSet->GetTileWidth();
}

Point TileMap::PixelToChessPosition(int x, int y, int tileNumber)
{
    if(x < 0 && y < 0) return Point( -1, -1);
    else               return Point( (int)(x + Camera::pos.x)/(tileSet->GetTileWidth()*tileNumber),
                                     (int)(y + Camera::pos.y)/(tileSet->GetTileHeight()*tileNumber) );
}

float TileMap::TileCenter(int coord, int tileNumber)
{
    return coord * tileNumber * GetTileSize() + GetTileSize() * tileNumber/2.0;
}

float TileMap::MapPositionToPixelPosition(int coord, int tileNumber)
{
    return GetTileSize() * tileNumber * coord + GetTileSize() * tileNumber/2.0;
}

int TileMap::PixelPositionToMapPosition(int pixels, int tileNumber)
{
    return pixels/(GetTileSize() * tileNumber);
}

void TileMap::SetTileState(Point point, TileState newState, int tileNumber)
{

    for(int i = 0; i < tileNumber; i++){
        for(int j = 0; j < tileNumber; j++){
            At(point.x * tileNumber + i, point.y * tileNumber + j).state = newState;
        }
    }
}

bool TileMap::CheckTileState(Point point, TileState checkState, int tileNumber)
{
    for(int i = 0; i < tileNumber; i++){
        for(int j = 0; j < tileNumber; j++){
                if( checkState != At(point.x * tileNumber + i, point.y * tileNumber + j).state ) return false;
        }
    }
    return true;
}

void TileMap::SetTileOccuper(Point point, GameObject* occuper, int tileNumber)
{
    for(int i = 0; i < tileNumber; i++){
        for(int j = 0; j < tileNumber; j++){
            At(point.x * tileNumber + i, point.y * tileNumber + j).occuper = occuper;
        }
    }
}

