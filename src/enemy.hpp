// Bartosz Stefaniak

#pragma once

#include "spaceship.hpp"
#include "player.hpp"
#include <chrono>
#include <memory>

/*!
    SpaceShip subclass representing enemy.\n
*/
class Enemy : public SpaceShip
{
public:
    /*!
        std::shared_ptr<Player> player - pointer to player used to determine direction towards player.\n
        int type - type of enemy\n
        int level - level of enemy\n
        both used to calculate enemy stats from defines.hpp file.\n
    */
    Enemy(std::shared_ptr<Player> player, int type, int level);

    /*!
        Overriden update() function same semantics as in SpaceShip class.\n
    */
    virtual void update() override;

    /*!
        Overriden get_hit() function same semantics as in SpaceShip class.\n
    */
    virtual void get_hit(int damage) override;

private:
    std::shared_ptr<Player> player;

    /*!
        Function that kills enemy and creates coin, and animation.\n
    */
    virtual void kill() override;

    /*!
        Returns position of target(player position).\n
    */
    virtual sf::Vector2f get_target_pos() override;

    /*!
        Returns texture path based on type and level.\n
    */
    std::string get_texture_path(int type, int level);

    /*!
        Returns speeed based on type and level.\n
    */
    float get_speed(int type, int level);

    /*!
        Randomly designates spawn point for enemy outside of player view.\n
    */
    sf::Vector2f get_spawn_point();

    std::chrono::time_point<std::chrono::steady_clock> last_shoot;
    float fire_rate;

    int type;
    int level;


};