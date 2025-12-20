#include "AmericanPutOption.h"

AmericanPutOption::AmericanPutOption(double expiry, double strike) : AmericanOption(expiry, strike) {}

double AmericanPutOption::payoff(double S) const{
	return std::max(getStrike() - S, 0.0);
}
