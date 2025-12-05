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
        throw std::invalid_argument("Le nombre de trajectoires doit être un entier positif.");
    }
    std::vector<double> path; 
    int nSteps = 0;

    if (option->isAsianOption()) {
        AsianOption* asian = static_cast<AsianOption*>(option);
        nSteps = asian->getTimeSteps().size();
        path.resize(nSteps);   // allocation unique
    }
    else {
        nSteps = 1;
        path.resize(1);        // allocation pour vanilla
    }
    for (int i = 0; i < nb_paths; i++) {
        if (option->isAsianOption()) {
            AsianOption* asian = static_cast<AsianOption*>(option);
            auto timeSteps = asian->getTimeSteps();
            double S = initial_price;
            double t_previous = 0.0;

            for (int k = 0; k < nSteps; k++) {
                double t = timeSteps[k];
                double dt = t - t_previous;
                double Z = MT::rand_norm();
                S *= std::exp((interest_rate - 0.5 * volatility * volatility) * dt
                    + volatility * std::sqrt(dt) * Z);
                path[k] = S;
                t_previous = t;
            }
        }
        else {
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
		throw std::runtime_error("Aucune trajectoire n'a encore été générée.");
	}
	return sumPayoff / nbPaths;  //moyenne
}


std::vector<double> BlackScholesMCPricer::confidenceInterval() const {
	if (nbPaths <= 1) {
		throw std::runtime_error("Il n'y a pas assez de trajectoire générée pour calculer l'IC.");
	}
    double mean = sumPayoff / nbPaths;
    double variance = (sumPayoff_Square - nbPaths * mean * mean) / (nbPaths - 1);
    double std_error = std::sqrt(variance / nbPaths);
    double margin = 1.96 * std_error;
    return { mean - margin, mean + margin };
}





