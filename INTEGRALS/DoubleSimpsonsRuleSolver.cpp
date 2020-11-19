#include "DoubleSimpsonsRuleSolver.h"

DoubleSimpsonsRuleSolver::DoubleSimpsonsRuleSolver(double begX, double endX, double begY, double endY,
                                                   Expression* function, double eps, int initN, int initM) {
    this->function = function;
    this->begX = begX;
    this->endX = endX;
    this->endY = endY;
    this->begY = begY;
    this->eps = eps;
    this->initN = initN;
    this->initM = initM;
}

double DoubleSimpsonsRuleSolver::calculate(int N, int M) {
    double hx = (endX - begX) / (2 * N);
    double hy = (endY - begY) / (2 * M);
    double curResult = 0;

    double* arguments = new double[2];

    //Обход области по прямоугольникам
    for (int ix = 0; ix < N; ++ix) {
        for (int jy = 0; jy < M; ++jy) {

            //Высление прямоугольника разбитого 9 частей (центр с весом 16, углы с весом 1, промежеточные с весом 4)
            for (int my = 2 * jy, i = 0; my <= 2 * jy + 2; ++my, ++i) {
                for (int kx = 2 * ix, j = 0; kx <= 2 * ix + 2; ++kx, ++j) {
                    double newX = begX;
                    for (int k = 0; k < kx; ++k) {
                        newX += hx;
                    }
                    double newY = begY;
                    for (int k = 0; k < my; ++k) {
                        newY += hy;
                    }
                    arguments[0] = newX;
                    arguments[1] = newY;
                    curResult += function->F(arguments) * (i != 1 ? (j != 1 ? 1 : 4) : (j != 1 ? 4 : 16));
                }
            }

        }
    }

    curResult *= hx * hy / 9;

    delete [] arguments;
    return curResult;
}

void DoubleSimpsonsRuleSolver::solve() {
    int N = initN;
    int M = initM;
    double curResult = calculate(N, M);
    while (true) {
        double nextResult = calculate(2 * N, 2 * M);        //Двойной пересчет
        if (abs(nextResult - curResult) < 15 * eps) {
            break;
        } else {
            curResult = nextResult;
            N *= 2;
            M *= 2;
        }
    }
    result = curResult;
    finN = N;
    finM = M;
}

double DoubleSimpsonsRuleSolver::getResult() {
    return result;
}

int DoubleSimpsonsRuleSolver::getFinalN() {
    return finN;
}

int DoubleSimpsonsRuleSolver::getFinalM() {
    return finM;
}


