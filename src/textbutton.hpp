// Bartosz Stefaniak

#pragma once

#include <SFML/Graphics.hpp>
#include <functional>

/*!
    Class for buttons made of text.\n
*/
class TextButton : public sf::Text 
{
public:
    /*!
        sf::Vector2f center - position of center point of button to be placed on.\n
        sf::String text - text of button.\n
        std::function<void()> function - function called when button is clicked.\n
        sf::Color active, sf::Color hover, sf::Color clicked - colors of text in respective buttons states.\n
        unsigned int char_size - size of characters, if 0 then size is default.\n
        Initializes TextButton object.\n
    */
    TextButton(sf::Vector2f center, sf::String text, std::function<void()> function,
               sf::Color active, sf::Color hover, sf::Color clicked, unsigned int char_size = 0);

    /*!
        Handles events(clicking, changing color according to mouse position).\n
    */
    void handle_events(const sf::Event& event);
    
protected:
    std::function<void()> function;
    sf::Color active_col, hover_col, clicked_col;
};