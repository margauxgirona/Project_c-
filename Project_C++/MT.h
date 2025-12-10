#pragma once
#include <random>

class MT {
private:
    static std::mt19937 _gen;
    MT() = delete;//Tester move and copy
public:
    static double rand_unif();
    static double rand_norm();
};
