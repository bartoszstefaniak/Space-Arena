// Bartosz Stefaniak

#include "enemy.hpp"
#include "resourcemanager.hpp"
#include "camera.hpp"
#include <cmath>
#include "projectilemanager.hpp"
#include "projectile.hpp"
#include "coin.hpp"
#include "animationmanager.hpp"

#include <random>

thread_local std::mt19937 gen{std::random_device{}()};
 
template<typename T>
T random(T min, T max) {
    using dist = std::conditional_t<
        std::is_integral<T>::value,
        std::uniform_int_distribution<T>,
        std::uniform_real_distribution<T>
    >;
    return dist{min, max}(gen);
}

Enemy::Enemy(std::shared_ptr<Player> player, int type, int level)
    : SpaceShip(get_spawn_point(), get_texture_path(type, level),
                get_speed(type, level)), player{player}
{
    setScale(X_SCALE, Y_SCALE);

    this->type  = type;
    this->level = level;
    hp = ENEMY_HP.at({type, level});
    fire_rate = ENEMY_FIRE_RATE.at({type, level});

}

sf::Vector2f Enemy::get_target_pos()
{
    return player->getPosition();
}

void Enemy::update()
{
    direction = get_target_pos() - getPosition();
    float norm = sqrt(direction.x * direction.x + direction.y * direction.y);
    
    direction /= norm;

    move(direction * speed);

    rot_to_target();

    auto curr_time = std::chrono::steady_clock::now();
    std::chrono::duration<float> diff = curr_time - last_shoot; 

    if(diff.count() > fire_rate)
    {
        last_shoot = curr_time;
        std::vector<std::unique_ptr<Projectile> > vec;
        vec.push_back(std::make_unique<Projectile>(getPosition(), getRotation(), ENEMY_LASER_PATH.at({type, level}), PROJECTILE_SPEED));
        ProjectileManager::add_projectiles(std::move(vec));
    }

}

void Enemy::kill()
{
    std::vector<std::unique_ptr<Projectile> > vec;
    vec.push_back(std::make_unique<Coin>(player, getPosition(), getRotation(), random(level * 3, level * level * 5)));

    ProjectileManager::add_projectiles(std::move(vec));

    AnimationManager::add_animation(EXPLOSION_ANIM_PATH, getPosition(), EXPLOSION_FRAMES);

    dead = true;
}

void Enemy::get_hit(int damage)
{
    hp -= damage;
    if(hp <= 0)
    {
        kill();
    }
}

std::string Enemy::get_texture_path(int type, int level)
{
    return ENEMY_TEXURE_PATH.at({type, level});
}

float Enemy::get_speed(int type, int level)
{
    return ENEMY_SPEED.at({type, level});
}

sf::Vector2f Enemy::get_spawn_point()
{
    sf::Vector2f center = Camera::get_view().getCenter();

    while(Camera::get_curr_view_bounds().contains(center))
    {
        center = {random(0.0f, Camera::get_bounds().width),
                  random(0.0f, Camera::get_bounds().height)};
    }

    return center;
}