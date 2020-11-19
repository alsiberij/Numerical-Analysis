#include <iostream>
#include "GaussianSolver.h"

using namespace std;

int main() {

    ifstream file("../GAUSS/sample.txt");

    GaussianSolver solver1(file);

    solver1.printInitial();
    solver1.solve();
    solver1.printSolutions();

    cout << "Discrepancy = " << solver1.getDiscrepancy() << endl;
    cout << "Relative error = " << solver1.getRelativeError() << endl << endl;

    file.close();


    file.open("../GAUSS/sampleLDLT.txt");
    GaussianSolver solverSym(file);

    solverSym.printInitial();
    solverSym.solveViaLDLT();
    solverSym.printSolutions();

    cout << "Discrepancy = " << solverSym.getDiscrepancy() << endl;
    cout << "Relative error = " << solverSym.getRelativeError() << endl;

    return 0;
}
