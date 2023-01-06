#pragma once

#include <vector>
#include <iterator>
#include <string>
#include <tuple>

using QArr = std::vector<int>;
using Idx = size_t;
using Cnt = size_t;

class VectorQSort: public QArr
{
public:
    using PartRes = std::tuple<Idx, Idx>;
protected:
    Cnt max_stage_;
    Cnt swap_count_;

    auto pivot_idx(const Idx left, const Idx right) const -> Idx;
    auto partition(const int piv, const Idx left, const Idx right) -> PartRes;
    void do_sort(const Idx &stage, const Idx &left, const Idx &right);
public:
    VectorQSort();
    VectorQSort(const std::initializer_list<int> & lst);
    VectorQSort(std::string_view str);
    void sort();
    void clear() noexcept;

    void set_string(std::string_view src);

    auto get_stat_max_stage() const -> Cnt;
    auto get_stat_swap_count() const -> Cnt;
};

std::ostream& operator<<(std::ostream & out, const VectorQSort & arr);

std::istream & operator>>(std::istream & in_str, VectorQSort & arr);