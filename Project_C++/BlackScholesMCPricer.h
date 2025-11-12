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
	double estimate;      
	double var;

public:
	BlackScholesMCPricer(Option* opt, double s0, double r, double sigma) : 
		option(opt), initial_price(s0), interest_rate(r), volatility(sigma),
		nbPaths(0), estimate(0.0),var(0.0) {}

	int getNbPaths() const;

	void generate(int nb_paths);

	double operator() () const;

	std::vector<double> confidenceInterval() const;



};



























