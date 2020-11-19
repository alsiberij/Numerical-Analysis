#include "TrapezoidalRuleSolver.h"

TrapezoidalRuleSolver::TrapezoidalRuleSolver(double beg, double end, Expression* function, double eps, int initN) {
    this->beg = beg;
    this->end = end;
    this->function = function;
    this->eps = eps;
    this->initN = initN;
}

void TrapezoidalRuleSolver::solve() {
    int N = initN;
    double curResult = calculate(N);
    while (true) {
        double nextResult = calculate(N * 2);           //Двойной пересчет
        if (abs(nextResult - curResult) < 3 * eps) {
            break;
        } else {
            curResult = nextResult;
            N *= 2;
        }
    }
    result = curResult;
    finN = N;
}

double TrapezoidalRuleSolver::calculate(int n) {
    //Вычисление интеграла с заданным количеством разбиений
    double xi = beg;
    double h = (end - beg) / n;
    double curResult = 0;
    for (int i = 0; i <= n; ++i) {
        curResult += function->F(&xi) * ((i == 0 or i == n) ? 1 : 2);
        xi += h;
    }
    curResult *= h / 2;
    return curResult;
}

double TrapezoidalRuleSolver::getResult() {
    return result;
}

int TrapezoidalRuleSolver::getFinalN() {
    return finN;
}
