#include "MT.h"
#include <random>

std::mt19937 MT::_gen{ std::random_device{}() };


static std::uniform_real_distribution<double> unif_dist(0.0, 1.0);
static std::normal_distribution<double> norm_dist(0.0, 1.0);

double MT::rand_unif() {
    return unif_dist(_gen);  
}

double MT::rand_norm() {
    return norm_dist(_gen);  
}
