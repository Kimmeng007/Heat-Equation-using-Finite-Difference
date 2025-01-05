#include "HeatEquationSolver1D.h"

namespace heat {

    void HeatEquationSolver1D::initializeMatrix() {
        temperatureMatrix = new double*[M];
        for (int t = 0; t < M; ++t) {
            temperatureMatrix[t] = new double[N];
            for (int x = 0; x < N; ++x) {
                temperatureMatrix[t][x] = u0;
            }
        }
    }

    void HeatEquationSolver1D::deallocateMatrix() {
        for (int t = 0; t < M; ++t) {
            delete[] temperatureMatrix[t];
        }
        delete[] temperatureMatrix;
    }

    void HeatEquationSolver1D::applyNeumannBoundary(double* currentRow) {
        currentRow[0] = currentRow[1]; /** Neumann boundary condition (du/dx = 0) */
    }

    void HeatEquationSolver1D::applyDirichletBoundary(double* currentRow) {
        currentRow[N - 1] = u0; /** Dirichlet boundary condition (fixed temperature) */
    }

    void HeatEquationSolver1D::solveTridiagonal(double* a, double* b, double* c, double* d, int N) {
        double* c_star = new double[N];
        double* d_star = new double[N];

        /** Forward sweep */
        c_star[0] = c[0] / b[0];
        d_star[0] = d[0] / b[0];
        for (int i = 1; i < N; ++i) {
            double m = 1.0 / (b[i] - a[i - 1] * c_star[i - 1]);
            c_star[i] = c[i] * m;
            d_star[i] = (d[i] - a[i - 1] * d_star[i - 1]) * m;
        }

        /** Back substitution */
        d[N - 1] = d_star[N - 1];
        for (int i = N - 2; i >= 0; --i) {
            d[i] = d_star[i] - c_star[i] * d[i + 1];
        }

        delete[] c_star;
        delete[] d_star;
    }


    void HeatEquationSolver1D::solve() {
        /**  Initialize the temperature matrix */
        initializeMatrix();

        /**  Calculate the thermal diffusivity and the coefficient r */
        double alpha = material.conductivity / (material.density * material.specificHeat);
        double r = alpha * dt / (dx * dx);

        double* a = new double[N - 1]; /** Sub-diagonal */
        double* b = new double[N];     /** Main diagonal */
        double* c = new double[N - 1]; /** Super-diagonal */
        double* d = new double[N];     /** Right-hand side */

        /** Initialize tridiagonal matrix coefficients*/
        for (int i = 0; i < N - 1; ++i) {
            a[i] = -r;
            c[i] = -r;
        }
        for (int i = 0; i < N; ++i) {
            b[i] = 1 + 2 * r;
        }

        /** Time-stepping loop */
        for (int n = 0; n < M - 1; ++n) {
            /** Construct the right-hand side vector */
            for (int x = 1; x < N - 1; ++x) {
                d[x] = temperatureMatrix[n][x] +
                       dt * source.F(x * dx) / (material.density * material.specificHeat);
            }

            /** Apply boundary conditions to the right-hand side*/
            d[0] = temperatureMatrix[n][0];       /** Neumann at x = 0 */
            d[N - 1] = u0;                      /** Dirichlet at x = L */

            /** Solve the tridiagonal system */
            solveTridiagonal(a, b, c, d, N);

            /** Update the temperature matrix for the next time step */
            for (int x = 0; x < N; ++x) {
                temperatureMatrix[n + 1][x] = d[x];
            }

            /** Apply boundary conditions to the updated row */
            applyNeumannBoundary(temperatureMatrix[n + 1]);
            applyDirichletBoundary(temperatureMatrix[n + 1]);
        }

        /** clean up dynamically allocated memory for tridiagonal coefficients */
        delete[] a;
        delete[] b;
        delete[] c;
        delete[] d;
    }

    void HeatEquationSolver1D::printTemperatureMatrix(std::ostream& os) const {
        os << "Temperature Matrix (in Kelvin):\n";
        for (int t = 0; t < M; ++t) {
            os << "Time step " << t << " (t = " << t * dt << " s): ";
            for (int x = 0; x < N; ++x) {
                os << temperatureMatrix[t][x] << " ";
            }
            os << "\n";
        }
    }

    const double* HeatEquationSolver1D::getTemperatureAtTime(int timeStep) const {
        if (timeStep >= 0 && timeStep < M) {
            return temperatureMatrix[timeStep]; 
        }
        return nullptr;
    }

}
