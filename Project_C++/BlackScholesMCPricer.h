#pragma once
#include "Option.h"
#include "MT.h"
#include <vector>
#include <cmath>
#include <stdexcept>

class BlackScholesMCPricer {
private:
	Option* option;
	double initial_price; //s0
	double interest_rate; //r
	double volatility; //sigma
	int nbPaths;
	double sumPayoff;    //somme des payoffs actualisés
	double sumPayoff_Square;  // somme des carrés des payoffs actualisés

public:
	BlackScholesMCPricer(Option* option, double initial_price, double interest_rate, double volatility);

	int getNbPaths() const;

	void generate(int nb_paths);

	double operator() () const;

	std::vector<double> confidenceInterval() const;



};




























