#include "Player.hpp"

Player::Player(int id)
{
    m_Id = id;
    m_World = 0;
}

void Player::setWorld(int world)
{
    m_World = world;
}

int Player::getWorld()
{
    return m_World;
}