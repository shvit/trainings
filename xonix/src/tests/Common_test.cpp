#include <boost/test/unit_test.hpp>
#include <iostream>
#include <iomanip>

#include "test.hpp"
#include "../Common.hpp"

BOOST_AUTO_TEST_SUITE(Common)

BOOST_AUTO_TEST_CASE(Rand)
{
    xon::RandInit();

    constexpr size_t iterations_count = 200;
    size_t count_dbl_1 = 0U;
    size_t count_dbl_2 = 0U;
    size_t count_bool_1 = 0U;
    size_t count_bool_2 = 0U;
    for(size_t iter=0U; iter < iterations_count; ++iter)
    {
        if(xon::RandDbl() < 0.5) ++count_dbl_1; else ++count_dbl_2;
        if(!xon::RandBool()) ++count_bool_1; else ++count_bool_2;
    }

    BOOST_CHECK_MESSAGE(count_dbl_1 > iterations_count/4, "Failed rand generator for low double (less 25%)");
    ++unit_tests::counter_checks;

    BOOST_CHECK_MESSAGE(count_dbl_2 > iterations_count/4, "Failed rand generator for high double (less 25%)");
    ++unit_tests::counter_checks;

    BOOST_CHECK_MESSAGE(count_bool_1 > iterations_count/4, "Failed rand generator for low bool (less 25%)");
    ++unit_tests::counter_checks;

    BOOST_CHECK_MESSAGE(count_bool_2 > iterations_count/4, "Failed rand generator for high bool (less 25%)");
    ++unit_tests::counter_checks;
}

BOOST_AUTO_TEST_CASE(F_normalizeAngle)
{
    #define CHK_NORM(VALUE) \
        {\
            auto new_val = xon::normalizeAngle(VALUE);\
            std::stringstream ss;\
            ss << "Failed normalize value " << VALUE << " to value " << new_val;\
            BOOST_CHECK_MESSAGE(((new_val<360.1) && (new_val > -0.1)), ss.str());\
            ++unit_tests::counter_checks;\
        }
    CHK_NORM(0.0)
    CHK_NORM(10.0)
    CHK_NORM(90.0)
    CHK_NORM(200.0)
    CHK_NORM(300.0)
    CHK_NORM(400.0)
    CHK_NORM(40000000000.0)
    CHK_NORM(-0.0)
    CHK_NORM(-10.0)
    CHK_NORM(-90.0)
    CHK_NORM(-200.0)
    CHK_NORM(-300.0)
    CHK_NORM(-400.0)
    CHK_NORM(-40000000000.0)

    #undef CHK_NORM
}

BOOST_AUTO_TEST_CASE(F_arithmeticMean)
{
    #define CHK_AVG(AVG, ...) \
    {\
        xon::WorldCoordList lst{__VA_ARGS__};\
        auto avg = xon::arithmeticMean(lst);\
        std::stringstream ss;\
        ss << "Failed average value need " << AVG << " get " << avg;\
        BOOST_CHECK_MESSAGE((AVG - avg) < 0.000001, ss.str());\
        ++unit_tests::counter_checks;\
    }

    CHK_AVG(1.0, 1.0)
    CHK_AVG(0.0, 1.0, -1.0)
    CHK_AVG(3.0, 2.0, 4.0)
    CHK_AVG(-300.0, -200.0, -400)
    CHK_AVG(1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0)

    #undef CHK_AVG
}

BOOST_AUTO_TEST_CASE(F_rand)
{
    #define CHK_ROUND(SRC_R, SRC_C, DST_R, DST_C) \
    {\
        xon::Point point{SRC_R, SRC_C};\
        auto [r,c] = xon::round(point);\
        std::stringstream ss;\
        ss << "Failed to round (R:" << SRC_R << ",C:" << SRC_C << "), need (R:" << DST_R << ",C:" << DST_C << "), get (R:"<<r<<",C:"<<c<<")";\
        BOOST_CHECK_MESSAGE((DST_R == r) && (DST_C == c), ss.str());\
        ++unit_tests::counter_checks;\
    }

    CHK_ROUND(0.0, 0.0, 0, 0)
    CHK_ROUND(0.49, 0.49, 0, 0)
    CHK_ROUND(0.51, 0.51, 1, 1)
    CHK_ROUND(-0.49, -0.49, 0, 0)
    CHK_ROUND(-0.51, -0.51, -1, -1)
    CHK_ROUND(100.49, 200.49, 100, 200)
    CHK_ROUND(100.51, 200.51, 101, 201)
    CHK_ROUND(-100.49, -200.49, -100, -200)
    CHK_ROUND(-100.51, -200.51, -101, -201)

    #undef CHK_ROUND
}

BOOST_AUTO_TEST_SUITE_END()