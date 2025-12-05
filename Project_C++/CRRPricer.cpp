#include <iostream>
#include <cmath> 
#include "CRRPricer.h"

CRRPricer::CRRPricer(Option * option, int depth, double asset_price, double up, double down, double interest_rate) :
    _option(option), _depth(depth), _S0(asset_price), _u(up), _d(down), _r(interest_rate) {
        // check for arbitrage
        if (!(down < interest_rate && interest_rate < up))
            throw std::invalid_argument("Arbitrage condition is not respected, we must have : D < R < U.");
        else if (option->isAsianOption())
            throw std::invalid_argument("Is Asian option");

        _S.setDepth(depth);
        _H.setDepth(depth);
        _Exercise.setDepth(depth);

        _computed = false;
}

CRRPricer::CRRPricer(Option* option, int depth, double asset_price, double r, double volatility) : 
_option(option), _depth(depth), _S0(asset_price), _r(r){

    double T = option->getExpiry();
    double h = T / depth;

    _u = std::exp((r + 0.5 * volatility * volatility) * h + volatility * std::sqrt(h)) - 1.0;
    _d = std::exp((r + 0.5 * volatility * volatility) * h - volatility * std::sqrt(h)) - 1.0;
    _r = std::exp(r * h) - 1.0;

    if (!(_d < _r && _r < _u))
        throw std::invalid_argument("Arbitrage condition not respected (D < R < U)");
    else if (option->isAsianOption())
            throw std::invalid_argument("Is Asian option");
    
    _S.setDepth(depth);
    _H.setDepth(depth);
    _Exercise.setDepth(depth);  
    _computed = false;

}

// function created to replace std::pow()
// because std::pow() is generic and computationnally expensive 
//On peut faire mieux, référence
double CRRPricer::intPow(double a, int exponent) const{
    double result = 1.0;
    for(int i = 0; i < exponent; i++)
        result *= a;
    return result;
}

void CRRPricer::compute(){
     // Precompute powers (1+u)^i and (1+d)^j
    vector<double> upPow(_depth+1), downPow(_depth+1);
    upPow[0] = downPow[0] = 1.0;

    for (int i = 1; i <= _depth; i++) {
        upPow[i]   = upPow[i-1]   * (1 + _u);
        downPow[i] = downPow[i-1] * (1 + _d);
    }

    for (int i = 0; i <= _depth; i++) {
        double S = _S0 * upPow[i] * downPow[_depth - i];
        _H.setNode(_depth, i, _option->payoff(S));
    }

    double q = (_r - _d) / (_u - _d);
    double inv_r = 1.0 / (1 + _r);

    if (_option->isAmericanOption()) {

        for (int n = _depth - 1; n >= 0; --n) {
            for (int i = 0; i <= n; i++) {

                double continuation =
                     (q * _H.getNode(n+1, i+1) +
                           (1 - q) * _H.getNode(n+1, i)) / inv_r;

    
                double S = _S0 * upPow[i] * downPow[n - i];
                double intrinsic = _option->payoff(S);

                bool exercise = intrinsic >= continuation;

                if (intrinsic >= continuation) {
                    _H.setNode(n, i, intrinsic);
                    _Exercise.setNode(n, i, true);}
                else {
                    _H.setNode(n, i, continuation);
                    _Exercise.setNode(n, i, false);}

            }
        }
    }

    else {
        // compute _H
        for (int n = _depth - 1; n >= 0; n--) {
            for (int i = 0; i <= n; i++) {
                double value = q * _H.getNode(n + 1, i + 1) + (1 - q) * _H.getNode(n + 1, i);
                value /= (1 + _r);
                _H.setNode(n, i, value);
            }
        }
    }

    _computed = true;


}

/*
void CRRPricer::compute(){
    // fill the _stockTree with the prices
    //Boucler une seule fois
    for(int n = 0; n <= _depth; n++){
        for(int i = 0; i <= n; i++){
            _S.setNode(n, i, _S0 * intPow(1 + _u, i) * intPow(1 + _d, n-i));
            
        }
    }
    // at expiracy date (at N = _depth), fair etout en une seule boucle
    for(int i = 0; i <= _depth; i++){
        _H.setNode(_depth, i, _option->payoff(_S.getNode(_depth, i)));
    }

    // risk neutral probability
    double q = (_r - _d) / (_u - _d);

    
    if (_option->isAmericanOption()) {
        for (int n = _depth - 1; n >= 0; n--) {
            for (int i = 0; i <= n; i++) {
                // Valeur de continuation
                double continuation = (q * _H.getNode(n + 1, i + 1) + (1 - q) * _H.getNode(n + 1, i)) / (1 + _r);

                // Valeur d'exercice immediat
                double intrinsic = _option->payoff(_S.getNode(n, i));

                if (intrinsic >= continuation) {
                    _H.setNode(n, i, intrinsic);
                    _Exercise.setNode(n, i, true);}
                else {
                    _H.setNode(n, i, continuation);
                    _Exercise.setNode(n, i, false);}
            }
        }
    }

    else {
        // compute _H
        for (int n = _depth - 1; n >= 0; n--) {
            for (int i = 0; i <= n; i++) {
                double value = q * _H.getNode(n + 1, i + 1) + (1 - q) * _H.getNode(n + 1, i);
                value /= (1 + _r);
                _H.setNode(n, i, value);
            }
        }
    }

    _computed = true; 
}

*/

double CRRPricer::get(int n, int i) const {
    if (n > _depth || i > n)
        throw std::out_of_range("CRRPricer::get indices out of range");
    return _H.getNode(n, i);
}

bool CRRPricer::getExercise(int n, int i) const {
            return _Exercise.getNode(n, i);
        }

static long double factorial(int n) {
    long double res = 1.0;
    for (int i = 2; i <= n; ++i)
        res *= i;
    return res;
}

//Optimiser factorielle, triangle de Pascal

double CRRPricer::operator()(bool closed_form) {
    if (!(_computed))
        compute();
    
    if (!closed_form)
        return _H.getNode(0, 0);

    double discount = 1.0 / std::pow(1 + _r, _depth);

    double q  = (_r - _d) / (_u - _d);
    double pq = q;           // q^i
    double p1 = 1.0 - q;     // (1-q)
    double p1pow = std::pow(p1, _depth); // initial: (1-q)^N

    long double C = 1.0;     // C(N,0)

    double sum = 0.0;

    for (int i = 0; i <= _depth; i++) {

        sum += C * pq * p1pow * _option->payoff(_S.getNode(_depth, i));

        if (i < _depth) { // To avoid calculate the last update

            C = C * (_depth - i) / (i + 1);

            // Update powers
            pq    *= q;        // q^i   -> q^(i+1)
            p1pow /= p1;       // (1-q)^(N-i) -> (1-q)^(N-i-1)
        }
    }

    return discount * sum;
}

/*
double CRRPricer::operator()(bool closed_form) {
    if (!(_computed))
        compute();
    
    if (!(closed_form))
        return _H.getNode(0, 0);
    else{
        double discount = 1 / intPow(1 + _r, _depth);
        // risk neutral probability
        double q = (_r - _d) / (_u - _d);
        double facto_N = factorial(_depth);
        double sum = 0.0;
        for(int i = 0; i <= _depth; i++){
            sum += (facto_N / (factorial(i) * factorial(_depth - i))) * intPow(q, i) * intPow(1 - q, _depth - i) * _option->payoff(_S.getNode(_depth, i));
        }
        return discount * sum;
    }
}*/