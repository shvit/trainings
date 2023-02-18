#include <ctime>   

#include "Common.hpp"

namespace xon
{

void RandInit()
{
    std::srand(std::time(nullptr));
}

auto RandDbl() -> double
{
    double ret = (double)std::rand() / RAND_MAX;
    return ret;
}

bool RandBool() 
{
    return RandDbl() > 0.5;
}

} // namespace xon