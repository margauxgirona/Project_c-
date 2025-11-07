#pragma once
#include "Option.h"
#include <vector>
#include <stdexcept>

class AsianOption : public Option {
private:
    std::vector<double> _timeSteps;
public:
    AsianOption(double expiry, const std::vector<double>& timeSteps)
        : Option(expiry), _timeSteps(timeSteps) {
        if (timeSteps.empty()) throw std::invalid_argument("Empty time steps");
    }

    std::vector<double> getTimeSteps() const { return _timeSteps; }

    double payoffPath(const std::vector<double>& path) const override {
        double avg = 0.0;
        for (double s : path) avg += s;
        avg /= path.size();
        return payoff(avg);
    }

    bool isAsianOption() const override { return true; }
};
