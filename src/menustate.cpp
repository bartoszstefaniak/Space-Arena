// Bartosz Stefaniak

#include "menustate.hpp"
#include "camera.hpp"
#include "resourcemanager.hpp"

MenuState::MenuState()
    : State(States::MenuState, sf::Color::Red)
{
    sprites.push_back(std::make_unique<sf::Sprite>(sf::Sprite(ResourceManager::get_texture(MENU_BG_TEXTURE_PATH, false, true),
                      {0, 0, static_cast<int>(Camera::get_width()), static_cast<int>(Camera::get_height())})));


    sf::Vector2f mid = {static_cast<float>(Camera::get_width()) / 2.0f, static_cast<float>(Camera::get_height()) / 2.0f};

    text_buttons.push_back(std::make_unique<TextButton>(TextButton(
        mid - sf::Vector2f(0, static_cast<float>(static_cast<float>(Camera::get_height())) * 0.1f), 
        "New game", [this] ()
        {
            pause();
            next = States::GameState;
            _reset_next = true;
        }, sf::Color::White, sf::Color(117, 151, 197), sf::Color(226, 211, 255), 40)));

    text_buttons.push_back(std::make_unique<TextButton>(TextButton(
        mid,
        "Continue", [this] ()
        {
            pause();
            next = States::GameState;
            _reset_next = false;
        }, sf::Color::White, sf::Color(117, 151, 197), sf::Color(226, 211, 255))));


    text_buttons.push_back(std::make_unique<TextButton>(TextButton(
        mid + sf::Vector2f(0, static_cast<float>(Camera::get_height()) * 0.1f),
        "Upgrades", [this] ()
        {
            pause();
            next = States::UpgradeState;
        }, sf::Color::White, sf::Color(117, 151, 197), sf::Color(226, 211, 255))));

    text_buttons.push_back(std::make_unique<TextButton>(TextButton(
        mid + sf::Vector2f(0, static_cast<float>(Camera::get_height()) * 0.2f),
        sf::String(L"Exit"), [this] ()
        {
            pause();
            _exit = 1;
        }, sf::Color::White, sf::Color(117, 151, 197), sf::Color(226, 211, 255))));

    title = std::make_unique<sf::Text>();
    title->setFont(ResourceManager::get_font(COINS_FONT_PATH));
    title->setCharacterSize(80);
    title->setString("Space Arena");
    title->setOrigin(title->getLocalBounds().width / 2, title->getLocalBounds().height / 2);
    title->setPosition(mid - sf::Vector2f(0, static_cast<float>(Camera::get_height()) * 0.35f));
}

void MenuState::draw()
{
    State::draw();
    Camera::get_window().draw(*title);
}