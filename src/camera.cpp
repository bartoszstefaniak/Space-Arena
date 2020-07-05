// Bartosz Stefaniak

#include "camera.hpp"

#include <iostream>

Camera::Camera()
{
    int height = 720;
    int width  = 1320;

    window.create(sf::VideoMode(width, height), TITLE, sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);
    window.setMouseCursorVisible(false);
    
    view.setSize(width, height);

    view.setCenter(width / 2.0f, height / 2.0f);
    window.setView(view);
}

unsigned int Camera::get_height()
{
    return view.getSize().y;
}

unsigned int Camera::get_width()
{
    return view.getSize().x;
}

sf::FloatRect Camera::get_bounds()
{
    return sf::FloatRect(0, 0, 4.0f * get_width(), 4.0f * get_height());
}

void Camera::reset_center()
{
    view.setCenter(get_width() / 2.0f, get_height() / 2.0f);
    window.setView(view);
}

void Camera::set_center(sf::Vector2f center)
{
    view.setCenter(center);
    window.setView(view);
}

sf::FloatRect Camera::get_curr_view_bounds()
{
    sf::FloatRect result;
    result.left = view.getCenter().x - view.getSize().x / 2.0;
    result.top = view.getCenter().y  - view.getSize().y / 2.0;
    result.height = view.getSize().y;
    result.width  = view.getSize().x;
    return result;
}