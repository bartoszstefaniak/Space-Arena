// Bartosz Stefaniak

#pragma once

#include "spaceship.hpp"
#include "defines.hpp"
#include <chrono>

#include <functional>
#include <memory>

/*!
    SpaceShip subclass representing plater.
*/
class Player : public SpaceShip
{
public:
    /*!
        sf::Vector2f center - position of player to be spawned in.\n
        std::function<void()> on_death - function to be invoked upon player death.\n
    */
    Player(sf::Vector2f center, std::function<void()> on_death);

    /*!
        Changes player coin amount by coins_.\n
    */
    void receive_coins(int coins_) { coins += coins_; };

    /*!
        Overriden handle_events(sf::Event event) function same semantics as in State class.\n
    */
    void handle_events(sf::Event event);

    /*!
        Checks for player collisions with enemies, and resolves them.\n
    */
    void check_collision(std::shared_ptr<SpaceShip> enemy);

    /*!
        Returns amount of coins owned by player.\n
    */
    int coin_cnt() { return coins; };

    /*!
        Overriden update() function same semantics as in State class.\n
    */
    virtual void update() override;

    /*!
        Overriden get_hit(int damage) deals damage to player, and calls kill() if player was killed.\n
    */
    virtual void get_hit(int damage) override;
    
    /*!
        Returns player's current hp.\n
    */
    int get_hp() { return hp; };

    /*!
        Resets player stats, invoked after new game button was clicked in main menu.\n
    */
    void reset();

    /*!
        Returns reference to array of ability levels used to drawing buttons in upgradestate.\n
    */
    std::array<int, ABILITIES>& get_ability_levels();

    /*!
        Sets ability value.\n
    */
    void set_ability_value(int ability, float value);

    /*!
        Returns max health. Used in soft and hard reset.\n;
    */
    int get_health()        { return static_cast<int>(ability_value[static_cast<int>(ABILITY_NAME::health)]); }

    /*!
        Returns current damage.\n;
    */
    int get_damage()           { return static_cast<int>(ability_value[static_cast<int>(ABILITY_NAME::damage)]); }

    /*!
        Returns current speed.\n;
    */
    float get_speed()       { return ability_value[static_cast<int>(ABILITY_NAME::speed)]; }

    /*!
        Returns current fire rate.\n;
    */
    float get_fire_rate()   { return ability_value[static_cast<int>(ABILITY_NAME::fire_rate)]; }

    /*!
        Returns current coin magnet range.\n;
    */
    float get_coin_magnet() { return ability_value[static_cast<int>(ABILITY_NAME::coin_magnet)]; }

    /*!
        Soft resets player(hp), Used after death.\n;
    */
    void soft_reset();
    
private:
    
    /*!
        Returns position of mouse cursor.\n
    */
    virtual sf::Vector2f get_target_pos() override;

    /*!
        Kills player, creates animation.\n
    */
    virtual void kill() override;

    std::function<void()> on_death;
    std::chrono::time_point<std::chrono::steady_clock> last_shoot;

    int coins = 0;

    std::array<int, 5>   ability_levels = {1, 1, 1, 1, 1};
    std::array<float, 5> ability_value  = {3.0f, 1.0f, 5.0f, 1.5f, 100.0f};


};