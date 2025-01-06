#include "HeatEquationSolver2D.h"

namespace heat {

    HeatEquationSolver2D::HeatEquationSolver2D(const Material& material, const Heatsource2D& source, double L, double tmax, double u0, int N, int M)
        : material(material), source(source), L(L), tmax(tmax), u0(u0), N(N), M(M), dx(L / (N - 1)), dt(tmax / (M - 1)) {
        temperatureGrids.resize(M, std::vector<std::vector<double>>(N, std::vector<double>(N, u0)));
    }

    void HeatEquationSolver2D::applyNeumannBoundary(std::vector<std::vector<double>>& grid) {
        for (int y = 0; y < N; ++y) {
            grid[0][y] = grid[1][y];  
        }
    }

    void HeatEquationSolver2D::applyDirichletBoundary(std::vector<std::vector<double>>& grid) {
        for (int y = 0; y < N; ++y) {
            grid[N - 1][y] = u0; 
        }
    }

    void HeatEquationSolver2D::solveTridiagonal(double* a, double* b, double* c, double* d, int size) {
        std::vector<double> c_star(size), d_star(size);

        c_star[0] = c[0] / b[0];
        d_star[0] = d[0] / b[0];
        for (int i = 1; i < size; ++i) {
            double m = 1.0 / (b[i] - a[i - 1] * c_star[i - 1]);
            c_star[i] = c[i] * m;
            d_star[i] = (d[i] - a[i - 1] * d_star[i - 1]) * m;
        }

        d[size - 1] = d_star[size - 1];
        for (int i = size - 2; i >= 0; --i) {
            d[i] = d_star[i] - c_star[i] * d[i + 1];
        }
    }

    void HeatEquationSolver2D::solve() {
        double alpha = material.conductivity / (material.density * material.specificHeat);
        double r = alpha * dt / (dx * dx);

        std::vector<double> a(N - 1, -r), b(N, 1 + 2 * r), c(N - 1, -r), d(N);

        for (int t = 0; t < M - 1; ++t) {
            // Implicit solve along x-direction
            for (int j = 0; j < N; ++j) {
                for (int i = 1; i < N - 1; ++i) {
                    d[i] = temperatureGrids[t][i][j] + 
                           dt * source.F(i * dx, j * dx) / (material.density * material.specificHeat);
                }
                applyNeumannBoundary(temperatureGrids[t]);
                solveTridiagonal(a.data(), b.data(), c.data(), d.data(), N);

                for (int i = 0; i < N; ++i) {
                    temperatureGrids[t + 1][i][j] = d[i];
                }
            }

            // Implicit solve along y-direction
            for (int i = 0; i < N; ++i) {
                for (int j = 1; j < N - 1; ++j) {
                    d[j] = temperatureGrids[t + 1][i][j];
                }
                applyDirichletBoundary(temperatureGrids[t + 1]);
                solveTridiagonal(a.data(), b.data(), c.data(), d.data(), N);

                for (int j = 0; j < N; ++j) {
                    temperatureGrids[t + 1][i][j] = d[j];
                }
            }
        }
    }

    const std::vector<std::vector<std::vector<double>>>& HeatEquationSolver2D::getAllTemperatureGrids() const {
        return temperatureGrids;
    }

}
