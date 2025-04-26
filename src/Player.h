#pragma once

class Player
{
private:
    int m_Id;
    int m_World;

public:
    Player(int id);
    void setWorld(int world);
    int getWorld();
};