// Bartosz Stefaniak

#pragma once

#include <SFML/Graphics.hpp>

#include "defines.hpp"

/*!
    Class for globally managing window, and it's viewed part\n
    provides function to acces sf::RenderWindow, sf::View, change position,\n
    get informations on screen.\n
*/
class Camera
{
public:
    /*!
        Constructs sf::RenderWindow and sf::View objects and sets up game screen.\n
    */
    Camera();

    /*!
        Returns reference to game window.\n
    */
    static sf::RenderWindow& get_window() { return window; };

    /*!
        Returns reference to game view.\n
    */
    static sf::View& get_view() { return view; };

    /*!
        Returns view height.\n
    */
    static unsigned int get_height();
    
    /*!
        Returns view width.\n
    */
    static unsigned int get_width();
    
    /*!
        Returns returns bounds for position on screen used in\n
        gamestate.hpp for free flying in space.\n
    */
    static sf::FloatRect get_bounds();

    /*!
        Resets view to initial part of screen, after changes while playing\n.
    */
    static void reset_center();

    /*!
        Sets view center to given position, used in gamestate.hpp to free fly.\n
    */
    static void set_center(sf::Vector2f center);

    /*!
        Returns rectangle bounding part of currently seen screen.\n
    */
    static sf::FloatRect get_curr_view_bounds();
private:
    static inline sf::RenderWindow window;
    static inline sf::View view;
};