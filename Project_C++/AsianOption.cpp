#include "AsianOption.h"
#include <stdexcept> 

AsianOption::AsianOption(const std::vector<double>& timeSteps) : Option(timeSteps.back()), _timeSteps(timeSteps) {
    if (timeSteps.empty()) {
        throw std::invalid_argument("Empty time steps");
    }
}

std::vector<double> AsianOption::getTimeSteps() const {
    return _timeSteps;
}

double AsianOption::payoffPath(const std::vector<double>& path) const {
    double avg = 0.0;
    for (double s : path) avg += s;
    avg /= path.size();
    return payoff(avg);
}

bool AsianOption::isAsianOption() const {
    return true;
}
