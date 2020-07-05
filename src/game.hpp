// Bartosz Stefaniak

#pragma once

#include <map>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "state.hpp"
#include "defines.hpp"
#include "menustate.hpp"
#include "gamestate.hpp"
#include "resourcemanager.hpp"
#include "upgradestate.hpp"
#include "camera.hpp"
#include "player.hpp"

/*!
    Main game class, that manages game loop, and states changes.\n
*/
class Game
{
public:
    /*!
        Initializes states and player class.\n
    */  
    Game();

    /*!
        Runs the game managing time, state changes, events, etc.\n
    */
    void run();
private:
    std::map <States, std::shared_ptr<State> > states;
    std::shared_ptr<State> curr_state;
    std::shared_ptr <Player> player;

    bool reset_next = false;

    Camera camera;
};