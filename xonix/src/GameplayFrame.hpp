#pragma once

#include <array>
#include <vector>
#include <chrono>
#include <ctime>   

#include "Common.hpp"
#include "Item.hpp"
#include "Field.hpp"

namespace xon
{

class GameplayFrame
{
public:
    TimeStamp timestamp_;
    std::vector<Item> enemy_;
    Item player_;

    Field field_;

    double enemy_speed_k_;

    auto generateRandEnemySpeed() -> double;
    auto generateRandEnemyAngle() -> double;

    /**
     * @brief Added new enemy and init his
     * 
     * First always in Sea, Second always in border, next - random location
     * @return Item& Reference to added enemy
     */
    auto enemyAdd() -> Item&;

    /**
     * @brief Delete last enemy
     * 
     * @return true If success
     * @return false If not success (if enemy list was empty)
     */
    bool enemyDel();

    void initItemInSea(Item& item);
    void initItemInBorder(Item& item, bool need_run = true);
    void initPlayer();


public:
    GameplayFrame();
    GameplayFrame(const GameplayFrame& src);

    bool init(const size_t rows, const size_t cols);

    auto enemiesCbegin() const -> decltype(enemy_)::const_iterator;
    auto enemiesCend() const -> decltype(enemy_)::const_iterator;

    auto getField() const -> const Field&;

    auto getPlayer() const -> const Item&;
    void setPlayerRun(double new_angle, double new_speed) noexcept;

    auto operator=(const GameplayFrame& src) -> GameplayFrame&;

    bool moveStep(TimeStamp new_time);

    void moveReflections(const GameplayFrame& backup);

};

} // namespace xon