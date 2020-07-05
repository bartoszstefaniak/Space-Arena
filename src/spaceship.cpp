// Bartosz Stefaniak

#include "spaceship.hpp"
#include "resourcemanager.hpp"
#include "camera.hpp"

#include <iostream>

SpaceShip::SpaceShip(sf::Vector2f center, std::string texture_path, float speed)
{
    setTexture(ResourceManager::get_texture(texture_path, true));
    setOrigin({static_cast<float>(getTextureRect().width / 2.0f), static_cast<float>(getTextureRect().height / 2.0f)});
    setPosition(center);
    this->speed = speed;

    direction = {0, 0};

    collision_radius = std::min(ResourceManager::get_texture(texture_path, true).getSize().x / 2.0f,
                                ResourceManager::get_texture(texture_path, true).getSize().y / 2.0f);

}

sf::FloatRect SpaceShip::get_position_bounds()
{
    sf::FloatRect bounds = Camera::get_bounds();
    
    bounds.left = getOrigin().x;
    bounds.top  = getOrigin().y;

    bounds.width  = Camera::get_bounds().width;
    bounds.height = Camera::get_bounds().height;

    return bounds;
}

void SpaceShip::rot_to_target()
{
    sf::Vector2f target   = get_target_pos();
    sf::Vector2f position = getPosition();

    sf::Vector2f temp = target - position;

    float angle = atan2(temp.y, temp.x);

    if(angle < 0)
    {
        angle = 2.0f * PI + angle;
    }

    setRotation(90.0f + angle * RAD_TO_DEG);
}