#include <cmath>

#include "Item.hpp"
#include "Field.hpp"

namespace xon
{

auto Item::calcDistance(const Item& chk) const -> double
{
    return calcDistance(chk.row, chk.col);
}

auto Item::calcDistance(const double chk_row, const double chk_col) const -> double
{
    return sqrt(std::pow(row - chk_row, 2) + std::pow(col - chk_col, 2));
}

bool Item::checkAround(const double chk_row, const double chk_col, const double dist)
{
    return calcDistance(chk_row, chk_col) < dist;
}

bool Item::checkAround(const Item& chk, const double dist)
{
    return checkAround(chk.row, chk.col, dist);
}

auto Item::operator=(const Item& src) -> Item&
{
    diameter = src.diameter;
    row = src.row;
    col = src.col;
    speed = src.speed;
    angle = src.angle;

    return *this;
}

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

double Item::normalizeAngle(const double curr_ang) const
{
    double ret = curr_ang;

    if(ret > 360.0) ret -= 360.0;
    if(ret < 0.0) ret += 360.0;

    return ret;
}


void Item::move(TimeInterval ti, const Field& fld, bool is_bot)
{
    double dist = speed * ti.count();
    double d_row = dist * cos(angle * 2.0 * M_PI / 360.0);
    double d_col = dist * sin(angle * 2.0 * M_PI / 360.0);
    double new_row = row - d_row;
    double new_col = col + d_col;
    double new_speed = speed;
    double new_angle = angle;

    //DEBUG("Move on distance "<<dist<<" (speed="<<speed<<", time="<<ti.count()<<") from [R:"<<row<<",C:"<<col<<"] to [R:"<<new_row<<",C:"<<new_col<<"]");

    if(is_bot)
    {
        if(fld.isInsideSea(row, col))
        {
            // Enemy on field
            if(!fld.isInsideSea(new_row, new_col))
            {
                if(new_row < fld.getSeaRowBegin()) { new_row = row + abs(d_row); new_angle = mirrorHorizontal(new_angle); }
                if(new_row > fld.getSeaRowEnd())   { new_row = row - abs(d_row); new_angle = mirrorHorizontal(new_angle); }
                if(new_col < fld.getSeaColBegin()) { new_col = col + abs(d_row); new_angle = mirrorVertical(new_angle); }
                if(new_col > fld.getSeaColEnd())   { new_col = col - abs(d_col); new_angle = mirrorVertical(new_angle); }

                //check (never do it)
                if (!fld.isInsideSea(new_row, new_col)) ERROR("Lost enemy - out of world (R:"<<row<<", C:"<<col<<") ---> (dR:"<<d_row<<", dC:"<<d_col<<") ---> "<<"---> (R:"<<new_row<<", C:"<<new_col<<")");
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

    row=new_row;
    col=new_col;
    speed = new_speed;
    angle = new_angle;
}


} // namespace xon