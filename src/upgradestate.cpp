// Bartosz Stefaniak

#include "upgradestate.hpp"
#include "resourcemanager.hpp"
#include "defines.hpp"
#include "camera.hpp"

UpgradeState::UpgradeState(std::shared_ptr<Player> player_)
    : State(States::UpgradeState, sf::Color::Magenta), player{player_}
{
    background = std::make_unique<sf::Sprite>(sf::Sprite(ResourceManager::get_texture(UPGRADE_BG_PATH, true, true),
        {0, 0, static_cast<int>(Camera::get_width()), static_cast<int>(Camera::get_height())}));

    sf::Vector2f description_location ={static_cast<float>(Camera::get_width()) / 2.0f, static_cast<float>(Camera::get_height()) / 2.0f};
    description_location.x -= static_cast<float>(Camera::get_width()) * 0.25f;

    coins_text = std::make_unique<sf::Text>();
    coins_text->setFont(ResourceManager::get_font(COINS_FONT_PATH));
    coins_text->setString("coins: " + std::to_string(player->coin_cnt()));
    coins_text->setOrigin(coins_text->getGlobalBounds().width / 2.0f,
                          coins_text->getGlobalBounds().height / 2.0f);
    
    coins_text->setPosition(description_location - sf::Vector2f({0.0f, static_cast<float>(Camera::get_height()) * 0.3f}));


    text_buttons.push_back(std::make_unique<TextButton>(TextButton(
        description_location - sf::Vector2f({0.0f, static_cast<float>(Camera::get_height()) * 0.2f}),
        "Health",
        [this]() {},
        sf::Color::White, sf::Color::White, sf::Color::White)));
    
    text_buttons.push_back(std::make_unique<TextButton>(TextButton(
        description_location - sf::Vector2f({0.0f, static_cast<float>(Camera::get_height()) * 0.1f}),
        "Damage",
        [this]() {},
        sf::Color::White, sf::Color::White, sf::Color::White)));

    text_buttons.push_back(std::make_unique<TextButton>(TextButton(
        description_location + sf::Vector2f({0.0f, static_cast<float>(Camera::get_height()) * 0.0f}),
        "Speed",
        [this]() {},
        sf::Color::White, sf::Color::White, sf::Color::White)));

    text_buttons.push_back(std::make_unique<TextButton>(TextButton(
        description_location + sf::Vector2f({0.0f, static_cast<float>(Camera::get_height()) * 0.1f}),
        "Fire rate",
        [this]() {},
        sf::Color::White, sf::Color::White, sf::Color::White)));

    text_buttons.push_back(std::make_unique<TextButton>(TextButton(
        description_location + sf::Vector2f({0.0f, static_cast<float>(Camera::get_height()) * 0.2f}),
        "Coin magnet",
        [this]() {},
        sf::Color::White, sf::Color::White, sf::Color::White)));

    for(int i = 0; i < ABILITIES; ++i)
    {
        create_ability_level_sprite(i);
        create_cost_text(i);
        create_upgrade_button(i);
    }

    description_location += sf::Vector2f({0.0f, static_cast<float>(Camera::get_height()) * 0.35f});
    description_location.x += static_cast<float>(Camera::get_width()) * 0.25f;

    text_buttons.push_back(std::make_unique<TextButton>(TextButton(
        description_location - sf::Vector2f({static_cast<float>(Camera::get_width()) * 0.15f, 0.0f}),
        "Main menu",
        [this]() {
            pause();
            next = States::MenuState;
        },
        sf::Color::White, sf::Color(117, 151, 197), sf::Color(226, 211, 255))));
    
    text_buttons.push_back(std::make_unique<TextButton>(TextButton(
        description_location + sf::Vector2f({static_cast<float>(Camera::get_width()) * 0.15f, 0.0f}),
        "play",
        [this]() {
            pause();
            next = States::GameState;
        },
        sf::Color::White, sf::Color(117, 151, 197), sf::Color(226, 211, 255))));


    upgrade_ability = [this](int N)
    {
        int level_to_get = player->get_ability_levels()[N];
        if(level_to_get >= ABILITY_LEVELS)
        {
            return ;
        }

        if(player->coin_cnt() >= ABILITY_COST[N][level_to_get])
        {
            player->receive_coins(-ABILITY_COST[N][level_to_get]);
            player->get_ability_levels()[N]++;
            player->set_ability_value(N, ABILITY_VALUE[N][level_to_get]);
        }
    };
}

void UpgradeState::create_ability_level_sprite(int N)
{
    for(int i = 0; i < ABILITY_LEVELS; ++i)
    {
        sf::Vector2f pos = {static_cast<float>(Camera::get_width()) / 2.0f,
                            static_cast<float>(Camera::get_height()) / 2.0f};

        pos.y = text_buttons[N]->getPosition().y + text_buttons[N]->getLocalBounds().height / 2.0f;
        
        std::unique_ptr<sf::Sprite> ptr = std::make_unique<sf::Sprite>(ResourceManager::get_texture(ABILITY_BAR_OFF_PATH , true));

        ptr->setScale(ABILITY_BAR_SCALE_X, ABILITY_BAR_SCALE_Y);
        ptr->setColor(off_color);

        ptr->setOrigin(ptr->getTexture()->getSize().x / 2.0f, ptr->getTexture()->getSize().y / 2.0f);
        ptr->setPosition(pos - sf::Vector2f({(ptr->getOrigin().x * 2.0f + LEVEL_BAR_OFFSET_X) * (2 - i), 0.0f}));
        ability_level_sprites[N][i] = std::move(ptr);
    }

    ability_level_sprites[N][0]->setTexture(ResourceManager::get_texture(ABILITY_BAR_ON_PATH , true));
    ability_level_sprites[N][0]->setColor(on_color);
}

void UpgradeState::create_cost_text(int N)
{
    std::unique_ptr<sf::Text> ptr = std::make_unique<sf::Text>();
    ptr->setFont(ResourceManager::get_font(COINS_FONT_PATH));
    ptr->setString("cost: " + std::to_string(ABILITY_COST[N][1]));
    ptr->setOrigin(ptr->getGlobalBounds().width / 2.0f, ptr->getGlobalBounds().height / 2.0f);

    sf::Vector2f center = ability_level_sprites[N][ABILITY_LEVELS - 1]->getPosition();
    center.x += ability_level_sprites[N][ABILITY_LEVELS - 1]->getOrigin().x * 2.0f;
    center.x += ptr->getOrigin().x;
    center.x += 60.0f;

    center.y -= ptr->getGlobalBounds().height / 2.0f;

    ptr->setPosition(center);

    ability_cost_text[N] = std::move(ptr);
}

void UpgradeState::create_upgrade_button(int N)
{
    sf::Vector2f center = ability_cost_text[N]->getPosition();
    center.x += ability_cost_text[N]->getOrigin().x;
    center.x += 50.0f;
    center.y += ability_cost_text[N]->getOrigin().y;

    std::unique_ptr<TextButton> ptr = std::make_unique<TextButton>(TextButton(
        center,
        "+",
        [this, N]() { upgrade_ability(N); },
        sf::Color::White, sf::Color(117, 151, 197), sf::Color(226, 211, 255),
        40
    ));

    ptr->move(0.0f, -ptr->getGlobalBounds().height / 2.0f);

    ability_upgrade_buttons[N] = std::move(ptr);
}

void UpgradeState::draw()
{
    Camera::get_window().draw(*background);
    
    State::draw();

    for(int i = 0; i < ABILITIES; ++i)
    {
        for(int j = 0; j < ABILITY_LEVELS; ++j)
        {
            Camera::get_window().draw(*ability_level_sprites[i][j]);
        }

        Camera::get_window().draw(*ability_cost_text[i]);
        Camera::get_window().draw(*ability_upgrade_buttons[i]);
    }

    Camera::get_window().draw(*coins_text);
}

void UpgradeState::handle_events(sf::Event event)
{
    State::handle_events(event);

    for(int i = 0; i < ABILITIES; ++i)
    {
        ability_upgrade_buttons[i]->handle_events(event);
    }
}

void UpgradeState::update()
{
    auto& levels = player->get_ability_levels();

    for(int i = 0; i < ABILITIES; ++i)
    {
        for(int j = 0; j < ABILITY_LEVELS; ++j)
        {
            if(j < levels[i])
            {
                ability_level_sprites[i][j]->setTexture(ResourceManager::get_texture(ABILITY_BAR_ON_PATH));
                ability_level_sprites[i][j]->setColor(on_color);
            }
            else
            {
                ability_level_sprites[i][j]->setTexture(ResourceManager::get_texture(ABILITY_BAR_OFF_PATH));
                ability_level_sprites[i][j]->setColor(off_color);   
            }
        }
    }

    for(int i = 0; i < ABILITIES; ++i)
    {
        auto center = ability_cost_text[i]->getPosition();
        ability_cost_text[i]->setString("Cost: " + (levels[i] != ABILITY_LEVELS ? std::to_string(ABILITY_COST[i][levels[i]]) : "INF"));
        ability_cost_text[i]->setOrigin(ability_cost_text[i]->getGlobalBounds().width / 2, ability_cost_text[i]->getGlobalBounds().height / 2);
        ability_cost_text[i]->setPosition(center);
    }

    auto center = coins_text->getPosition();
    coins_text->setString("coins: " + std::to_string(player->coin_cnt()));
    coins_text->setOrigin(coins_text->getGlobalBounds().width / 2, coins_text->getGlobalBounds().height / 2);
    coins_text->setPosition(center);
}