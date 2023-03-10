#include <boost/test/unit_test.hpp>
#include <iostream>
#include <iomanip>

#include "test.hpp"
#include "../VectorQSort.hpp"

BOOST_AUTO_TEST_SUITE(Common)

template<typename T>
class test_VectorQSort: public VectorQSort<T>
{
public:
    size_t iteration{0U};
    auto pivot_idx(const Idx left, const Idx right) const -> Idx
    {
        if(left > right) throw std::runtime_error("Failed left-right borders");
        if(left == right) return left;
        if((left == 0U) && (right == (std::vector<T>::size()-1U)))
        {
            return iteration;
        }
        return left + (std::rand() % (right-left+1));
    }

    using VectorQSort<T>::VectorQSort;
    using VectorQSort<T>::eqv;
};

BOOST_AUTO_TEST_CASE(SortedVectors)
{
    #define CHK_ONE(LEFT, RIGHT, MSG, ARR) \
        BOOST_CHECK_MESSAGE((LEFT)==(RIGHT),\
                            "Failed " MSG " (current "+std::to_string(LEFT)+" need "+std::to_string(RIGHT)+"); Array is '"+ARR+"'");\
        ++unit_tests::counter_checks;

    #define CHK_VECTOR(CNT, ...) \
        {\
            VectorQSort<int> arr{__VA_ARGS__};\
            CHK_ONE(arr.size(), CNT, "count of elements", #__VA_ARGS__);\
            CHK_ONE(arr.get_stat_max_stage(), 0U, "clean 'deep' statistic", #__VA_ARGS__);\
            CHK_ONE(arr.get_stat_swap_count(), 0U, "clean 'swap' statistic", #__VA_ARGS__);\
            std::vector et_vec{arr};\
            arr.sort();\
            std::sort(et_vec.begin(), et_vec.end());\
            for(size_t idx=0U; idx<arr.size(); ++idx)\
            {\
                CHK_ONE(arr[idx], et_vec[idx], "sorted element["+std::to_string(idx)+"]", #__VA_ARGS__);\
            }\
        }

    CHK_VECTOR(15, 100, 0, 9, 8, 7, 6, 5, 4, 3, 2, 1, 3, 99, -10, -50)
    CHK_VECTOR(15, "100 0 9 8 7 6 5 4 3 2 1 3 99 -10 -50")
    CHK_VECTOR(1, 1)
    CHK_VECTOR(1, "1")
    CHK_VECTOR(0, )
    CHK_VECTOR(0, "")
    CHK_VECTOR(5, 5, 4, 3, 2, 1)
    CHK_VECTOR(5, "5 4 3 2 1")
    CHK_VECTOR(5, -100, -100, 100, 100, 0)
    CHK_VECTOR(5, "-100 -100 100 100 0")
    CHK_VECTOR(20, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10)
    CHK_VECTOR(20, "-10 -10 -10 -10 -10 -10 -10 -10 -10 -10 -10 -10 -10 -10 -10 -10 -10 -10 -10 -10")

    #undef CHK_VECTOR
    #undef CHK_ONE
}

BOOST_AUTO_TEST_CASE(Statistics)
{
    #define CHK_ONE(ARG, D1, D2, MSG, ARR) \
        BOOST_CHECK_MESSAGE((ARG>=D1) && (ARG<=D2),\
                            "Failed " MSG " "+std::to_string(ARG)+" (out of band "+std::to_string(D1)+".."+std::to_string(D2)+"); Array is '"+ARR+"'");\
        ++unit_tests::counter_checks;

    #define CHK_VECTOR(D1, D2, S1, S2, ...) \
    {\
        VectorQSort<int> arr1{__VA_ARGS__};\
        for(size_t iter=0U; iter < arr1.size(); ++iter)\
        {\
            test_VectorQSort<int> arr{__VA_ARGS__};\
            arr.iteration = iter;\
            arr.sort();\
            CHK_ONE(arr.get_stat_max_stage(), D1, D2, "'deep' statistics", #__VA_ARGS__)\
            CHK_ONE(arr.get_stat_swap_count(), S1, S2, "'swap' statistics", #__VA_ARGS__)\
        }\
    }

    CHK_VECTOR(3, 8, 10, 10, 100, 0, 9, 8, 7, 6, 5, 4, 3, 2, 1, 3, 99, -10, -50)
    CHK_VECTOR(3, 8, 10, 10, "100 0 9 8 7 6 5 4 3 2 1 3 99 -10 -50")
    CHK_VECTOR(0, 0, 0, 0, 1)
    CHK_VECTOR(0, 0, 0, 0, "1")
    CHK_VECTOR(0, 0, 0, 0,)
    CHK_VECTOR(0, 0, 0, 0, "")
    CHK_VECTOR(1, 3, 2, 2, 5, 4, 3, 2, 1)
    CHK_VECTOR(1, 3, 2, 2, "5  4  3  2  1")
    CHK_VECTOR(3, 3, 0, 0, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10)
    CHK_VECTOR(3, 3, 0, 0, "-10 -10 -10 -10 -10 -10 -10 -10 -10 -10 -10 -10 -10 -10 -10 -10 -10 -10 -10 -10")
    CHK_VECTOR(1, 3, 1, 1, -100, -100, 100, 100, 0)
    CHK_VECTOR(1, 3, 1, 1, "-100 -100 100 100 0")

    #undef CHK_VECTOR
    #undef CHK_ONE
}

BOOST_AUTO_TEST_CASE(Strings)
{
    test_VectorQSort<std::string> arr;
    std::string_view str="zz za zf sd aaaa aaaa";

    arr.set_string(str);
    BOOST_CHECK_MESSAGE(arr.size() == 6U, "Failed array size (current "+std::to_string(arr.size())+" but need 6)");
    ++unit_tests::counter_checks;

    arr.sort();
    BOOST_CHECK_MESSAGE(arr.get_stat_swap_count() == 4U, "Failed 'swap' statistics (current "+std::to_string(arr.get_stat_swap_count())+" but need 4)");
    ++unit_tests::counter_checks;

    #define CHK_ONE(IDX, RIGHT) \
        BOOST_CHECK_MESSAGE(arr[IDX]==RIGHT,\
                            "Failed sorted element[" #IDX "] (current '"+arr[IDX]+"' need '" RIGHT "'); Array is '"+std::string{str}+"'");\
        ++unit_tests::counter_checks;

    CHK_ONE(0, "aaaa")
    CHK_ONE(1, "aaaa")
    CHK_ONE(2, "sd")
    CHK_ONE(3, "za")
    CHK_ONE(4, "zf")
    CHK_ONE(5, "zz")

    #undef CHK_ONE
}

BOOST_AUTO_TEST_CASE(Floating)
{
    test_VectorQSort<float> arr;
    std::string_view str="2.0 1.0000005 1.0000004 1.0000003 1.0000002 1.0000001";

    arr.set_string(str);
    BOOST_CHECK_MESSAGE(arr.size() == 6U, "Failed array size (current "+std::to_string(arr.size())+" but need 6)");
    ++unit_tests::counter_checks;

    //std::cout << std::fixed << std::setprecision(20) << "Before: " << arr << std::endl;
    arr.sort();
    //std::cout << std::fixed << std::setprecision(20) << "After: " << arr << std::endl;
    BOOST_CHECK_MESSAGE(arr.get_stat_swap_count() == 1U, "Failed 'swap' statistics (current "+std::to_string(arr.get_stat_swap_count())+" but need 1)");
    ++unit_tests::counter_checks;

    #define CHK_ONE(IDX, RIGHT) \
        BOOST_CHECK_MESSAGE(arr.eqv(IDX, RIGHT),\
                            "Failed sorted element[" #IDX "] (current "+std::to_string(arr[IDX])+" need "+std::to_string(RIGHT)+"); Array is '"+std::string{str}+"'");\
        ++unit_tests::counter_checks;

    CHK_ONE(0, 1.0)
    CHK_ONE(1, 1.0)
    CHK_ONE(2, 1.0)
    CHK_ONE(3, 1.0)
    CHK_ONE(4, 1.0)
    CHK_ONE(5, 2.0)

    #undef CHK_ONE
}

BOOST_AUTO_TEST_SUITE_END()