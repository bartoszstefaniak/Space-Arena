// Bartosz Stefaniak

#include "textbutton.hpp"
#include "resourcemanager.hpp"
#include "camera.hpp"

#include <SFML/Window.hpp>

TextButton::TextButton(sf::Vector2f center, sf::String text, std::function<void()> function,
                       sf::Color active, sf::Color hover, sf::Color clicked, unsigned int char_size)
{
    setString(text);
    
    if(char_size) setCharacterSize(char_size);

    setFont(ResourceManager::get_font(COINS_FONT_PATH));
    setOrigin(getGlobalBounds().width / 2, getGlobalBounds().height / 2);
    setPosition(center);

    this->active_col  = active;
    this->hover_col   = hover;
    this->clicked_col = clicked;
    
    this->function = function;
    
}

void TextButton::handle_events(const sf::Event& event)
{
    auto mouse_pos = Camera::get_window().mapPixelToCoords(sf::Vector2i(sf::Mouse::getPosition(Camera::get_window())));

    // std::cout << "mouse_pos\t" << mouse_pos.x << " " << mouse_pos.y << "\n";
    // std::cout << "global\t" << getGlobalBounds().left << " " << getGlobalBounds().top << "\n";

    if(getGlobalBounds().contains(sf::Vector2f(mouse_pos)))
    {
        if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
        {
            setFillColor(clicked_col);
        }
        else
        {
            setFillColor(hover_col);
        }        
    }
    else
    {
        setFillColor(active_col);
    }

    if(event.type == sf::Event::MouseButtonReleased)
    {
        if(getGlobalBounds().contains(sf::Vector2f(mouse_pos)))
        {
            function();
        }
    }
}