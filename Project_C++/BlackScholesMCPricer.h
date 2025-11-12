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
	BlackScholesMCPricer(Option* opt, double s0, double r, double sigma);

	int getNbPaths() const;

	void generate(int nb_paths);

	double operator() () const;

	std::vector<double> confidenceInterval() const;



};



























