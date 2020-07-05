// Bartosz Stefaniak

#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <complex>

/*!
    Base class for spaceship object.
*/
class SpaceShip : public sf::Sprite
{
public:
    /*!
        sf::Vector2f center - position for spaceship to be created on.\n
        std::string texture_path - path to spaceship texture.\n
        float speed - spaceship movement speed.\n
        Initializes spaceship, calculates radius for collision detection.\n
    */
    SpaceShip(sf::Vector2f center, std::string texture_path, float speed = 1.0f);

    /*!
        Pure virtual function for updating state of spaceship.\n
    */
    virtual void update() = 0;

    /*!
        Pure virtual function for making spaceship receive damage.\n
    */
    virtual void get_hit(int damage) = 0;

    /*!
        Checks whether spaceship is dead.\n
    */
    virtual bool is_dead() { return dead; }

    /*!
        Returns collision radius for collision checking.\n
    */
    float get_collision_radius() { return collision_radius; };

protected:
    /*!
        Pure virtual function for chosing target.\n
    */
    virtual sf::Vector2f get_target_pos() = 0;

    /*!
        Pure virtual function for killing spaceship.\n
    */
    virtual void kill() = 0;
    
    /*!
        Returns rectangle in which spaceship can move.\n
    */
    virtual sf::FloatRect get_position_bounds();

    /*!
        Rotates texture to face target.\n
    */
    void rot_to_target();

    float collision_radius = 0;

    sf::Vector2f direction;

    int hp;
    float speed;
    bool dead = false;

};