#pragma once

#include <unordered_map>
#include <unordered_set>
#include <memory>
#include <chrono>
#include "Wall.h"
#include "CObject.h"
#include "Cylinder.h"
#include "Player.h"
#include "identifier.h"
#include <sampgdk.h>

class Manager
{
private:
    std::unordered_map<int, std::shared_ptr<CObject>> m_Objects;
    std::unordered_map<int, std::shared_ptr<Wall>> m_Walls;
    std::unordered_map<int, std::shared_ptr<Cylinder>> m_Cylinders;
    std::unordered_map<int, std::shared_ptr<Player>> m_Players;
    Identifier m_Identifier[PHY_MAX_ITEM_TYPES];
    std::unordered_set<int> m_RemoveItems[PHY_MAX_ITEM_TYPES];
    int m_UpdateInterval = PHY_TIMER_INTERVAL;
    std::chrono::system_clock::time_point m_LastUpdate = std::chrono::system_clock::now();
    int m_LastDelayMs = 0;

    template<typename T>
    int storeItem(int type, T item, std::unordered_map<int, std::shared_ptr<T>> &container);

public:
    int addObject(CObject object);
    int addWall(Wall wall);
    int addCylinder(Cylinder cylinder);
    void addPlayer(int playerid);
    void deletePlayer(int playerid);
    void deleteItem(int type, int id);
    std::shared_ptr<CObject> findObject(int id);
    std::shared_ptr<Wall> findWall(int id);
    std::shared_ptr<Cylinder> findCylinder(int id);
    std::shared_ptr<Player> findPlayer(int id);
    void update();
    void setUpdateInterval(int interval_ms);
    bool shouldUpdate();
    int countItems(int type);
    void removeMarkedItems();
};