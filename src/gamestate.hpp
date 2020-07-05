// Bartosz Stefaniak

#pragma once

#include "state.hpp"
#include "projectilemanager.hpp"
#include "enemy.hpp"
#include "player.hpp"

#include <array>

/*!
    State subclass representing gameplay state.\n
*/
class GameState : public State
{
public:
    /*!
        Constructs texts, sprites, player used in game.\n
    */
    GameState();

    /*!
        Overriden handle_events(sf::Event event) function same semantics as in State class.\n
    */
    virtual void handle_events(sf::Event event) override;

    /*!
        Overriden update() function same semantics as in State class.\n
    */
    virtual void update() override;

    /*!
        Overriden draw() function same semantics as in State class.\n
    */
    virtual void draw()   override;

    /*!
        Overriden reset() function same semantics as in State class.\n
    */
    virtual void reset()  override;

    /*!
        Overriden pause() function same semantics as in State class.\n
    */
    virtual void pause()  override;

    /*!
        Overriden resume() function same semantics as in State class.\n
    */
    virtual void resume() override;

    /*!
        Returns player pointer used in upgradestate, needed for ability levels, gold information.\n
    */
    std::shared_ptr<Player> get_player();

private:
    std::shared_ptr<Player> player;
    std::unique_ptr<sf::Text> coins_text = std::make_unique<sf::Text>();
    std::unique_ptr<TextButton> won_game1;
    std::unique_ptr<TextButton> won_game2;

    std::vector < std::unique_ptr<sf::Sprite> > health_sprites;
    std::vector < std::shared_ptr<Enemy> > enemies;

    std::chrono::time_point<std::chrono::steady_clock> last_resume;

    ProjectileManager projectile_manager;

    int enemies_spawned = 0;
    int enemy_tier = 1;

    /*!
        Spawns enemies.\n
    */
    void spawn_enemies();

};