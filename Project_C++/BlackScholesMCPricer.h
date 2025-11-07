#pragma once
#include "Option.h"
#include "MT.h"
#include <vector>
#include <cmath>
#include <stdexcept>

// =====================================================
//  Classe BlackScholesMCPricer
//  Monte Carlo pricer sous modèle de Black-Scholes
// =====================================================
class BlackScholesMCPricer {
private:
    Option* option;          // pointeur vers l'option à pricer
    double initial_price;    // S0
    double interest_rate;    // r
    double volatility;       // σ
    int nbPaths;             // nombre total de trajectoires simulées

    double estimate;         // moyenne empirique actuelle
    double var;              // accumulateur de variance (méthode de Welford)

public:
    // Constructeur conforme au sujet
    BlackScholesMCPricer(Option* option, double initial_price, double interest_rate, double volatility)
        : option(option),
        initial_price(initial_price),
        interest_rate(interest_rate),
        volatility(volatility),
        nbPaths(0),
        estimate(0.0),
        var(0.0) {}

    // Génère des trajectoires Monte Carlo et met à jour estimate et var
    void generate(int nb_paths);

    // Retourne la meilleure estimation actuelle du prix
    double operator()() const;

    // Retourne l'intervalle de confiance à 95%
    std::vector<double> confidenceInterval() const;

    // Nombre de trajectoires générées
    int getNbPaths() const { return nbPaths; }
};
