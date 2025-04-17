#pragma once

#include <unordered_map>
#include <unordered_set>
#include <memory>
#include <chrono>
#include "Wall.h"
#include "CObject.h"
#include "identifier.h"

class Manager
{
private:
    std::unordered_map<int, std::shared_ptr<CObject>> m_Objects;
    std::unordered_map<int, std::shared_ptr<Wall>> m_Walls;
    int m_UpdateInterval = PHY_TIMER_INTERVAL;
    std::chrono::system_clock::time_point m_LastUpdate = std::chrono::system_clock::now();
    int m_LastDelayMs = 0;
    std::unordered_set<int> m_RemoveObjects;
    std::unordered_set<int> m_RemoveWalls;
    Identifier m_Identifier[PHY_MAX_ITEM_TYPES];

public:
    int addObject(CObject object);
    int addWall(Wall wall);
    void deleteObject(int id);
    void deleteWall(int id);
    std::shared_ptr<CObject> findObject(int id);
    std::shared_ptr<Wall> findWall(int id);
    void update();
    void setUpdateInterval(int interval_ms);
    bool shouldUpdate();
    void removeMarkedItems();
    int countItems(int type);
};