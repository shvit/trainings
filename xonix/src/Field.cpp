#include <cassert>
#include <cmath>
#include <vector>

#include "Field.hpp"
#include "Item.hpp"

namespace xon
{

static_assert(minimal_border > 1, "Minimal border width (base_border) is wrong");
static_assert(rows_minimal > (minimal_border*2+2), "Minimal dimension (rows_minimal) is wrong");
static_assert(cols_minimal > (minimal_border*2+2), "Minimal dimension (cols_minimal) is wrong");

Field::Field()
{
}

bool Field::is_valid()
{
    return (rows_ >= rows_minimal) && (cols_ >= cols_minimal) &&
            (rows_ >= (border_*2+2)) &&
            (cols_ >= (border_*2+2));
}

bool Field::set_new_size(int rows, int cols, int border)
{
    rows_ = rows;
    cols_ = cols;

    if(!is_valid()) return false;

    init();

    return true;
}

bool Field::set_new_size(int rows, int cols)
{
    return set_new_size(rows, cols, minimal_border);
}

auto Field::get_size() -> std::tuple<size_t, size_t>
{
    return {rows_, cols_};
}

auto Field::get_rows() const -> size_t
{
    return rows_;
}

auto Field::get_cols() const -> size_t
{
    return cols_;
}

auto Field::get_border() const -> size_t
{
    return border_;
}

auto Field::getRowsDbl() const -> double
{
    return (double)rows_;
}

auto Field::getColsDbl() const -> double
{
    return (double)cols_;
}

auto Field::getBorderDbl() const -> double
{
    return (double)border_;
}

auto Field::getChar(const IntWorldCoord row, const IntWorldCoord col) const -> CellValue
{
    if((row < get_world_row_begin()) ||
       (row > get_world_row_end()) ||
       (col < get_world_col_begin()) ||
       (col > get_world_col_end()))
    {
        return CellValue::monolith;
    }
    else
    {
        return field_[row][col];
    }
}

void Field::init()
{
    std::fill(&field_[0U][0U], 
              &field_[0U][0U] + rows_maximal*cols_maximal,
              CellValue::sea);

    if(is_valid())
    {
        // Make borders
        for(size_t row = 0U; row < border_; ++row)
        {
            std::fill(&field_[row][0U], &field_[row][cols_], CellValue::land);

            size_t row_down = rows_ - row - 1U;
            std::fill(&field_[row_down][0U], &field_[row_down][cols_], CellValue::land);
        }
        for(size_t row = border_; row <= (rows_ - border_); ++row)
        {
            std::fill(&field_[row][0U], &field_[row][border_], CellValue::land);
            std::fill(&field_[row][cols_ - border_], &field_[row][cols_], CellValue::land);
        }
    }
              
}

auto Field::operator=(const Field& src) -> Field&
{
    rows_ = src.rows_;
    cols_ = src.cols_;
    border_ = src.border_;
    std::copy(&src.field_[0][0], &src.field_[0][0] + rows_maximal*cols_maximal, &field_[0][0]);

    return *this;
}

//--------------------------------------------------------------------------------------

bool Field::isInsideWorld(const double curr_row, const double curr_col) const
{
    return (curr_row > getWorldRowBegin()) && (curr_row < getWorldRowEnd()) &&
           (curr_col > getWorldColBegin()) && (curr_col < getWorldColEnd());
}

bool Field::isInsideSea(const double curr_row, const double curr_col) const
{
    auto [int_row, int_col] = normalizeIntPoint(curr_row, curr_col);

    return field_[int_row][int_col] != CellValue::land;
}

bool Field::isInsideLand(const double curr_row, const double curr_col) const
{
    auto [int_row, int_col] = normalizeIntPoint(curr_row, curr_col);

    return field_[int_row][int_col] != CellValue::sea;
}

bool Field::isOnBorder(const double curr_row, const double curr_col) const
{
    return isInsideWorld(curr_row, curr_col) && !isInsideSea(curr_row, curr_col);
}

bool Field::isInsideSea(const Item& val) const
{
    return isInsideSea(val.getRow(), val.getCol());
}

//--------------------------------------------------------------------------------------

auto Field::get_world_row_begin() const -> IntWorldCoord
{
    return 0U;
}
auto Field::get_world_row_end() const -> IntWorldCoord
{
    assert(rows_ > 0U);
    return rows_ - 1U;
}
auto Field::get_world_col_begin() const -> IntWorldCoord
{
    return 0U;
}
auto Field::get_world_col_end() const -> IntWorldCoord
{
    assert(cols_ > 0U);
    return cols_ - 1U;
}

auto Field::get_sea_row_begin() const -> IntWorldCoord
{
    assert(rows_ > border_);
    return get_world_row_begin() + border_;
}

auto Field::get_sea_row_end() const -> IntWorldCoord
{
    assert((rows_ > 0U) && (rows_ > border_));
    return rows_ - border_ - 1U;
}

auto Field::get_sea_col_begin() const -> IntWorldCoord
{
    assert(cols_ > border_);
    return get_world_col_begin() + border_;
}

auto Field::get_sea_col_end() const -> IntWorldCoord
{
    assert((cols_ > 0U) && (cols_ > border_));
    return cols_ - border_ - 1U;
}

//--------------------------------------------------------------------------------------

auto Field::getWorldRowBegin() const -> double
{
    return (double)get_world_row_begin() - 0.49;
}
auto Field::getWorldRowEnd() const -> double
{
    return (double)get_world_row_end() + 0.49;
}
auto Field::getWorldColBegin() const -> double
{
    return (double)get_world_col_begin() - 0.49;
}
auto Field::getWorldColEnd() const -> double
{
    return (double)get_world_col_end() + 0.49;
}

auto Field::getSeaRowBegin() const -> double
{
    return (double)get_sea_row_begin() - 0.49;
}
auto Field::getSeaRowEnd() const -> double
{
    return (double)get_sea_row_end() + 0.49;;
}
auto Field::getSeaColBegin() const -> double
{
    return (double)get_sea_col_begin() - 0.49;
    
}
auto Field::getSeaColEnd() const -> double
{
    return (double)get_sea_col_end() + 0.49;;
}

//--------------------------------------------------------------------------------------

auto Field::normalizeIntPoint(const double curr_row, const double curr_col) const -> IntWorldPoint
{
    IntWorldIndex int_row = std::lround(curr_row);
    IntWorldIndex int_col = std::lround(curr_col);

    if(IntWorldIndex tmp_val = get_world_row_begin(); int_row < tmp_val) int_row = tmp_val;
    if(IntWorldIndex tmp_val = get_world_row_end();   int_row > tmp_val) int_row = tmp_val;
    if(IntWorldIndex tmp_val = get_world_col_begin(); int_col < tmp_val) int_col = tmp_val;
    if(IntWorldIndex tmp_val = get_world_col_end();   int_col > tmp_val) int_col = tmp_val;

    return {int_row, int_col};
}

auto Field::getCollisionNormale(const Item& item, bool ref_sea, bool ref_land) const -> WorldCoordList
{
    //WorldCoordOpt ret;

    auto [row, col] = round(item);
    auto diam = round(item.getDiameter() + 0.49);
    std::vector<WorldCoord> collised_angles;

    for(IntWorldCoord d = 0; d <= diam; ++d)
    {
        for(IntWorldCoord r = row - d; r <= row + d; ++r)
        {
            for(IntWorldCoord c = col - d; c <= col + d; ++c)
            {
                if((getChar(r, c) == CellValue::monolith) ||
                   (ref_sea  && (getChar(r, c) == CellValue::sea)) ||
                   (ref_land && (getChar(r, c) == CellValue::land)))
                {
                    WorldCoord d_row = (WorldCoord)r - item.getRow();
                    WorldCoord d_col = (WorldCoord)c - item.getCol();
                    WorldCoord alphaRad = std::atan2(d_row, d_col);
                    WorldCoord chk_row = item.getRow() + (item.getDiameter() / 2) * sin(alphaRad);
                    WorldCoord chk_col = item.getCol() + (item.getDiameter() / 2) * cos(alphaRad);
                    if((((WorldCoord)r - chk_row) < 0.5) && 
                       (((WorldCoord)c - chk_col) < 0.5))
                    { // collision
                        collised_angles.emplace_back(180.0 * alphaRad / M_PI);
                    }
                }
            }
        }

        if(collised_angles.size()) // no more
        {
            DEBUG("Collised angles [d=" << d << "] for item " << item << ": " << collised_angles)
            break; 
        }
    }

    return collised_angles;
}


} // namespace xon