//#pragma once
#ifndef ROBOPATH_H
#define ROBOPATH_H

#include <vector>
#include <map>

#include "Component.h"
#include "Vec2.h"
#include "Sprite.h"
#include "TileMap.h"
#include "resources_path.h"
#include "PlayerUnity.h"
#include "Handler.h"
#include "Event.h"
#include "TileInfo.h"
#include "PathMarker.h"

using std::vector;
using std::multimap;

class PlayerUnityPath: public Component
{
    public:
        PlayerUnityPath(GameObject& associated, TileMap<TileInfo>* tileMap, Vec2& destination);
        virtual ~PlayerUnityPath();
        void EarlyUpdate(float dt){};
        void Update(float dt);
        void LateUpdate(float dt){};
        void Render() const {};
        bool Is(unsigned int type)const;
        void ButtonObserver(Component* btn);

        void CreatePath();
        Vec2 GetNext();
        bool HasPoints();
        void OnClick();
        void AddMarker(Vec2 position);

        Event<PlayerUnityPath, int&> pathFinished;

        typedef multimap<long, HandlerBase*> HandlerMap;
        HandlerMap StartMapping()
		{
			HandlerMap temp;
			return temp;
		}

        //registra o objeto e qual seu método deve ser chamado, associando o id
        template<typename TargetT>
        void RegisterPathFinishedListener(TargetT* object)
        {
            listeners.insert(std::make_pair(++listenerId, new Handler<TargetT>(object, object->OnPathFinished)));
        }


    protected:

    private:
        long listenerId;
        Vec2& destination;
        bool parentSelected;
        vector<Vec2*> movingPath;
        vector<GameObject*> pathMarkers;
        HandlerMap listeners;
        TileMap<TileInfo>* tileMap;
};

#endif // ROBOPATH_H
