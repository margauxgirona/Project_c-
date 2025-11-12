#include "CallOption.h"

double CallOption::payoff(double S) const {
		return std::max(S - getStrike(), 0.0);
	}