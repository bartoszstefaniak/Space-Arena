// Bartosz Stefaniak

#pragma once

/*!
    File that contains paths to files, enemy informations, const values used in game.\n
*/

#include "SFML/System.hpp"
#include <cmath>
#include <map>

const std::map<std::pair<int, int>, float> ENEMY_SPEED = {
    {{1, 1}, 2.0f},
    {{1, 2}, 4.0f},
    {{1, 3}, 5.0f},
    {{0, 0}, 8.0f}
};

const std::map<std::pair<int, int>, std::string> ENEMY_TEXURE_PATH = {
    {{1, 1}, "../assets/enemyBlack3.png"},
    {{1, 2}, "../assets/enemyBlack4.png"},
    {{1, 3}, "../assets/enemyBlack5.png"},
    {{0, 0}, "../assets/spaceShips_007.png"}
};

const std::map<std::pair<int, int>, std::string> ENEMY_LASER_PATH = {
    {{1, 1}, "../assets/laserBlue02.png"},
    {{1, 2}, "../assets/laserBlue02.png"},
    {{1, 3}, "../assets/laserBlue02.png"},
    {{0, 0}, "../assets/laserRed16.png"}
};

const std::map<std::pair<int, int>, float> ENEMY_FIRE_RATE = {
    {{1, 1}, 2.5f},
    {{1, 2}, 2.1f},
    {{1, 3}, 1.5f},
    {{0, 0}, 0.8f}
};

const std::map<std::pair<int, int>, int> ENEMY_HP = {
    {{1, 1}, 1},
    {{1, 2}, 4},
    {{1, 3}, 15},
    {{0, 0}, 400}
};

enum class States{MenuState = 0, GameState, UpgradeState, SettingsState};
enum class ABILITY_NAME{health = 0, damage, speed, fire_rate, coin_magnet};


constexpr unsigned int WINDOW_WIDTH  = 800;
constexpr unsigned int WINDOW_HEIGHT = 600;
constexpr float PROJECTILE_SPEED     = 10.0f;
constexpr float X_SCALE              = 0.75f;
constexpr float Y_SCALE              = 0.75f;
constexpr float EPS                  = 0.01;
constexpr float RAD_TO_DEG           = 57.2957795f;
constexpr float PI                   = 3.14159265359f;
constexpr float COIN_SPEED           = 2.0f;
constexpr float COIN_SCALE_X         = 0.5f;
constexpr float COIN_SCALE_Y         = 0.5f;
constexpr float LIFE_OFFSET_X        = 5.0f;
constexpr float LIFE_OFFSET_Y        = 5.0f;
constexpr float PLAYER_SPEED         = 4.0f;
constexpr float LEVEL_BAR_OFFSET_X   = 15.0f;
constexpr float ABILITY_BAR_SCALE_X  = 1.5f; 
constexpr float ABILITY_BAR_SCALE_Y  = 1.2f;
constexpr int   MAX_LIFES            = 8;
constexpr int   ABILITY_LEVELS       = 5;
constexpr int   ABILITIES            = 5;
constexpr int   BASE_HP              = 3;
constexpr int   BASE_DAMAGE          = 1;
constexpr int   EXPLOSION_FRAMES     = 9;
constexpr int   ANIMATION_FRAME_SKIP = 3;
constexpr float BASE_FIRE_RATE       = 1.5;
constexpr float BASE_COIN_MAGNET     = 200;

constexpr char TITLE[]                = "Space arena";
constexpr char PLAYER_LASER_PATH[]    = "../assets/laserGreen11.png";
constexpr char PLAYER_TEXTURE_PATH[]  = "../assets/playerShip1_green.png";
constexpr char COIN_PATH[]            = "../assets/spaceBuilding_008.png";
constexpr char LIFE_TEXTURE_PATH[]    = "../assets/playerLife1_green.png";
constexpr char COINS_FONT_PATH[]      = "../assets/kenvector_future.ttf";
constexpr char UPGRADE_BG_PATH[]      = "../assets/black.png";
constexpr char MENU_BG_TEXTURE_PATH[] = "../assets/blue.png";
constexpr char GAME_BG_PATH[]         = "../assets/darkpurple.png";
constexpr char ABILITY_BAR_ON_PATH[]  = "../assets/squareRed.png";
constexpr char ABILITY_BAR_OFF_PATH[] = "../assets/squareWhite.png";
constexpr char EXPLOSION_ANIM_PATH[]  = "../assets/regularExplosion"; 

constexpr std::array<std::array<int, ABILITY_LEVELS>, ABILITIES> ABILITY_COST = {
        std::array<int, ABILITY_LEVELS>({0, 25, 75, 150, 300}),
        std::array<int, ABILITY_LEVELS>({0, 25, 75, 150, 300}),
        std::array<int, ABILITY_LEVELS>({0, 25, 75, 150, 300}),
        std::array<int, ABILITY_LEVELS>({0, 25, 75, 150, 300}),
        std::array<int, ABILITY_LEVELS>({0, 25, 75, 150, 300})
    };

constexpr std::array<std::array<float, ABILITY_LEVELS>, ABILITIES> ABILITY_VALUE = {
    std::array<float, ABILITY_LEVELS>({BASE_HP, BASE_HP + 1, BASE_HP + 2, BASE_HP + 3, BASE_HP + 4}),
    std::array<float, ABILITY_LEVELS>({BASE_DAMAGE, BASE_DAMAGE + 2, BASE_DAMAGE + 6, BASE_DAMAGE + 11, BASE_DAMAGE + 20}),
    std::array<float, ABILITY_LEVELS>({PLAYER_SPEED, PLAYER_SPEED + 1, PLAYER_SPEED + 2, PLAYER_SPEED + 3, PLAYER_SPEED + 4}),
    std::array<float, ABILITY_LEVELS>({BASE_FIRE_RATE, BASE_FIRE_RATE - 0.3f, BASE_FIRE_RATE - 0.6f, BASE_FIRE_RATE - 0.9f, 0.0f}),
    std::array<float, ABILITY_LEVELS>({BASE_COIN_MAGNET, BASE_COIN_MAGNET + 100.0f, BASE_COIN_MAGNET + 200.0f, BASE_COIN_MAGNET + 350.0f, BASE_COIN_MAGNET + 500.0f})
};

// "kenney_spaceshooterextension/PNG/Sprites/Building/spaceBuilding_005.png";