#include <cstdlib>
#include <sstream>
#include <iostream>

#include "VectorQSort.hpp"

int main(int argc, char *argv[])
{
    VectorQSort arr;
    if(argc > 1)
    {
        std::stringstream ss;
        std::copy(argv+1, argv+argc, std::ostream_iterator<char*>(ss, " "));
        arr.set_string(ss.str());
    }
    else
    {
        std::cout << "Enter array data (separated by Space and finish with Enter):" << std::endl;
        std::cin >> arr;
    }

   //VectorQSort arr{100, 0, 9, 8, 7, 6, 5, 4, 3, 2, 1, 3, 99, -10, -50};

    std::cout << "Parsed input array with " << arr.size() << " items" << std::endl;

    if(!arr.size()) std::exit(EXIT_SUCCESS);

    std::cout << "Source: " << arr << std::endl;
    arr.sort();
    std::cout << "Result: " << arr << std::endl;

    std::cout << "Sorting statistics:" << std::endl;
    std::cout << "  Maximum deep: " << arr.get_stat_max_stage() << std::endl;
    std::cout << "  Swap count: " << arr.get_stat_swap_count() << std::endl;
}
