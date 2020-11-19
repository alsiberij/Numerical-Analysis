#pragma once
#include <iostream>
#include "../Expression.h"

using namespace std;


//Решение систем дифференциальных уравнений явным методом Эйлера
class ExplicitEulerSolver {
private:
    int dim;
    Expression** functions;
    double xBeg;
    double xEnd;
    double eps;
    double tauMax;
    double* solutions;

    void print(double x);

public:
    ExplicitEulerSolver(int dim, Expression** functions, double xBeg, double xEnd, double eps, double tauMax, double* initApprox);

    void solve();

    ~ExplicitEulerSolver();
};
