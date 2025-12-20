#include "BlackScholesMCPricer.h"
#include "AsianOption.h"
#include <cmath>
#include <stdexcept>


BlackScholesMCPricer::BlackScholesMCPricer(Option* option, double initial_price, double interest_rate, double volatility) : 
		option(option), initial_price(initial_price), interest_rate(interest_rate), volatility(volatility),
		nbPaths(0), sumPayoff(0.0), sumPayoff_Square(0.0) {}


int BlackScholesMCPricer::getNbPaths() const {
	return nbPaths;
}


void BlackScholesMCPricer::generate(int nb_paths) {
    if (nb_paths <= 0) {
        throw std::invalid_argument("Number of trajectories must be positive");
    }

    std::vector<double> path(1); 
    int nSteps = 1;
    std::vector<double> timeSteps; // for AsianOption
	
    AsianOption* asian = nullptr;
    if (option->isAsianOption()) {
        asian = static_cast<AsianOption*>(option);
        timeSteps = asian->getTimeSteps();
        nSteps = timeSteps.size();
        path.resize(nSteps);
    }
    // Loop on all trajectories
    for (int i = 0; i < nb_paths; i++) {
        if (asian) {
            double S = initial_price;
            double t_previous = 0.0;
            for (int k = 0; k < nSteps; k++) {
                double dt = timeSteps[k] - t_previous;
                double Z = MT::rand_norm();
                S *= std::exp((interest_rate - 0.5 * volatility * volatility) * dt
                              + volatility * std::sqrt(dt) * Z);
                path[k] = S;
                t_previous = timeSteps[k];
            }
        } else { // vanilla option
            double Z = MT::rand_norm();
            double ST = initial_price * std::exp((interest_rate - 0.5 * volatility * volatility) * option->getExpiry()
                                                 + volatility * std::sqrt(option->getExpiry()) * Z);
            path[0] = ST;
        }

        double payoff = option->payoffPath(path);
        double discounted = std::exp(-interest_rate * option->getExpiry()) * payoff;

        nbPaths++;
        sumPayoff += discounted;
        sumPayoff_Square += discounted * discounted;
    }
}


double BlackScholesMCPricer::operator() () const {
	if (nbPaths == 0) {
		throw std::runtime_error("No trajectory generated");
	}
	return sumPayoff / nbPaths;
}


std::vector<double> BlackScholesMCPricer::confidenceInterval() const {
	if (nbPaths <= 1) {
		throw std::runtime_error("Not enough trajectories to compute the confidence interval");
	}
    double mean = sumPayoff / nbPaths;
    double variance = (sumPayoff_Square - nbPaths * mean * mean) / (nbPaths - 1);
    double std_error = std::sqrt(variance / nbPaths);
    double margin = 1.96 * std_error;
    return { mean - margin, mean + margin };
}






