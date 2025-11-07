#include "BlackScholesMCPricer.h"
#include "AsianOption.h"
#include <cmath>
#include <stdexcept>

void BlackScholesMCPricer::generate(int nb_paths) {
    if (nb_paths <= 0) throw std::invalid_argument("Le nombre de trajectoires doit être positif");

    double T = option->getExpiry();

    for (int i = 0; i < nb_paths; ++i) {
        std::vector<double> path;

        // 🔹 Cas d'une option asiatique
        if (option->isAsianOption()) {
            AsianOption* asian = dynamic_cast<AsianOption*>(option);
            if (!asian) throw std::runtime_error("Erreur : cast AsianOption impossible");

            auto timeSteps = asian->getTimeSteps();
            double S = initial_price;
            double prev_t = 0.0;
            path.reserve(timeSteps.size());

            for (double t : timeSteps) {
                double dt = t - prev_t;
                double Z = MT::rand_norm();
                S *= std::exp((interest_rate - 0.5 * volatility * volatility) * dt
                    + volatility * std::sqrt(dt) * Z);
                path.push_back(S);
                prev_t = t;
            }
        }
        // 🔹 Cas d'une option européenne
        else {
            double Z = MT::rand_norm();
            double ST = initial_price * std::exp((interest_rate - 0.5 * volatility * volatility) * T
                + volatility * std::sqrt(T) * Z);
            path.push_back(ST);
        }

        // 🔹 Payout actualisé
        double payoff = option->payoffPath(path);
        double discounted = std::exp(-interest_rate * T) * payoff;

        // Mise à jour incrémentale de la moyenne et de la variance (Welford)
        nbPaths++;
        double delta = discounted - estimate;
        estimate += delta / nbPaths;
        var += delta * (discounted - estimate);
    }
}

double BlackScholesMCPricer::operator()() const {
    if (nbPaths == 0) throw std::runtime_error("Aucune trajectoire générée");
    return estimate;
}

std::vector<double> BlackScholesMCPricer::confidenceInterval() const {
    if (nbPaths <= 1) throw std::runtime_error("Pas assez de trajectoires pour calculer l'IC");

    double variance = var / (nbPaths - 1);  // variance empirique
    double stdErr = std::sqrt(variance / nbPaths);
    double margin = 1.96 * stdErr;          // 95% intervalle de confiance

    return { estimate - margin, estimate + margin };
}