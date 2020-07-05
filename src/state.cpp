// Bartosz Stefaniak

#include "state.hpp"
#include "camera.hpp"
#include <SFML/Window.hpp>

State::State(States state_id, sf::Color bg_color)
{
    this->state_id = state_id;
    this->bg_color = bg_color;
}

void State::draw()
{
    for(const auto& sprite : sprites)
    {
        Camera::get_window().draw(*sprite);
    }

    for(const auto& text_button : text_buttons)
    {
        Camera::get_window().draw(*text_button);
    }
}

void State::handle_events(sf::Event event)
{
    for(const auto& text_button : text_buttons)
    {
        text_button->handle_events(event);
    }
}

void State::pause()
{
    _done = true;
}

void State::resume()
{
    _done = false;
}