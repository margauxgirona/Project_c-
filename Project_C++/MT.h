#pragma once
#include <random>

class MT {
    private:
        static std::mt19937 _gen;
        MT() = delete;

        // Suppress the copy and move constructors
        // We want to ensure that the MT class is not hackable.
        // That is why we disabled the copy and move constructors and assignment operators.
        MT(const MT&) = delete;
        MT(MT&&) = delete;
        MT& operator=(const MT&) = delete;
        MT& operator=(MT&&) = delete;

    public:
        static double rand_unif();
        static double rand_norm();
};
