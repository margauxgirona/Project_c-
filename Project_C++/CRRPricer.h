#ifndef CRRPRICER_H
#define CRRPRICER_H

#include <iostream>
#include "Option.h"
#include "EuropeanVanillaOption.h"
#include "PutOption.h"
#include "CallOption.h"
#include "BinaryTree.h"

class CRRPricer{
    private:
        Option * _option;
        int _depth;
        double _S0;
        double _u;
        double _d;
        double _r;

        BinaryTree<double> _S;
        BinaryTree<double> _H;
        
        bool _computed;
    
    public:
        CRRPricer(Option * option, int depth, double asset_price, double up, double down, double interest_rate);

        double intPow(double a, int exponent) const;
        void compute();

        double get(int n, int i) const;

        double operator()(bool closed_form = false);

        BinaryTree<double> get_S() const {return _S; }
        BinaryTree<double> get_H() const {return _H; }
};

#endif