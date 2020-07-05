// Bartosz Stefaniak

#include "coin.hpp"
#include "defines.hpp"

Coin::Coin(std::shared_ptr<Player> player, const sf::Vector2f& origin, float angle, int value)
    : Projectile(origin, angle, COIN_PATH, COIN_SPEED, value), player{player}
{
    scale(COIN_SCALE_X, COIN_SCALE_Y);
    this->value = value;
    type = 1;
}

void Coin::update()
{
    auto vec = player->getPosition() - getPosition();
    float dist = sqrt(vec.x * vec.x + vec.y * vec.y);

    vec /= dist;

    if(dist <= player->get_coin_magnet())
    {
        direction = vec;
    }
    else direction = {0.0f, 0.0f};

    move(direction * speed);

}