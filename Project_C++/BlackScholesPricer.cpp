#include "BlackScholesPricer.h"
#include "CallOption.h"
#include "PutOption.h"
#include <cmath>

BlackScholesPricer::BlackScholesPricer(EuropeanVanillaOption* option, double asset_price, double interest_rate, double volatility) : vanilla(option), asset_price(asset_price), interest_rate(interest_rate), volatility(volatility) {}

BlackScholesPricer::BlackScholesPricer(EuropeanDigitalOption* option, double asset_price, double interest_rate, double volatility) : digital(option), asset_price(asset_price), interest_rate(interest_rate), volatility(volatility) {}


// Price computation
double BlackScholesPricer::operator()() const {
	// vanilla option
	if (vanilla) {
		double d1 = (std::log(asset_price / vanilla->getStrike()) + (interest_rate + 0.5 * volatility * volatility) * vanilla->getExpiry()) / (volatility * std::sqrt(vanilla->getExpiry()));
		double d2 = d1 - volatility * std::sqrt(vanilla->getExpiry());

		if (vanilla->GetOptionType() == EuropeanVanillaOption::call) {
			return asset_price * N(d1) - vanilla->getStrike() * std::exp(-interest_rate * vanilla->getExpiry()) * N(d2);
		}
		else if (vanilla->GetOptionType() == EuropeanVanillaOption::put) {
			return vanilla->getStrike() * std::exp(-interest_rate * vanilla->getExpiry()) * N(-d2) - asset_price * N(-d1);
		}
		else
			throw std::invalid_argument("Unknown option type.");
	}
	// digital option
	else if (digital) {
		double d1 = (std::log(asset_price / digital->getStrike()) + (interest_rate + 0.5 * volatility * volatility) * digital->getExpiry()) / (volatility * std::sqrt(digital->getExpiry()));
		double d2 = d1 - volatility * std::sqrt(digital->getExpiry());

		if (digital->GetOptionType() == EuropeanDigitalOption::call)
            return std::exp(-interest_rate * digital->getExpiry()) * N(d2);
        else if (digital->GetOptionType() == EuropeanDigitalOption::put)
            return std::exp(-interest_rate * digital->getExpiry()) * N(-d2);
		else
			throw std::invalid_argument("Unknown option type.");
	}
	else {
			throw std::invalid_argument("Unknown option type.");
	}
}

double BlackScholesPricer::delta() const {
	
	if (vanilla){
		double d1 = (std::log(asset_price / vanilla->getStrike()) + (interest_rate + 0.5 * volatility * volatility) * vanilla->getExpiry()) / (volatility * std::sqrt(vanilla->getExpiry()));
		if (vanilla->GetOptionType() == EuropeanVanillaOption::call) {
			return N(d1);
		}
		else {
			return N(d1) - 1.0;
		}
	}
	else if (digital){
		double d2 = (std::log(asset_price / digital->getStrike()) + (interest_rate + 0.5 * volatility * volatility) * digital->getExpiry()) / (volatility * std::sqrt(digital->getExpiry())) - volatility * std::sqrt(digital->getExpiry());
		double n_pdf = (1 / std::sqrt(2 * M_PI)) * std::exp(-d2*d2 / 2);
		double a = std::exp(-interest_rate * digital->getExpiry()) * n_pdf / (asset_price * volatility * std::sqrt(digital->getExpiry()));

		if (digital->GetOptionType() == EuropeanDigitalOption::call)
			return a;
		else
			return -a;
	}
	else {
		throw std::invalid_argument("Unknown option type.");
	}
}
