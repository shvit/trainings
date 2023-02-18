#pragma once

#include <iostream>
#include <iomanip>
#include <chrono>
#include <sstream>
#include <syslog.h>
#include <tuple>

namespace xon
{

using TimeStamp = std::chrono::time_point<std::chrono::system_clock>;
using TimeInterval = std::chrono::duration<double>;

using IntWorldIndex = long;
using IntWorldPoint = std::tuple<IntWorldIndex, IntWorldIndex>;

constexpr IntWorldIndex rows_minimal = 10;
constexpr IntWorldIndex rows_maximal = 256;
constexpr IntWorldIndex cols_minimal = 20;
constexpr IntWorldIndex cols_maximal = 256;

constexpr IntWorldIndex minimal_border = 3;

constexpr size_t default_enemy_count = 20U;

constexpr double default_player_speed = 10.0;

constexpr double default_enemy_speed_k = 3.0; ///< Duration for enemy speed (from player/k to player*k)

constexpr double init_collision_distance = 3.0; ///< Collision distance for enemies (for player *=2)

class Field;
class Item;
class Gameplay;
class GameplayFrame;
class Render;
class Game;

enum class CellValue: char
{
    empty,        ///< Sea
    base,         ///< Land
    property,     ///< Path
    fill1,        ///< investigated stage 1
    fill2,        ///< investigated stage 2
};

/**
 * @brief Radomize pseudo rand() from current time
 * 
 */
void RandInit();

/**
 * @brief Get randomized value 0...1
 * 
 * @return double Randomized value
 */
auto RandDbl() -> double;

/**
 * @brief Get random boolean value
 * 
 * @return true/false randomized
 */
bool RandBool();



} // namespace xon

#define LOG_MESSAGE(TYPE, MSG) \
{\
    std::stringstream ss;\
    ss << MSG;\
    syslog(LOG_##TYPE, "[%s] %s(): %s", #TYPE, __func__, ss.str().c_str());\
}

#define DEBUG(MSG) LOG_MESSAGE(DEBUG, MSG);
#define INFO(MSG) LOG_MESSAGE(INFO, MSG);
#define NOTICE(MSG) LOG_MESSAGE(NOTICE, MSG);
#define WARNING(MSG) LOG_MESSAGE(WARNING, MSG);
#define ERROR(MSG) LOG_MESSAGE(ERR, MSG);

