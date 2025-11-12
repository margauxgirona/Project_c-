#pragma once
#include <random>

class MT {
private:
    static std::mt19937 _gen;
    MT() = delete;
public:
    static double rand_unif();
    static double rand_norm();
};
