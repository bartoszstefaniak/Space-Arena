// Bartosz Stefaniak

#include "projectile.hpp"
#include "resourcemanager.hpp"
#include "camera.hpp"

#include <complex>

Projectile::Projectile(const sf::Vector2f& origin, const float angle, const std::string& path, float speed, int value, bool player_made)
{
    setTexture(ResourceManager::get_texture(path, true));
    setOrigin({static_cast<float>(getTextureRect().width / 2.0f), static_cast<float>(getTextureRect().height / 2.0f)});
    setPosition(origin);

    setRotation(angle);

    auto tmp = std::complex<float>(0.0f, -1.0f);
    tmp *= std::polar(1.0f, angle * 0.0174532925f);

    direction = {tmp.real(), tmp.imag()};

    this->speed = speed;
    this->value = value;
    this->player_made = player_made;
}

void Projectile::update()
{
    setPosition(getPosition() + speed * direction);
}