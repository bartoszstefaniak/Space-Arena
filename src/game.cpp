// Bartosz Stefaniak

#include "game.hpp"
#include "resourcemanager.hpp"

Game::Game()
{
    states[States::GameState] = std::make_shared<GameState>();
    states[States::MenuState] = std::make_shared<MenuState>();

    player = std::dynamic_pointer_cast<GameState>(states[States::GameState])->get_player();

    states[States::UpgradeState] = std::make_shared<UpgradeState>(player);

    curr_state = states[States::MenuState];
}

void Game::run()
{
    sf::Clock clock;
    sf::Time next_update_time = clock.getElapsedTime();
    bool exit = false;

    while(!curr_state->exit() && !exit)
    {
        sf::Time curr_time = clock.getElapsedTime();
        sf::Event event;

        while(Camera::get_window().pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                exit = true;
            }

            curr_state->handle_events(event);
        }

        if(curr_state->done())
        {
            if(curr_state->do_reset())
            {
                states[curr_state->get_next()]->reset();
            }

            if(curr_state->exit()) break;

            curr_state->pause();
            curr_state = states[curr_state->get_next()];

            curr_state->resume();
        }

        if(curr_time >= next_update_time)
        {
            next_update_time += sf::seconds(0.01f);
            curr_state->update();
            if(curr_time < next_update_time)
            {
                Camera::get_window().clear(curr_state->get_bg_color());
                curr_state->draw();
                Camera::get_window().display();
            }
        }
        else
        {
            sf::sleep(next_update_time - curr_time);
        }
    }
}