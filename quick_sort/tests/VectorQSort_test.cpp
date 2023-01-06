#include <boost/test/unit_test.hpp>
#include <iostream>

#include "test.hpp"
#include "../VectorQSort.hpp"

BOOST_AUTO_TEST_SUITE(Common)

class test_VectorQSort: public VectorQSort
{
public:
    size_t iteration{0U};
    auto pivot_idx(const Idx left, const Idx right) const -> Idx
    {
        if(left > right) throw std::runtime_error("Failed left-right borders");
        if(left == right) return left;
        if((left == 0U) && (right == (size()-1U)))
        {
            return iteration;
        }
        return left + (std::rand() % (right-left+1));
    }

    using VectorQSort::VectorQSort;
};

BOOST_AUTO_TEST_CASE(SortedVectors)
{
    #define CHK_ONE(LEFT, RIGHT, MSG, ARR) \
        BOOST_CHECK_MESSAGE((LEFT)==(RIGHT),\
                            "Failed " MSG " (current "+std::to_string(LEFT)+" need "+std::to_string(RIGHT)+"); Array is '"+ARR+"'");\
        ++unit_tests::counter_checks;

    #define CHK_VECTOR(CNT, ...) \
        {\
            VectorQSort arr{__VA_ARGS__};\
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
        VectorQSort arr1{__VA_ARGS__};\
        for(size_t iter=0U; iter < arr1.size(); ++iter)\
        {\
            test_VectorQSort arr{__VA_ARGS__};\
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

BOOST_AUTO_TEST_SUITE_END()