#pragma once
#include "Option.h"
#include <vector>
#include <stdexcept>

class AsianOption : public Option {
private:
    std::vector<double> _timeSteps;

public:
    AsianOption(const std::vector<double>& timeSteps);

    std::vector<double> getTimeSteps() const;

    double payoffPath(const std::vector<double>& path) const override;

    bool isAsianOption() const override;
};
