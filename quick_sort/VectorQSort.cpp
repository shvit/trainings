#include <sstream>
#include <iostream>

#include "VectorQSort.hpp"

VectorQSort::VectorQSort():
    QArr(),
    max_stage_{0U},
    swap_count_{0U}
{
}

VectorQSort::VectorQSort(const std::initializer_list<int> & lst):
    QArr{lst},
    max_stage_{0U},
    swap_count_{0U}
{
}

VectorQSort::VectorQSort(std::string_view str):
    QArr()
{
    set_string(str);
}

void VectorQSort::set_string(std::string_view src)
{
    clear();
    std::stringstream ss;
    ss << src;
    while (ss.good())
    {
        std::string word;
        ss >> word;
        if(!word.size()) continue;
        int new_item;
        try
        {
            new_item = stoi(word);
        }
        catch (const std::invalid_argument & e) 
        {
            std::cerr << "Error: Failed to convert string '" << word << "' to integer" << std::endl;
            continue;
        }
        push_back(new_item);
    }
}

void VectorQSort::clear() noexcept
{
    QArr::clear();
    max_stage_ = 0U;
    swap_count_ = 0U;

}

void VectorQSort::sort()
{
    max_stage_ = 0U;
    swap_count_ = 0U;
    if(this->size()) do_sort(0U, 0U, this->size() - 1);
}

void VectorQSort::do_sort(const Idx &stage, const Idx &left, const Idx &right)
{
    if(stage > max_stage_) max_stage_ = stage;
    if(stage > 2*this->size()) throw std::runtime_error("Failed algorithm! Too deep processing");

    if(left >= right) return;

    Idx piv_idx = pivot_idx(left, right);
    int piv = (*this)[piv_idx];

    auto [new_left, new_right] = partition(piv, left, right);

    if((new_left-left) > 1U) do_sort(stage+1U, left, new_left-1);
    if((right-new_right) > 1U) do_sort(stage+1U, new_right+1, right);
}

auto VectorQSort::pivot_idx(const Idx left, const Idx right) const -> Idx
{
    if(left > right) throw std::runtime_error("Failed left-right borders");
    if(left == right) return left;

    Idx ret = left + (std::rand() % (right-left+1));

    return ret;
}

auto VectorQSort::partition(const int piv, const Idx left, const Idx right) -> VectorQSort::PartRes
{
    if(left > right) std::runtime_error("Failed left-right borders");
    Idx new_left = left;
    Idx new_right = right; 
    while(true)
    {
        while((*this)[new_left] < piv) ++new_left;
        while((*this)[new_right] > piv) --new_right;
        if(new_left >= new_right) break;
        if((*this)[new_left] == (*this)[new_right])
        {
            ++new_left;
            --new_right;
            continue;
        }
        std::swap((*this)[new_left], (*this)[new_right]);
        ++swap_count_;
    }
    return {new_left, new_right};
}

auto VectorQSort::get_stat_max_stage() const -> Cnt
{
    return max_stage_;
}

auto VectorQSort::get_stat_swap_count() const -> Cnt
{
    return swap_count_;
}

std::ostream& operator<<(std::ostream & out, const VectorQSort & arr)
{
    std::copy(arr.cbegin(), 
              arr.cend(), 
              std::ostream_iterator<int>(out, " "));

    return out;
}

std::istream & operator>>(std::istream & in_str, VectorQSort & arr)
{
    std::string line;
    getline(in_str, line);
    arr.set_string(line);
    return in_str;
}
