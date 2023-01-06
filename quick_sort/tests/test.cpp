#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>
#include <iostream>

#include "test.hpp"

namespace unit_tests
{

size_t counter_checks{0U};

} // namespace unit_tests

BOOST_AUTO_TEST_SUITE(Main)

/** \brief Show finish counter
 *
 */
BOOST_AUTO_TEST_CASE(Finish)
{
  // show counter
  std::cout << "Summary checks " << unit_tests::counter_checks << std::endl;
}

BOOST_AUTO_TEST_SUITE_END()
