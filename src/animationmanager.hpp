// Bartosz Stefaniak

#pragma once

#include "animation.hpp"

#include <vector>

/*!
    Class for managing globally animations(drawing them, calling update,adding to pool) using static functions.\n
    This class also manages memory allocations for animations.\n
*/
class AnimationManager
{
public:
    /*!
        Calls update on every animation. And deletes those already finished.\n
    */
    static void update();

    /*!
        Deletes all ongoing animations.\n
    */
    static void clear();

    /*!
        Draws animations to window provided by camera.hpp\n
    */
    static void draw();

    /*!
        Returns number of currently managed animations.\n
    */
    static int size() { return animations.size(); }

    /*!
        Adds animation to container by invoking Animation constructor.\n
        Takes same parameters as Animation constructor.\n
    */
    static void add_animation(std::string path, sf::Vector2f center, int frames);

private:
    static inline std::vector<std::unique_ptr<Animation> > animations;

};