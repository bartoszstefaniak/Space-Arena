// Bartosz Stefaniak

#pragma once

#include <SFML/Graphics.hpp>
#include <string>


/*!
    Class representing projectiles in game, used as class for lasers.\n
*/
class Projectile : public sf::Sprite
{
public:
    /*!
        const sf::Vector2f& origin - projectile creation position.\n
        const float angle - angle that projectile needs to be rotated by.\n
        const std::string& path - path to texture for laser.\n
        float speed = 1 - default speed of projectile.\n
        int value = 1 - default value of projectile, used as damage or coin value in coin subclass.\n
        bool player_made = false - false means that projectile was created by enemy, used in resolving colisions.\n
    */
    Projectile(const sf::Vector2f& origin, const float angle, const std::string& path, float speed = 1, int value = 1, bool player_made = false);

    /*!
        Updates position of projectile.\n
    */
    virtual void update();

    /*!
        Sets _done flag for projectile. Meaning it will be deleted in next projectilemanager update() call.\n
    */
    void set_done() { _done = true; };

    /*!
        Returns value of projectile.\n
    */
    int get_value() { return value; };

    /*!
        Returns _done flag.\n
    */
    bool done() { return _done; };

    /*!
        Returns shooter, true = player, false = enemy.\n
    */
    bool shooter() { return player_made; };

    /*!
        Checks whether this projectile is coin.\n
    */
    bool is_coin() { return type; };

protected:
    sf::Vector2f direction = {0.0f, 0.0f};
    float speed = 0.0f;
    int value;
    bool _done = 0;
    bool player_made = 0;
    int type = 0;
};
