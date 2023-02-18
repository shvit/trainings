#include <cmath>

#include "Item.hpp"
#include "Field.hpp"

namespace xon
{

Item::Item():
    diameter_{1},
    row_{0},
    col_{0},
    speed_{0},
    angle_{0}
{
}

Item::Item(const Item& src):
    Item()
{
    operator=(src);
    //initPosition(src.row_, src.col_, src.diameter_);
    //initDynamic(src.speed_, src.angle_);
}

Item::~Item()
{
}

void Item::initPosition(WorldCoord row, WorldCoord col, WorldCoord diameter) noexcept
{
    row_ = row;
    col_ = col;
    diameter_ = diameter;
}

void Item::initDynamic(WorldCoord speed, WorldCoord angle) noexcept
{
    speed_ = speed;
    angle_ = angle;
}

auto Item::operator=(const Item& src) noexcept -> Item&
{
    diameter_ = src.diameter_;
    row_ = src.row_;
    col_ = src.col_;
    speed_ = src.speed_;
    angle_ = src.angle_;

    return *this;
}

/*
double Item::mirrorVertical(const double curr_ang) const
{
    double new_ang = 360.0 - curr_ang;
    return normalizeAngle(new_ang);
}

double Item::mirrorHorizontal(const double curr_ang) const
{
    double new_ang = 180.0 - curr_ang;
    return normalizeAngle(new_ang);
}
*/
//double Item::normalizeAngle(const double curr_ang) const
//{
//    double ret = curr_ang;
//
//    if(ret > 360.0) ret -= 360.0;
//    if(ret < 0.0) ret += 360.0;

//    return ret;
//}

/*
void Item::move(TimeInterval ti, const Field& fld, bool is_bot)
{
    double dist = speed_ * ti.count();
    double d_row = dist * cos(angle_ * 2.0 * M_PI / 360.0);
    double d_col = dist * sin(angle_ * 2.0 * M_PI / 360.0);
    double new_row = row_ - d_row;
    double new_col = col_ + d_col;
    double new_speed = speed_;
    double new_angle = angle_;

    //DEBUG("Move on distance "<<dist<<" (speed="<<speed<<", time="<<ti.count()<<") from [R:"<<row<<",C:"<<col<<"] to [R:"<<new_row<<",C:"<<new_col<<"]");

    if(is_bot)
    {
        if(fld.isInsideSea(row_, col_))
        {
            // Enemy on field
            if(!fld.isInsideSea(new_row, new_col))
            {
                if(new_row < fld.getSeaRowBegin()) { new_row = row_ + abs(d_row); new_angle = mirrorHorizontal(new_angle); }
                if(new_row > fld.getSeaRowEnd())   { new_row = row_ - abs(d_row); new_angle = mirrorHorizontal(new_angle); }
                if(new_col < fld.getSeaColBegin()) { new_col = col_ + abs(d_row); new_angle = mirrorVertical(new_angle); }
                if(new_col > fld.getSeaColEnd())   { new_col = col_ - abs(d_col); new_angle = mirrorVertical(new_angle); }

                //check (never do it)
                if (!fld.isInsideSea(new_row, new_col)) ERROR("Lost enemy - out of world (R:"<<row_<<", C:"<<col_<<") ---> (dR:"<<d_row<<", dC:"<<d_col<<") ---> "<<"---> (R:"<<new_row<<", C:"<<new_col<<")");
            }
        }
        else
        {
            // Enemy on border
            if(!fld.isOnBorder(new_row, new_col))
            {
                
            }

        }
    }
    else
    {
        if(!fld.isInsideWorld(new_row, new_col))
        {
            if(new_row < fld.getWorldRowBegin()) new_row = (double)fld.get_world_row_begin();
            if(new_row > fld.getWorldRowEnd())   new_row = (double)fld.get_world_row_end();
            if(new_col < fld.getWorldColBegin()) new_col = (double)fld.get_world_col_begin();
            if(new_col > fld.getWorldColEnd())   new_col = (double)fld.get_world_col_end();
            new_speed = 0.0;

            //check (never do it)
            if (!fld.isInsideWorld(new_row, new_col)) ERROR("Player out of world (R:"<<new_row<<", C:"<<new_col<<")");
        }
    }

    row_=new_row;
    col_=new_col;
    speed_ = new_speed;
    angle_ = new_angle;
}
*/
//--------------------------------------------------------------------------------------

auto Item::getRow() const -> WorldCoord
{
    return row_;
}

auto Item::getCol() const -> WorldCoord
{
    return col_;
}

auto Item::getDiameter() const -> WorldCoord
{
    return diameter_;
}

auto Item::getSpeed() const -> WorldCoord
{
    return speed_;
}

auto Item::getAngle() const -> WorldCoord
{
    return angle_;
}
//--------------------------------------------------------------------------------------

auto Item::calcDistanceCenter(const Item& other) const -> double
{
    return sqrt(std::pow(row_ - other.row_, 2) + 
                std::pow(col_ - other.col_, 2));
}

auto Item::calcDistanceSurface(const Item& other) const -> double
{
    return calcDistanceCenter(other) - (diameter_ / 2) - (other.diameter_ / 2);
}

//--------------------------------------------------------------------------------------

auto Item::operator-(const Item& right) const -> WorldCoord
{
    return calcDistanceSurface(right);
}

//--------------------------------------------------------------------------------------

auto Item::operator*=(const TimeInterval ti) -> Item&
{
    double dist = speed_ * ti.count();
    double d_row = dist * cos(angle_ * 2.0 * M_PI / 360.0);
    double d_col = dist * sin(angle_ * 2.0 * M_PI / 360.0);
    row_ -= d_row;
    col_ += d_col;

    return *this;
}

auto Item::operator*(const TimeInterval ti) const -> Item
{
    Item new_item{*this};
    new_item *= ti;

    return new_item;
}

void Item::reflectByTangent(const WorldCoord tangent)
{
    angle_ = normalizeAngle(2.0 * tangent - angle_);
}

void Item::reflectByNormale(const WorldCoord normale)
{
    reflectByTangent(normale + 90.0);
}

Item::operator Point() const
{
    return {row_, col_};
}

//--------------------------------------------------------------------------------------

auto operator<<(std::ostream& str, const Item& val) -> std::ostream&
{
    str << "(R:" << val.getRow() << 
           ",C:" << val.getCol() << 
           ",D:"<< val.getDiameter() << 
           ",A:" << val.getAngle() << 
           ",S:" << val.getSpeed() << ")";
    return str;
}

} // namespace xon