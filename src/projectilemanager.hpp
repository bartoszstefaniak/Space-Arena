// Bartosz Stefaniak

#pragma once

#include "projectile.hpp"
#include "enemy.hpp"
#include "player.hpp"

/*!
    Class for managing globally projectiles(drawing them, calling update, adding to pool) using static functions.\n
    This class also manages memory allocations for projectiles.\n
*/
class ProjectileManager
{
public:
    /*!
        Adds projectiles from add_projectiles(...) calls to poll of projectiles.\n
        Calls update on projectiles in pool.\n
        Deletes projectiles with done flag set up.\n
    */
    static void update();

    /*!
        Adds projectiles to buffer which will be added to pool in update() call.\n
    */
    static void add_projectiles(std::vector <std::unique_ptr<Projectile> >&& to_add);

    /*!
        Returns const reference to projectiles vector.\n
    */
    const static std::vector< std::unique_ptr<Projectile> >& get_projectiles();

    /*!
        Checks collisions with ship. And calls appropriate function depending on projectile type and ship type.\n
    */
    static void check_collisions(std::shared_ptr<SpaceShip> ship);

    /*!
        Deletes all projectiles.\n
    */
    static void clear();


private:
    static inline std::vector < std::unique_ptr<Projectile> > projectiles;
    static inline std::vector < std::unique_ptr<Projectile> > projectile_buffer;

};