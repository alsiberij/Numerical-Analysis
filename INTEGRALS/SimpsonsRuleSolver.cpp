#include "SimpsonsRuleSolver.h"

SimpsonsRuleSolver::SimpsonsRuleSolver(double beg, double end, Expression *function, double eps, int initN) {
    this->beg = beg;
    this->end = end;
    this->function = function;
    this->eps = eps;
    this->initN = initN;
}

void SimpsonsRuleSolver::solve() {
    int N = initN;
    double curResult = calculate(N);
    while (true) {
        double nextResult = calculate(N * 2);           //Двойной пересчет
        if (abs(nextResult - curResult) < 15 * eps) {
            break;
        } else {
            curResult = nextResult;
            N *= 2;
        }
    }
    result = curResult;
    finN = N;
}

double SimpsonsRuleSolver::calculate(int N) {
    //Вычисление интеграла с заданным количеством разбиений
    double xi = beg;
    double h = (end - beg) / N;
    double result = 0;
    for (int i = 0; i <= N; ++i) {
        double fx = function->F(&xi);
        if (i % 2 != 0) {
            fx *= 4;
        } else {
            fx *= ((i == 0 or i == N) ? 1 : 2);
        }
        result += fx;
        xi += h;
    }
    result *= h / 3;
    return result;
}

double SimpsonsRuleSolver::getResult() {
    return result;
}

int SimpsonsRuleSolver::getFinalN() {
    return finN;
}
