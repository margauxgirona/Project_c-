#pragma once
#include <random>

class MT {
private:
    static std::mt19937 _gen;

    MT() = delete; // empêche la création d'instances

public:
    static double rand_unif() {
        static std::uniform_real_distribution<> dist(0.0, 1.0);
        return dist(_gen);
    }

    static double rand_norm() {
        static std::normal_distribution<> dist(0.0, 1.0);
        return dist(_gen);
    }
};
