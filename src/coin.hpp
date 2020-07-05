// Bartosz Stefaniak

#pragma once

#include "projectile.hpp"
#include "player.hpp"

#include <memory>

/*!
    Class representing projectile subtype: coin\n
    It's homing projectile if player is close enough, otherwise it stays in place.\n
*/
class Coin : public Projectile
{
public:
    /*!
        std::shared_ptr<Player> player - pointer to player used to determine direction towards player.\n
        sf::Vector2f& origin - place of enemy's death\n
        float angle - coin rotation angle\n
        int value - value of coin\n
    */
    Coin(std::shared_ptr<Player> player, const sf::Vector2f& origin, float angle, int value = 1);

    /*!
        Calculates direction towards player, and moves coin if player is close enough.\n
    */
    virtual void update() override;

private:
    std::shared_ptr<Player> player;

};