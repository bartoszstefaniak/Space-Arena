// Bartosz Stefaniak

#include "projectilemanager.hpp"
#include "coin.hpp"

void ProjectileManager::update()
{
    projectiles.insert(std::end(projectiles), 
                       std::make_move_iterator(std::begin(projectile_buffer)),
                       std::make_move_iterator(std::end(projectile_buffer)));
    
    projectile_buffer.clear();


    for(auto& projectile : projectiles)
    {
        projectile->update();
    }

    projectiles.erase(std::remove_if(std::begin(projectiles), std::end(projectiles),
                            [](std::unique_ptr<Projectile>& ptr)
                            {
                                return ptr->done();
                            }), end(projectiles));
}

const std::vector<std::unique_ptr<Projectile> >& ProjectileManager::get_projectiles()
{
    return projectiles;
}

void ProjectileManager::add_projectiles(std::vector <std::unique_ptr<Projectile> >&& to_add)
{
    projectile_buffer.insert(std::end(projectile_buffer), 
                       std::make_move_iterator(std::begin(to_add)),
                       std::make_move_iterator(std::end(to_add)));
}

void ProjectileManager::check_collisions(std::shared_ptr<SpaceShip> ship)
{
    for(auto& projectile : projectiles)
    {
        if(projectile->done()) continue;
        
        if(projectile->getGlobalBounds().intersects(ship->getGlobalBounds()))
        {
            // ship is enemy ship
            if(std::dynamic_pointer_cast<Enemy>(ship) != nullptr)
            {
                if(projectile->shooter())
                {
                    ship->get_hit(projectile->get_value());
                    projectile->set_done();
                }
            }
            // ship is player
            else
            {
                // projectile created by enemy
                if(!projectile->shooter())
                {
                    if(projectile->is_coin())
                    {
                        std::dynamic_pointer_cast<Player>(ship)->receive_coins(projectile->get_value());
                    }
                    else
                    {
                        ship->get_hit(projectile->get_value());
                    }
                    projectile->set_done();
                }
            }
        }
    }
}

void ProjectileManager::clear()
{
    projectiles.clear();
    projectile_buffer.clear();
}