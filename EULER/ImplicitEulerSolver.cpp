#include "ImplicitEulerSolver.h"

ImplicitEulerSolver::ImplicitEulerSolver(int dim, Expression** functions, double xBeg, double xEnd, double eps,
                                         double tauMax, double tauMin, double* initApprox) {
    this->dim = dim;
    this->functions = functions;
    this->xBeg = xBeg;
    this->xEnd = xEnd;
    this->eps = eps;
    this->tauMax = tauMax;
    this->tauMin = tauMin;
    solutionsPrev = new double[dim];
    solutions = new double[dim + 1];    //Дополнительная ячейка для хранения параметра
    solutionsNext = new double[dim];
    for (int i = 0; i < dim; ++i) {
        solutionsPrev[i] = initApprox[i];
        solutions[i] = initApprox[i];
        solutionsNext[i] = initApprox[i];
    }
}

void ImplicitEulerSolver::solve() {
    double t = xBeg;
    double tNext;

    double tauPrev = tauMin;
    double tau = tauMin;
    double tauNext;

    solutions[dim] = t;

    double* epsK = new double[dim];

    Expression** adjFunctions = new Expression*[dim];   //Формирование нового вектора функций на основе исходного
    for (int i = 0; i < dim; ++i) {
        adjFunctions[i] = new DifferentialExpression(dim, functions[i], i, solutions, tau, t);
    }

    while (t < xEnd) {
        tNext = t + tau;

        for (int i = 0; i < dim; ++i) {     //Уставновка необходимых параметров для нового вектора функций
            dynamic_cast<DifferentialExpression*>(adjFunctions[i])->setTau(tau);
            dynamic_cast<DifferentialExpression*>(adjFunctions[i])->setX(t);
        }

        NewtonSolver solver(dim, adjFunctions, 100, solutions, eps);    //Решение системы нелинейных уравнений относительно solutionsNext
        solver.solve();

        for (int i = 0; i < dim; ++i) {
            solutionsNext[i] = solver.getSolutions()[i];
        }

        for (int i = 0; i < dim; ++i) {
            epsK[i] = -(tau / (tau + tauPrev)) * (solutionsNext[i] - solutions[i] - tau * (solutions[i] - solutionsPrev[i]) / tauPrev);
        }

        bool needRecount = false;   //При необходимости пересчета уменьшаем шаг
        for (int i = 0; i < dim; i++) {
            if (abs(epsK[i]) > eps and !needRecount) {
                tau /= 2;
                tNext = t;
                for (int j = 0; j < dim; j++) {
                    solutionsNext[j] = solutions[j];
                }
                needRecount = true;
            }
        }

        if (needRecount) {
            continue;
        };

        double *tauTmp = new double[dim];
        for (int i = 0; i < dim; i++) {     //Правило трех зон
            if (abs(epsK[i]) > eps) {
                tauTmp[i] = tau / 2;
            } else if (eps / 4 < abs(epsK[i]) && abs(epsK[i]) <= eps) {
                tauTmp[i] = tau;
            } else if (abs(epsK[i]) <= eps / 4) {
                tauTmp[i] = 2 * tau;
            }
            //tauTmp[i] = sqrt(eps/abs(epsK[i])) * tau; //По формуле
        }


        double curTauMin = tauTmp[0];       //Поиск минимального шага
        for (int i = 1; i < dim; i++) {
            if (curTauMin > tauTmp[i]) {
                curTauMin = tauTmp[i];
            }
        }
        delete[] tauTmp;
        tauNext = curTauMin;

        if (tauNext > tauMax) {
            tauNext = tauMax;
        }

        if ((t + tau > xEnd) and t < xEnd) {
            t = xEnd - tau;
        }

        print(t);

        for (int i = 0; i < dim; i++) {
            solutionsPrev[i] = solutions[i];
            solutions[i] = solutionsNext[i];
        }

        tauPrev = tau;
        tau = tauNext;
        t = tNext;
    }

    delete [] epsK;
    for (int i = 0; i < dim; ++i) {
        delete adjFunctions[i];
    }
    delete [] adjFunctions;
}

void ImplicitEulerSolver::print(double x) {
    cout << "X = " << x << ":   ";
    for (int i = 0; i < dim; ++i) {
        cout << "Y" << i << " = " << solutions[i] << "; ";
    }
    cout << endl;
}

ImplicitEulerSolver::~ImplicitEulerSolver() {
    delete [] solutionsPrev;
    delete [] solutions;
    delete [] solutionsNext;
}
