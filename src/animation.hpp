// Bartosz Stefaniak

#pragma once

#include <SFML/Graphics.hpp>
#include "defines.hpp"

/*!
    Class for displaying, creating animations.\n
*/
class Animation : public sf::Sprite
{
public:
    /*!
        std::string path - path to animation frames, in form x/y/animation_name{C}.png, where {C} is frame number\n
        starting at 0\n
        sf::Vector2f center - center point for animation position.\n
        int frames - how many frames does animation have.\n
    */
    Animation(std::string path, sf::Vector2f center, int frames);

    /*!
        Returns flag saying if animation is over
    */
    bool done() { return done_; } ;

    /*!
        Changes animation frame every ANIMATION_FRAME_SKIP( defines.hpp ) game frames.\n
        When animation is over sets done_ flag; \n
    */
    void update();

private:
    std::string base_anim_path;
    bool done_ = false;
    int frames = 0;
    int skipped_frames = ANIMATION_FRAME_SKIP;
    int current_frame = 0;

};