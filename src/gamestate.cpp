// Bartosz Stefaniak

#include "gamestate.hpp"
#include "resourcemanager.hpp"
#include "camera.hpp"
#include "player.hpp"
#include "projectilemanager.hpp"
#include "animationmanager.hpp"

GameState::GameState()
    : State(States::MenuState, sf::Color::Yellow)
{
    sprites.push_back(std::make_unique<sf::Sprite>(sf::Sprite(ResourceManager::get_texture(GAME_BG_PATH, false, true),
                     static_cast<sf::IntRect>(Camera::get_bounds()))));

    player = std::make_shared<Player>(Player({Camera::get_bounds().width / 2.0f, Camera::get_bounds().height / 2.0f},
                            [this]()
                            {
                                next = States::UpgradeState;
                            }));

    for(int i = 0; i < MAX_LIFES; ++i)
    {
        health_sprites.emplace_back(std::make_unique<sf::Sprite>());
        health_sprites.back()->setTexture(ResourceManager::get_texture(LIFE_TEXTURE_PATH));
    }

    coins_text->setFont(ResourceManager::get_font(COINS_FONT_PATH));

    won_game1  = std::make_unique<TextButton>(TextButton(
        {0, 0},
        "You won!",
        [this](){
            pause();
            next = States::MenuState;
        },
        sf::Color::White, sf::Color(117, 151, 197), sf::Color(226, 211, 255),
        40));
    
    won_game2  = std::make_unique<TextButton>(TextButton(
        {0, 0},
        "Click to return to menu.",
        [this](){
            pause();
            next = States::MenuState;
        },
        sf::Color::White, sf::Color(117, 151, 197), sf::Color(226, 211, 255),
        40));
}

std::shared_ptr<Player> GameState::get_player()
{
    return player;
}

void GameState::draw()
{
    State::draw();

    for(int i = 0; i < player->get_hp(); ++i)
    {
        Camera::get_window().draw(*health_sprites[i]);
    }

    
    for(auto& projectile : ProjectileManager::get_projectiles())
    {
        Camera::get_window().draw(*projectile);
    }
    
    if(player->get_hp() > 0)Camera::get_window().draw(*player);

    for(auto enemy : enemies)
    {
        Camera::get_window().draw(*enemy);
    }

    AnimationManager::draw();
    Camera::get_window().draw(*coins_text);

    if(enemy_tier >= 4 && !enemies.size())
    {
        won_game1->setPosition(player->getPosition());
        won_game2->setPosition(won_game1->getPosition() + sf::Vector2f({0.0f, won_game1->getGlobalBounds().height}) + sf::Vector2f(0.0f, 10.0f));
        Camera::get_window().draw(*won_game1);
        Camera::get_window().draw(*won_game2);
    }

}

void GameState::handle_events(sf::Event event)
{
    if(enemy_tier >= 4 && !enemies.size())
    {
        won_game1->handle_events(event);
        won_game2->handle_events(event);
    }
    else
    {
        State::handle_events(event);
        player->handle_events(event);

    }

    if(event.type == sf::Event::KeyReleased and event.key.code == sf::Keyboard::Key::Escape)
    {
        _done = true;
        next = States::MenuState;
    }

    
}

void GameState::update()
{
    if(player->get_hp() > 0 && !(enemy_tier >= 4 && !enemies.size()))
    {

        player->update();

        sf::FloatRect bounds = Camera::get_bounds();

        auto position = player->getPosition();
        
        bounds.left = Camera::get_width()  / 2.0f;
        bounds.top  = Camera::get_height() / 2.0f;

        bounds.width  = Camera::get_bounds().width  - 2.0f * bounds.left;
        bounds.height = Camera::get_bounds().height - 2.0f * bounds.top;

        if(position.x < bounds.left) position.x = bounds.left;
        if(position.x > bounds.left + bounds.width) position.x = bounds.left + bounds.width;
        if(position.y < bounds.top) position.y = bounds.top;
        if(position.y > bounds.top + bounds.height) position.y = bounds.top + bounds.height;

        Camera::set_center(position);

        for(int i = 0; i < player->get_hp(); ++i)
        {
            health_sprites[i]->setPosition(Camera::get_curr_view_bounds().left + LIFE_OFFSET_X * (i + 1) + health_sprites[i]->getTextureRect().width * i,
                                        Camera::get_curr_view_bounds().top + LIFE_OFFSET_Y);
        }

        sf::Vector2f mid = {Camera::get_curr_view_bounds().left + Camera::get_curr_view_bounds().width / 2.0f,
                            Camera::get_curr_view_bounds().top + 5.0f};

        coins_text->setString("Coins: " + std::to_string(player->coin_cnt()));
        coins_text->setOrigin(coins_text->getLocalBounds().width / 2, coins_text->getLocalBounds().height / 2);
        coins_text->setPosition(mid);


        ProjectileManager::check_collisions(player);

        for(auto enemy : enemies)
        {
            ProjectileManager::check_collisions(enemy);
            player->check_collision(enemy);
        }


        enemies.erase(std::remove_if(std::begin(enemies), std::end(enemies), [](std::shared_ptr<Enemy> ptr)
                        {
                            return ptr->is_dead();
                        }), end(enemies));



        for(auto enemy : enemies)
        {
            enemy->update();
        }

        ProjectileManager::update();

        auto curr_time = std::chrono::steady_clock::now();
        std::chrono::duration<float> diff = curr_time - last_resume; 

        if(diff.count() > 2.0f)
        {
            spawn_enemies();
        }

        AnimationManager::update();
    }
    else if(player->get_hp() <= 0)
    {
        AnimationManager::update();

        if(!AnimationManager::size())
        {
            pause();
            sf::sleep(sf::seconds(0.2f));
        }
    }
}

void GameState::reset()
{
    player->reset();
    
}

void GameState::pause()
{
    _done = true;

    Camera::reset_center();
}

void GameState::resume()
{
    _done = false;
    enemies.clear();
    ProjectileManager::clear();
    player->soft_reset();
    AnimationManager::clear();
    last_resume = std::chrono::steady_clock::now();

    enemy_tier = 1;
    enemies_spawned = 0;

    Camera::set_center(player->getOrigin());
}

void GameState::spawn_enemies()
{
    if(enemies.size() < 6)
    {
        if(enemies_spawned == 12)
        {
            enemy_tier += 1;
            enemies_spawned = 0;
        }
        
        if(enemy_tier < 4)
        {
            int level = enemy_tier;
            int type  = 1;
            enemies.push_back(std::make_shared<Enemy>(player, type, level));
            ++enemies_spawned; 
        }
        else
        {
            if(enemy_tier == 4)
            {
                int level = 0;
                int type  = 0;
                enemies.push_back(std::make_shared<Enemy>(player, type, level));
                ++enemies_spawned; 

                ++enemy_tier;
            }
        }
    }
}