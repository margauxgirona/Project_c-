#include "BlackScholesMCPricer.h"
#include "AsianOption.h"
#include <cmath>
#include <stdexcept>


BlackScholesMCPricer::BlackScholesMCPricer(Option* opt, double s0, double r, double sigma) : 
		option(opt), initial_price(s0), interest_rate(r), volatility(sigma),
		nbPaths(0), estimate(0.0),var(0.0) {}


int BlackScholesMCPricer::getNbPaths() const {
	return nbPaths;
}

void BlackScholesMCPricer::generate(int nb_paths) {
	if (nb_paths <= 0) {
		throw std::invalid_argument("Le nombre de trajectoires doit être un entier positif.");
	}
	for (int i = 0; i < nb_paths; i++) {
		std::vector<double> path;
		if (option -> isAsianOption()) {
			AsianOption* asian = static_cast<AsianOption*>(option);
			auto timeSteps = asian->getTimeSteps();
			double S = initial_price; 
			double t_previous = 0.0;        // pour calculer dt
			for (double t : timeSteps) {
				double dt = t - t_previous; // Intervalle de temps entre deux pas de simulation
				double Z = MT::rand_norm();  // nombre aléatoire N(0,1)
				S *= std::exp((interest_rate - 0.5 * volatility * volatility) * dt
					+ volatility * std::sqrt(dt) * Z); // Formule Black-Scholes 
				path.push_back(S);
				t_previous = t;
			}
		}
		else {
			double Z = MT::rand_norm();  // nombre aléatoire N(0,1)
			double T = option->getExpiry();   //Temps final (expiration) de l'option
			double ST = initial_price * std::exp((interest_rate - 0.5 * volatility * volatility) * T
				+ volatility * std::sqrt(T) * Z);
			path.push_back(ST);
		}
		double payoff = option->payoffPath(path);
		double discounted = std::exp(-interest_rate * option->getExpiry()) * payoff;
		nbPaths++;
		double delta = discounted - estimate;   //Différence entre le nouveau payoff et la moyenne actuelle
		estimate += delta / nbPaths;
		var += delta * (discounted - estimate);
	}
}

double BlackScholesMCPricer::operator() () const {
	if (nbPaths == 0) {
		throw std::runtime_error("Aucune trajectoire n'a encore été générée.");
	}
	return estimate;
}


std::vector<double> BlackScholesMCPricer::confidenceInterval() const {
	if (nbPaths <= 1) {
		throw std::runtime_error("Il n'y a pas assez de trajectoire générée pour calculer l'IC.");
	}
	double variance = var / (nbPaths - 1);
	double std_error = sqrt(variance / nbPaths);
	double margin = 1.96 * std_error;
	return { estimate - margin, estimate + margin };
}



