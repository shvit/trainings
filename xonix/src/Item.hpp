#pragma once

#include <cstddef>

#include "Common.hpp"

namespace xon
{

/**
 * @brief 
 * 
 *  Speed: points in second
 *  Angle: 0...360 degree
 *            0/360
 *       270    X     90
 *             180
 */
class Item
{
protected:

    double mirrorVertical(const double curr_ang) const;
    double mirrorHorizontal(const double curr_ang) const;
    double normalizeAngle(const double curr_ang) const;

public:
    double diameter;
    double row;
    double col;
    double speed;
    double angle;

    auto calcDistance(const Item& chk) const -> double;
    auto calcDistance(const double chk_row, const double chk_col) const -> double;

    bool checkAround(const double chk_row, const double chk_col, const double dist);
    bool checkAround(const Item& chk, const double dist);

    auto operator=(const Item& src) -> Item&;

    void move(TimeInterval ti, const Field& fld, bool is_bot = true);

};



} // namespace xon
