#pragma once
#include <cmath>
#include "../Expression.h"

using namespace std;


//Решения определенного интеграла методом Симпсона
class SimpsonsRuleSolver {
private:
    double beg;
    double end;
    Expression* function;
    double eps;
    int initN;
    int finN;
    double result;

    double calculate(int N);

public:
    SimpsonsRuleSolver(double beg, double end, Expression* function, double eps, int initN);

    void solve();

    double getResult();

    int getFinalN();
};

