// Bartosz Stefaniak

#pragma once

#include "defines.hpp"
#include "textbutton.hpp"


#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>


/*!
    Base class for state of game.
*/
class State
{
public:
    /*!
        States state_id - id of constructed state.\n
        sf::Color bg_color - background color of state.\n
        Initializes state_id and bg_color member variables.\n
    */
    State(States state_id, sf::Color bg_color);

    /*!
        Calls handle_events(sf::Event event) on every class member, which has this function,\n
        text_buttons, player and processes event according to class in which is called.\n
    */
    virtual void handle_events(sf::Event event);

    /*!
        Calls draw() on every class member, which has this function,\n
        animations, projectiles, spaceships.\n
    */
    virtual void draw();

    /*!
        Pauses current state preparing it to get changed.\n
    */
    virtual void pause();

    /*!
        Resumes current state after resume.\n
    */
    virtual void resume();

    /*!
        Calls update() on every class member, which has this function,\n
        animations, projectiles, spaceships, camera.\n
    */
    virtual void update() {};

    /*!
        Resets current state.\n
    */
    virtual void reset()  {};

    /*!
        Returns next state after current.\n
    */
    States get_next()        { return next; }

    /*!
        Returns current state_id.\n
    */
    States get_state_id()    { return state_id; }

    /*!
        Returns current state background color.\n
    */
    sf::Color get_bg_color() { return bg_color; }

    /*!
        Checks if done flag is set up.\n
    */
    virtual bool done()  { return _done; }

    /*!
        Checks if exit flag is set up.\n
        This flag exits game.\n
    */
    virtual bool exit()  { return _exit; }

    /*!
        Checks reset() should be called on current state.\n
    */
    virtual bool do_reset() { return _reset; }

    /*!
        Checks reset() should be called on next state.\n
    */
    virtual bool reset_next() { return _reset_next; };

    /*!
        Destructs sprites, text buttons.\n
    */
    virtual ~State() = default;


protected:
    std::vector <std::unique_ptr<sf::Sprite> > sprites;
    std::vector <std::unique_ptr<TextButton> > text_buttons;
    States next;
    States state_id;
    sf::Color bg_color;
    bool _reset_next = false;
    bool _done  = false;
    bool _exit  = false;
    bool _reset = false;
};