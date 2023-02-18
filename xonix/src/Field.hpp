#pragma once

#include <algorithm>
#include <tuple>

#include "Common.hpp"


namespace xon
{

class Field
{
public:

protected:
    size_t rows_{rows_minimal};
    size_t cols_{cols_minimal};
    size_t border_{minimal_border};
    CellValue field_[rows_maximal][cols_maximal];

public:
    Field();
    bool is_valid();
    bool set_new_size(int rows, int cols);
    bool set_new_size(int rows, int cols, int border);
    void init();

    auto normalizeIntPoint(const double curr_row, const double curr_col) const -> IntWorldPoint;

    auto get_size() -> std::tuple<size_t, size_t>;

    auto get_rows() const -> size_t;
    auto get_cols() const -> size_t;
    auto get_border() const -> size_t;

    auto getRowsDbl() const -> double;
    auto getColsDbl() const -> double;
    auto getBorderDbl() const -> double;

    auto get_world_row_begin() const -> IntWorldCoord;
    auto get_world_row_end() const -> IntWorldCoord;
    auto get_world_col_begin() const -> IntWorldCoord;
    auto get_world_col_end() const -> IntWorldCoord;

    auto get_sea_row_begin() const -> IntWorldCoord;
    auto get_sea_row_end() const -> IntWorldCoord;
    auto get_sea_col_begin() const -> IntWorldCoord;
    auto get_sea_col_end() const -> IntWorldCoord;

    auto getWorldRowBegin() const -> double;
    auto getWorldRowEnd() const -> double;
    auto getWorldColBegin() const -> double;
    auto getWorldColEnd() const -> double;

    auto getSeaRowBegin() const -> double;
    auto getSeaRowEnd() const -> double;
    auto getSeaColBegin() const -> double;
    auto getSeaColEnd() const -> double;


    auto getChar(const IntWorldCoord, const IntWorldCoord) const -> CellValue;

    auto operator=(const Field& src) -> Field&;

    bool isInsideWorld(const double curr_row, const double curr_col) const;

    bool isInsideSea(const double curr_row, const double curr_col) const;
    bool isInsideLand(const double curr_row, const double curr_col) const;

    bool isOnBorder(const double curr_row, const double curr_col) const;

    bool isInsideSea(const Item& val) const;

    auto getCollisionNormale(const Item& val, bool ref_sea = false, bool ref_land = false) const -> WorldCoordList;

};

} // namespace xon