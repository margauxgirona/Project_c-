#include "MT.h"
#include <random>

std::mt19937 MT::_gen{ std::random_device{}() };

double MT::rand_unif() 
{
    static std::uniform_real_distribution<> loi_uniforme(0.0, 1.0);
    return loi_uniforme(_gen);
}

double MT::rand_norm() 
{
    static std::normal_distribution<> loi_normale(0.0, 1.0);
    return loi_normale(_gen);
}
