#ifndef TILEMAP_H
#define TILEMAP_H

#include <vector>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>


#include "MultiTileSet.h"
#include "Point.h"
#include "TileInfo.h"
#include "Camera.h"

using std::vector;
using std::ifstream;
using std::stringstream;
using std::getline;
using std::cout;
using std::endl;
using std::streambuf;

class TileMap
{
    public:
        TileMap(int mWidth, int mHeight, int layers, TileSet* tileSet = NULL);
        TileMap(string file, TileSet* tileSet = NULL);
        void Load(string file);
        void SetTileSet(TileSet* tileSet);
        TileInfo& At(int x, int y, int z = 0);
        void Render (int cameraX = 0, int cameraY = 0);
        void RenderLayer(int layer, int cameraX = 0, int cameraY = 0);

        int GetWidth(){return mapWidth;};
        int GetHeight(){return mapHeight;};
        int GetDepth(){return mapDepth;};
        //~TileMap();
        Point PixelToChessPosition(int x, int y, int tileNumber = 1);
        int GetTileSize();
        int GetSize();

        float TileCenter(int coord, int tileNumber = 1);
        float MapPositionToPixelPosition(int coord, int tileNumber = 1);
        int PixelPositionToMapPosition(int pixels, int tileNumber = 1);

        void SetTileOccuper(Point point, GameObject* occuper, int tileNumber = 1);
        bool CheckTileState(Point point, TileState checkState, int tileNumber = 1);
        void SetTileState(Point point, TileState newState, int tileNumber = 1);

    protected:
        /* vazio */
    private:
        //vector<int> tileMatrix;
        vector<TileInfo> tileMatrix;
        //O mapa nao pode conter s? ints, dever? conter informa??o de estar ou nao ocupado, al?m de quais
        //tiles s?o seus vizinhos
        TileSet* tileSet;
        int mapWidth;
        int mapHeight;
        int mapDepth;
};

#endif // TILEMAP_H
