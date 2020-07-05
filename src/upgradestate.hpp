// Bartosz Stefaniak

#pragma once

#include "state.hpp"
#include "player.hpp"

#include <SFML/Graphics.hpp>
#include <functional>

/*!
    State subclass representing player spaceship upgrade screen.\n
*/
class UpgradeState : public State
{
public:
    /*!
        std::shared_ptr<Player> player_ - pointer to player spaceship, provides information about,\n
        gathered coins, ability levels.\n
        Creates texts, buttons, background.\n
    */
    UpgradeState(std::shared_ptr<Player> player_);

    /*!
        Overriden draw() function same semantics as in State class.\n
    */
    virtual void draw() override;

    /*!
        Overriden update() function same semantics as in State class.\n
    */
    virtual void update() override;

    /*!
        Overriden handle_events(sf::Event event) function same semantics as in State class.\n
    */
    virtual void handle_events(sf::Event event) override;

private:
    /*!
        Creates N-th ability, level sprites(bought-unbought ability level).\n
    */
    void create_ability_level_sprite(int N);

    /*!
        Creates text describing cost of N-th ability upgrade.\n
    */
    void create_cost_text(int N);

    /*!
        Creates button which upgrades N-th ability\n
    */
    void create_upgrade_button(int N);

    std::function<void(int)> upgrade_ability;

    std::array<std::array<std::unique_ptr<sf::Sprite>, ABILITY_LEVELS>, ABILITIES> ability_level_sprites;

    std::shared_ptr<Player> player;
    std::unique_ptr<sf::Text> coins_text;
    std::unique_ptr<sf::Sprite> background;

    std::array<std::unique_ptr<sf::Text>, ABILITIES> ability_cost_text;
    std::array<std::unique_ptr<TextButton>, ABILITIES> ability_upgrade_buttons;

    sf::Color on_color = sf::Color(255, 255, 255, 255);
    sf::Color off_color = sf::Color(255, 255, 255, 160);

};