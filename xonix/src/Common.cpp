#include <ctime>   
#include <limits>
#include <cmath>

#include "Common.hpp"
#include "Item.hpp"

namespace xon
{

void RandInit()
{
    std::srand(std::time(nullptr));
}

auto RandDbl() -> double
{
    double ret = (double)std::rand() / RAND_MAX;
    return ret;
}

bool RandBool() 
{
    return RandDbl() > 0.5;
}

auto normalizeAngle(const WorldCoord curr_angle) -> WorldCoord
{
    WorldCoord ret = curr_angle;
    WorldCoord range_up = 360.0 + 360 * std::numeric_limits<WorldCoord>::epsilon();
    WorldCoord range_down = -360.0 * std::numeric_limits<WorldCoord>::epsilon();
    while(ret > range_up) ret -= 360.0;
    while(ret < range_down) ret += 360.0;

    return ret;
}

auto round(const WorldCoord val) -> IntWorldCoord
{
    return std::lround(val);
}

auto round(const Point& val) -> IntPoint
{
    IntWorldCoord row = round(std::get<0>(val));
    IntWorldCoord col = round(std::get<1>(val));
    return {row, col};
}

auto round(const Item& val) -> IntPoint
{
    IntWorldCoord row = round(val.getRow());
    IntWorldCoord col = round(val.getCol());
    return {row, col};
}

auto operator<<(std::ostream& stream, const WorldCoordList& lst) -> std::ostream&
{
    stream << "{";
    for(size_t iter = 0U; iter < lst.size(); ++iter)
    {
        if(iter) stream << ",";
        stream << lst[iter];
    }
    stream << "}";
    return stream;
}

auto arithmeticMean(const WorldCoordList& lst) -> WorldCoord
{
    WorldCoord ret = 0.0;
    for(size_t iter = 0U; iter < lst.size(); ++iter) ret += lst[iter];
    ret /= (double)lst.size();

    return ret;
}


} // namespace xon