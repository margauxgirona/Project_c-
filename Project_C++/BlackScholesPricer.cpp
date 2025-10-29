#include "BlackScholesPricer.h"
#include "CallOption.h"
#include "PutOption.h"
#include <cmath>

//calcul du prix
double BlackScholesPricer::operator()() const {
	double S = asset_price;
	double K = option->getStrike();
	double T = option->getExpiry();
	double r = interest_rate;
	double v = volatility;
	double d1 = (std::log(S / K) + (r + 0.5 * v * v) * T) / (v * std::sqrt(T));
	double d2 = d1 - v * std::sqrt(T);
	if (option->GetOptionType() == EuropeanVanillaOption::call) {
		return S * N(d1) - K * std::exp(-r * T) * N(d2);
	}
	else if (option->GetOptionType() == EuropeanVanillaOption::put) {
		return K * std::exp(-r * T) * N(-d2) - S * N(-d1);
	}
	else {
		throw std::invalid_argument("Unknown option type.");
	}
}

double BlackScholesPricer::delta() const {
	double S = asset_price;
	double K = option->getStrike();
	double T = option->getExpiry();
	double r = interest_rate;
	double v = volatility;
	double d1 = (std::log(S / K) + (r + 0.5 * v * v) * T) / (v * std::sqrt(T));
	if (option->GetOptionType() == EuropeanVanillaOption::call) {
		return N(d1);
	}
	else if (option->GetOptionType() == EuropeanVanillaOption::put) {
		return N(d1) - 1.0;
	}
	else {
		throw std::invalid_argument("Unknown option type.");
	}
}
