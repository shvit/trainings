//#pragma once

#include <vector>
#include <iterator>
#include <string>
#include <tuple>
#include <optional>
#include <math.h>

using Idx = size_t;
using Cnt = size_t;

template<typename T>
class VectorQSort: public std::vector<T>
{
public:
    using PartRes = std::tuple<Idx, Idx>;
protected:
    Cnt max_stage_{0U};
    Cnt swap_count_{0U};

    auto pivot_idx(const Idx left, const Idx right) const -> Idx;
    auto partition(const T piv, const Idx left, const Idx right) -> PartRes;
    void do_sort(const Idx &stage, const Idx &left, const Idx &right);
    auto value_from_string(const std::string & val) -> std::optional<T>;
    bool eqv(const Idx index, const T& value) const;
    bool less(const Idx index, const T& value) const;
    bool more(const Idx index, const T& value) const;
public:
    using std::vector<T>::vector;

    VectorQSort(std::string_view str);
    void sort();
    void clear() noexcept;

    void set_string(std::string_view src);

    auto get_stat_max_stage() const -> Cnt;
    auto get_stat_swap_count() const -> Cnt;
};

template<typename T>
std::ostream& operator<<(std::ostream & out, const VectorQSort<T> & arr);

template<typename T>
std::istream & operator>>(std::istream & in_str, VectorQSort<T> & arr);

//---------------------------------------------------------------------------

template<typename T>
VectorQSort<T>::VectorQSort(std::string_view str):
    std::vector<T>()
{
    set_string(str);
}

template<typename T>
auto VectorQSort<T>::pivot_idx(const Idx left, const Idx right) const -> Idx
{
    if(left > right) throw std::runtime_error("Failed left-right borders");
    if(left == right) return left;

    Idx ret = left + (std::rand() % (right-left+1));

    return ret;
}

template<typename T>
auto VectorQSort<T>::partition(const T piv, const Idx left, const Idx right) -> PartRes
{
    if(left > right) std::runtime_error("Failed left-right borders");
    Idx new_left = left;
    Idx new_right = right; 
    while(true)
    {
        while(less(new_left, piv)) ++new_left;
        while(more(new_right, piv)) --new_right;
        if(new_left >= new_right) break;
        if(eqv(new_left, (*this)[new_right]))
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

template<typename T>
void VectorQSort<T>::do_sort(const Idx &stage, const Idx &left, const Idx &right)
{
    if(stage > max_stage_) max_stage_ = stage;
    if(stage > 2*this->size()) throw std::runtime_error("Failed algorithm! Too deep processing");

    if(left >= right) return;

    Idx piv_idx = pivot_idx(left, right);
    T piv{(*this)[piv_idx]};

    auto [new_left, new_right] = partition(piv, left, right);

    if((new_left-left) > 1U) do_sort(stage+1U, left, new_left-1);
    if((right-new_right) > 1U) do_sort(stage+1U, new_right+1, right);
}

template<typename T>
void VectorQSort<T>::sort()
{
    max_stage_ = 0U;
    swap_count_ = 0U;
    if(this->size()) do_sort(0U, 0U, this->size() - 1);
}

template<typename T>
void VectorQSort<T>::clear() noexcept
{
    std::vector<T>::clear();
    max_stage_ = 0U;
    swap_count_ = 0U;
}

template<typename T>
void VectorQSort<T>::set_string(std::string_view src)
{
    clear();
    std::stringstream ss;
    ss << src;
    while (ss.good())
    {
        std::string word;
        ss >> word;
        if(!word.size()) continue;
        auto new_item = value_from_string(word);
        if(new_item.has_value())
        {
            std::vector<T>::push_back(new_item.value());
        }
        else
        {
            std::cerr << "Error: Failed to convert string '" << word << "' to internal type" << std::endl;
        }
    }
}

template<typename T>
auto VectorQSort<T>::get_stat_max_stage() const -> Cnt
{
    return max_stage_;
}

template<typename T>
auto VectorQSort<T>::get_stat_swap_count() const -> Cnt
{
    return swap_count_;
}

template<typename T>
auto VectorQSort<T>::value_from_string(const std::string& val) -> std::optional<T>
{
    std::optional<T> ret_val;
    try
    {
        if constexpr (std::is_integral_v<T>)
        {
            if constexpr (std::is_signed_v<T>)
            {
                ret_val = (T)stoll(val);
            }
            else
            {
                ret_val = (T)stoull(val);
            }
        }
        else
        if constexpr (std::is_floating_point_v<T>)
        {
            ret_val = (T)stold(val);
        }
        else
        if constexpr (std::is_constructible_v<T, std::string>)
        {
            ret_val = T{val};
        }
    }
    catch(const std::exception& e)
    {
        ret_val.reset();
    }

    return ret_val;
}

template<typename T>
bool VectorQSort<T>::eqv(const Idx index, const T& value) const
{
    if constexpr (std::is_floating_point_v<T>)
    {
        constexpr int ulp = 2;
        return fabsl((*this)[index] - value) <= std::numeric_limits<T>::epsilon() * fabsl((*this)[index] + value) * ulp ||
               fabsl((*this)[index] - value) < std::numeric_limits<T>::min();
    }
    else
    {
        return (*this)[index] == value;
    }
}

template<typename T>
bool VectorQSort<T>::less(const Idx index, const T& value) const
{
    return !eqv(index, value) && ((*this)[index] < value);
}

template<typename T>
bool VectorQSort<T>::more(const Idx index, const T& value) const
{
    return !eqv(index, value) && ((*this)[index] > value);
}

//------------------------------------------------------------------------

template<typename T>
std::ostream& operator<<(std::ostream & out, const VectorQSort<T> & arr)
{
    std::copy(arr.cbegin(), 
              arr.cend(), 
              std::ostream_iterator<T>(out, " "));

    return out;
}

template<typename T>
std::istream & operator>>(std::istream & in_str, VectorQSort<T> & arr)
{
    std::string line;
    getline(in_str, line);
    arr.set_string(line);
    return in_str;
}
