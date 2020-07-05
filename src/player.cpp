// Bartosz Stefaniak

#include "player.hpp"
#include "camera.hpp"
#include "projectilemanager.hpp"
#include "animationmanager.hpp"

Player::Player(sf::Vector2f center, std::function <void()> on_death)
    : SpaceShip(center, PLAYER_TEXTURE_PATH)
{
    setScale(X_SCALE, Y_SCALE);

    this->on_death = on_death;
}

void Player::reset()
{
    for(int i = 0; i < ABILITIES; ++i)
    {
        ability_levels[i] = 1;
        ability_value[i] = ABILITY_VALUE[i][0];
    }

    setPosition({Camera::get_bounds().width / 2.0f, Camera::get_bounds().height / 2.0f});

    hp = ability_value[static_cast<int>(ABILITY_NAME::health)];
    coins = 0;
}

void Player::soft_reset()
{
    hp = ability_value[static_cast<int>(ABILITY_NAME::health)];
    setPosition({Camera::get_bounds().width / 2.0f, Camera::get_bounds().height / 2.0f});
    direction = {0, 0};
}


sf::Vector2f Player::get_target_pos()
{
    return Camera::get_window().mapPixelToCoords(sf::Vector2i(sf::Mouse::getPosition(Camera::get_window())),
                                                 Camera::get_view());
}

void Player::handle_events(sf::Event event)
{
    if(event.type == sf::Event::EventType::KeyReleased)
    {
        if(event.key.code == sf::Keyboard::D or event.key.code == sf::Keyboard::A)
        {
            direction.x = 0;
        }
        
        if(event.key.code == sf::Keyboard::W or event.key.code == sf::Keyboard::S)
        {
            direction.y = 0;
        }
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) direction.x = -1.0f;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) direction.x =  1.0f;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) direction.y = -1.0f;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) direction.y =  1.0f;

    auto curr_time = std::chrono::steady_clock::now();
    std::chrono::duration<float> diff = curr_time - last_shoot; 

    if(event.type == sf::Event::MouseButtonReleased and diff.count() > get_fire_rate())
    {
        last_shoot = std::chrono::steady_clock::now();
        std::vector<std::unique_ptr<Projectile> > vec;
        vec.push_back(std::make_unique<Projectile>(getPosition(), getRotation(), PLAYER_LASER_PATH, PROJECTILE_SPEED, get_damage(), true));
        ProjectileManager::add_projectiles(std::move(vec));
    }
}

void Player::update()
{
    move(direction * get_speed());

    sf::Vector2f position = getPosition() + getOrigin();

    if(position.x < get_position_bounds().left) position.x = get_position_bounds().left;
    if(position.x > get_position_bounds().left + get_position_bounds().width) position.x = get_position_bounds().left + get_position_bounds().width;
    if(position.y < get_position_bounds().top) position.y = get_position_bounds().top;
    if(position.y > get_position_bounds().top + get_position_bounds().height) position.y = get_position_bounds().top + get_position_bounds().height;
    
    position -= getOrigin();

    setPosition(position);

    rot_to_target();
}

void Player::get_hit(int damage)
{
    hp -= damage;

    if(hp <= 0)
    {
        return kill();
    }

}

void Player::kill()
{
    AnimationManager::add_animation(EXPLOSION_ANIM_PATH, getPosition(), EXPLOSION_FRAMES);
    direction = {0.0f, 0.0f};
    on_death();

}


void Player::check_collision(std::shared_ptr<SpaceShip> enemy)
{
    sf::Vector2f tmp = getPosition() - enemy->getPosition();
    float dist = sqrt(tmp.x * tmp.x + tmp.y * tmp.y);

    float rr = get_collision_radius() + enemy->get_collision_radius();

    if(!(dist > rr))
    {
        enemy->get_hit(100000);
        get_hit(1);
    }

}

std::array<int, ABILITIES>& Player::get_ability_levels()
{
    return ability_levels;
}

void Player::set_ability_value(int ability, float value)
{
    ability_value[ability] = value;
}