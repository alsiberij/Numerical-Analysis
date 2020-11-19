#include "ExplicitEulerSolver.h"

ExplicitEulerSolver::ExplicitEulerSolver(int dim, Expression** functions, double xBeg, double xEnd, double eps,
                                         double tauMax, double* initApprox) {
    this->dim = dim;
    this->functions = functions;
    this->xBeg = xBeg;
    this->xEnd = xEnd;
    this->eps = eps;
    this->tauMax = tauMax;
    solutions = new double[dim + 1];    //Дополнительная ячейка для параметра t
    for (int i = 0; i < dim; ++i) {
        solutions[i] = initApprox[i];
    }
}

void ExplicitEulerSolver::print(double x) {
    cout << "X = " << x << ":   ";
    for (int i = 0; i < dim; ++i) {
        cout << "Y" << i << " = " << solutions[i] << "; ";
    }
    cout << endl;
}

void ExplicitEulerSolver::solve() {
    double* fSols = new double[dim];
    double xCur = xBeg;
    while (xCur <= xEnd) {
        print(xCur);

        solutions[dim] = xCur;                      //Нахождение F(Yk, tk)
        for (int i = 0; i < dim; ++i) {
            fSols[i] = functions[i]->F(solutions);
        }

        double tau = eps / (abs(fSols[0]) + eps / tauMax);      //Вычисление шага
        for (int i = 0; i < dim; ++i) {
            if (eps / (abs(fSols[i]) + eps / tauMax) < tau) {
                tau = eps / (abs(fSols[i]) + eps / tauMax);
            }
        }

        for (int i = 0; i < dim; ++i) {
            solutions[i] = solutions[i] + tau * fSols[i];
        }

        xCur += tau;
    }

    delete [] fSols;
}

ExplicitEulerSolver::~ExplicitEulerSolver() {
    delete [] solutions;
}
