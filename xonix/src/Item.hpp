#pragma once

#include <cstddef>

#include "Common.hpp"

namespace xon
{

/**
 * @brief Class for any xonix items (enemy/player)
 * 
 *  Speed: points in second (default 0)
 *  Angle: 0...360 degree (default 0)
 *            0/360
 *       270    X     90
 *             180
 *  Diasmeter: 1 point by default
 */
class Item
{
protected:
    WorldCoord diameter_;
    WorldCoord row_;
    WorldCoord col_;
    WorldCoord speed_;
    WorldCoord angle_;

    double mirrorVertical(const double curr_ang) const;
    double mirrorHorizontal(const double curr_ang) const;
    double normalizeAngle(const double curr_ang) const;

public:

    /** @brief Default constructor
     */
    Item();

    Item(const Item& src);

    /** @brief Default destructor
     */
    ~Item();

    void initPosition(WorldCoord row, WorldCoord col, WorldCoord diameter = default_enemy_diameter) noexcept;
    void initDynamic(WorldCoord speed, WorldCoord angle) noexcept;


    auto calcDistanceCenter(const Item& other) const -> double;
    auto calcDistanceSurface(const Item& other) const -> double;

    auto operator=(const Item& src) noexcept -> Item&;

    //void move(TimeInterval ti, const Field& fld, bool is_bot = true);

    /**
     * @brief Getter for coordinate row
     * 
     * @return WorldCoord Value
     */
    auto getRow() const -> WorldCoord;

    /**
     * @brief Getter for coordinate column
     * 
     * @return WorldCoord Value
     */
    auto getCol() const -> WorldCoord;

    /**
     * @brief Getter for diameter of item
     * 
     * @return WorldCoord Value
     */
    auto getDiameter() const -> WorldCoord;

    /**
     * @brief Getter for speed of item
     * 
     * @return WorldCoord Value
     */
    auto getSpeed() const -> WorldCoord;

    /**
     * @brief Getter for angle of item
     * 
     * @return WorldCoord Value
     */
    auto getAngle() const -> WorldCoord;
    
    /**
     * @brief Calculate distance between points
     * 
     * @param right [in] Other point
     * @return double Distance
     */
    auto operator-(const Item& right) const -> WorldCoord;

    /**
     * @brief Calculate next position after time
     * 
     * @param ti Time distance
     * @return Item New position item
     */
    auto operator*(const TimeInterval ti) const -> Item;

    auto operator*=(const TimeInterval ti) -> Item&;

    void reflectByTangent(const WorldCoord tangent);

    void reflectByNormale(const WorldCoord normale);

    operator Point() const;
};

/**
 * @brief Output stream operator for Item
 * 
 * @param str Output stream
 * @param val Item value
 * @return std::ostream& Output stream
 */
auto operator<<(std::ostream& str, const Item& val) -> std::ostream&;

} // namespace xon
