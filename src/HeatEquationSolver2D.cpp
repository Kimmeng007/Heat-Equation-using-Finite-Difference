#include "HeatEquationSolver2D.h"
#include <vector>

namespace heat {

    void HeatEquationSolver2D::initializeMatrix() {
        temperatureMatrix = new double**[M];
        for (int t = 0; t < M; ++t) {
            temperatureMatrix[t] = new double*[N];
            for (int x = 0; x < N; ++x) {
                temperatureMatrix[t][x] = new double[N];
                for (int y = 0; y < N; ++y) {
                    temperatureMatrix[t][x][y] = u0;
                }
            }
        }
    }

    void HeatEquationSolver2D::deallocateMatrix() {
        for (int t = 0; t < M; ++t) {
            for (int x = 0; x < N; ++x) {
                delete[] temperatureMatrix[t][x];
            }
            delete[] temperatureMatrix[t];
        }
        delete[] temperatureMatrix;
    }

    void HeatEquationSolver2D::applyNeumannBoundary(double** currentLayer) {
        // Neumann condition on edges (du/dn = 0)
        for (int i = 0; i < N; ++i) {
            currentLayer[0][i] = currentLayer[1][i];
            currentLayer[N - 1][i] = currentLayer[N - 2][i];
            currentLayer[i][0] = currentLayer[i][1];
            currentLayer[i][N - 1] = currentLayer[i][N - 2];
        }
    }

    void HeatEquationSolver2D::applyDirichletBoundary(double** currentLayer) {
        // Dirichlet condition on edges
        for (int i = 0; i < N; ++i) {
            currentLayer[0][i] = u0;
            currentLayer[N - 1][i] = u0;
            currentLayer[i][0] = u0;
            currentLayer[i][N - 1] = u0;
        }
    }

    void HeatEquationSolver2D::solve() {
        // Thermal diffusivity
        double alpha = material.conductivity / (material.density * material.specificHeat);
        double r = alpha * dt / (dx * dx);

        // Temporar arrays for intermediate steps
        double** tempX = new double*[N];
        for (int i = 0; i < N; ++i) {
            tempX[i] = new double[N];
        }

        // Time stepping loop
        for (int t = 0; t < M - 1; ++t) {
            // Copy current temperature layer to tempX for intermediate computations
            for (int x = 0; x < N; ++x) {
                for (int y = 0; y < N; ++y) {
                    tempX[x][y] = temperatureMatrix[t][x][y];
                }
            }

            // Solve in x-direction (ADI step 1)
            for (int y = 1; y < N - 1; ++y) {
                // Create and solve tridiagonal system for each row
                double* lower = new double[N - 2]; // Lower diagonal
                double* diag = new double[N - 2]; // Main diagonal
                double* upper = new double[N - 2]; // Upper diagonal
                double* rhs = new double[N - 2];  // Right-hand side

                for (int x = 1; x < N - 1; ++x) {
                    lower[x - 1] = -r;
                    diag[x - 1] = 1 + 2 * r;
                    upper[x - 1] = -r;
                    rhs[x - 1] = tempX[x][y] + r * (temperatureMatrix[t][x][y + 1] - 2 * temperatureMatrix[t][x][y] + temperatureMatrix[t][x][y - 1]);
                }

                // Thomas algorithm to solve tridiagonal system
                for (int i = 1; i < N - 2; ++i) {
                    double m = lower[i - 1] / diag[i - 1];
                    diag[i] -= m * upper[i - 1];
                    rhs[i] -= m * rhs[i - 1];
                }
                rhs[N - 3] /= diag[N - 3];
                for (int i = N - 4; i >= 0; --i) {
                    rhs[i] = (rhs[i] - upper[i] * rhs[i + 1]) / diag[i];
                }

                // Update temperature for x-direction
                for (int x = 1; x < N - 1; ++x) {
                    tempX[x][y] = rhs[x - 1];
                }

                delete[] lower;
                delete[] diag;
                delete[] upper;
                delete[] rhs;
            }

            // Apply Neumann or Dirichlet boundar conditions after x-direction step
            applyNeumannBoundary(tempX);

            // Solve in y-direction (ADI step 2)
            for (int x = 1; x < N - 1; ++x) {
                // Create and solve tridiagonal system for each column
                double* lower = new double[N - 2]; // Lower diagonal
                double* diag = new double[N - 2]; // Main diagonal
                double* upper = new double[N - 2]; // Upper diagonal
                double* rhs = new double[N - 2];  // Right-hand side

                for (int y = 1; y < N - 1; ++y) {
                    lower[y - 1] = -r;
                    diag[y - 1] = 1 + 2 * r;
                    upper[y - 1] = -r;
                    rhs[y - 1] = tempX[x][y] + r * (tempX[x + 1][y] - 2 * tempX[x][y] + tempX[x - 1][y]) + dt * source.F(x * dx, y * dx);
                }

                // Thomas algorithm to solve tridiagonal system
                for (int i = 1; i < N - 2; ++i) {
                    double m = lower[i - 1] / diag[i - 1];
                    diag[i] -= m * upper[i - 1];
                    rhs[i] -= m * rhs[i - 1];
                }
                rhs[N - 3] /= diag[N - 3];
                for (int i = N - 4; i >= 0; --i) {
                    rhs[i] = (rhs[i] - upper[i] * rhs[i + 1]) / diag[i];
                }

                // Update temperature for y-direction
                for (int y = 1; y < N - 1; ++y) {
                    temperatureMatrix[t + 1][x][y] = rhs[y - 1];
                }

                delete[] lower;
                delete[] diag;
                delete[] upper;
                delete[] rhs;
            }

            // Apply Neumann or Dirichlet boundar conditions after y-direction step
            applyNeumannBoundary(temperatureMatrix[t + 1]);
        }

        // Deallocate temporar array
        for (int i = 0; i < N; ++i) {
            delete[] tempX[i];
        }
        delete[] tempX;
    }


    void HeatEquationSolver2D::printTemperatureMatrixAtTime(int timeStep, std::ostream& os) const {
        if (timeStep < 0 || timeStep >= M) {
            os << "Invalid time step.\n";
            return;
        }
        os << "Temperature Matrix at Time Step " << timeStep << " (t = " << timeStep * dt << " s):\n";
        for (int x = 0; x < N; ++x) {
            for (int y = 0; y < N; ++y) {
                os << temperatureMatrix[timeStep][x][y] << " ";
            }
            os << "\n";
        }
    }

    // std::vector<std::vector<std::vector<double>>> HeatEquationSolver2D::getTemperatureMatrix() const {
    //     std::vector<std::vector<std::vector<double>>> temperatureGrids(M_,
    //         std::vector<std::vector<double>>(N_, std::vector<double>(N_)));

    //     for (int t = 0; t < M_; ++t) {
    //         for (int i = 0; i < N_; ++i) {
    //             for (int j = 0; j < N_; ++j) {
    //                 temperatureGrids[t][i][j] = temperatureMatrix[t][i][j];
    //             }
    //         }
    //     }
    //     return temperatureGrids;
    // }

    // Function to get all temperature grids (3D representation for all time steps)
    std::vector<std::vector<std::vector<double>>> HeatEquationSolver2D::getAllTemperatureGrids() const {
        std::vector<std::vector<std::vector<double>>> temperatureGrids(M);  // Vector to store all temperature grids

        for (int t = 0; t < M; ++t) {
            // Create a 2D grid for each time step
            temperatureGrids[t] = std::vector<std::vector<double>>(N, std::vector<double>(N));

            // Copy the temperature data for each grid
            for (int x = 0; x < N; ++x) {
                for (int y = 0; y < N; ++y) {
                    temperatureGrids[t][x][y] = temperatureMatrix[t][x][y];
                }
            }
        }
        return temperatureGrids;
    }
}

