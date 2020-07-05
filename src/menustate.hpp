// Bartosz Stefaniak

#pragma once

#include "state.hpp"

/*!
    State subclass representing main menu.\n
*/
class MenuState : public State
{
public:
    /*!
        Creates buttons, background for main menu.\n
    */
    MenuState();

    /*!
        Overriden draw() function same semantics as in State class.\n
    */
    virtual void draw() override;

    /*!
        Overriden do_reset() function tells game loop whether next state needs to be reseted.\n
    */
    virtual bool do_reset() override { return _reset_next; };
private:
    std::unique_ptr<sf::Text> title;
};