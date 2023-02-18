#include <boost/test/unit_test.hpp>
#include <iostream>
#include <iomanip>

#include "test.hpp"
#include "../Item.hpp"

BOOST_AUTO_TEST_SUITE(Item)

class TestItem: public xon::Item
{
public:
    
    using xon::Item::diameter_;
    using xon::Item::row_;
    using xon::Item::col_;
    using xon::Item::speed_;
    using xon::Item::angle_;
};

BOOST_AUTO_TEST_CASE(Reflects)
{
    #define CHK_REFL(TYPE, ANG_SRC, ANG_RFLCT, ANG_DST) \
    {\
        TestItem tst;\
        tst.initDynamic(1.0, ANG_SRC);\
        tst.reflectBy##TYPE(ANG_RFLCT);\
        auto res = tst.getAngle();\
        std::stringstream ss;\
        ss << "Failed to reflect '" << #TYPE << "' Source=" << ANG_SRC << ", Rfl=" << ANG_RFLCT << ", Need=" << ANG_DST << ", Get=" << res;\
        BOOST_CHECK_MESSAGE((ANG_DST - res) < 0.000001, ss.str());\
        ++unit_tests::counter_checks;\
    }
    
    #define CHK_REFL_NORM(NRM, SRC_ANG, DST_ANG) \
        CHK_REFL(Normale, SRC_ANG, NRM, DST_ANG)\
        CHK_REFL(Tangent, SRC_ANG, NRM+90.0, DST_ANG)

    CHK_REFL_NORM(0.0,   0.0, 180.0)
    CHK_REFL_NORM(0.0,   1.0, 179.0)
    CHK_REFL_NORM(0.0,  43.0, 137.0)
    CHK_REFL_NORM(0.0,  44.0, 134.0)
    CHK_REFL_NORM(0.0,  45.0, 135.0)
    CHK_REFL_NORM(0.0,  46.0, 134.0)
    CHK_REFL_NORM(0.0,  47.0, 133.0)
    CHK_REFL_NORM(0.0,  89.0,  91.0)
    CHK_REFL_NORM(0.0, 271.0, 269.0)
    CHK_REFL_NORM(0.0, 314.0, 226.0)
    CHK_REFL_NORM(0.0, 315.0, 225.0)
    CHK_REFL_NORM(0.0, 316.0, 224.0)
    CHK_REFL_NORM(0.0, 359.0, 181.0)

    // Parallel
    CHK_REFL_NORM(0.0,  90.0,   0.0)
    CHK_REFL_NORM(0.0,  90.0,  10.0)
    CHK_REFL_NORM(0.0,  90.0,  20.0)
    CHK_REFL_NORM(0.0,  90.0,  30.0)
    CHK_REFL_NORM(0.0,  90.0,  90.0)
    CHK_REFL_NORM(0.0,  90.0,  -0.0)
    CHK_REFL_NORM(0.0,  90.0, -10.0)
    CHK_REFL_NORM(0.0,  90.0, -20.0)
    CHK_REFL_NORM(0.0,  90.0, -30.0)
    CHK_REFL_NORM(0.0,  90.0, -90.0)
    CHK_REFL_NORM(0.0, 270.0,   0.0)
    CHK_REFL_NORM(0.0, 270.0,  10.0)
    CHK_REFL_NORM(0.0, 270.0,  20.0)
    CHK_REFL_NORM(0.0, 270.0,  30.0)
    CHK_REFL_NORM(0.0, 270.0,  90.0)
    CHK_REFL_NORM(0.0, 270.0,  -0.0)
    CHK_REFL_NORM(0.0, 270.0, -10.0)
    CHK_REFL_NORM(0.0, 270.0, -20.0)
    CHK_REFL_NORM(0.0, 270.0, -30.0)
    CHK_REFL_NORM(0.0, 270.0, -90.0)
    
    #undef CHK_REFL_NORM
    #undef CHK_REFL
}


BOOST_AUTO_TEST_SUITE_END()