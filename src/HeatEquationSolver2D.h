#ifndef HEAT_EQUATION_SOLVER_2D_H
#define HEAT_EQUATION_SOLVER_2D_H

#include <vector>
#include "Material.h"
#include "Heatsource2D.h"

/**
 * @brief Solves the two-dimensional heat equation for a given material and heat source.
 */
namespace heat {
    class HeatEquationSolver2D {
    private:
        Material material;      /**< Material properties */
        Heatsource2D source;    /**< Heat source affecting the material */
        double L;               /**< Length of the domain in both x and y */
        double tmax;            /**< Maximum simulation time */
        double u0;              /**< Initial temperature */
        int N;                  /**< Number of spatial divisions in x and y */
        int M;                  /**< Number of time steps */
        double dx;              /**< Spatial step size */
        double dt;              /**< Time step size */

        std::vector<std::vector<std::vector<double>>> temperatureGrids; /**< 3D array for temperature values */

        /**
         * @brief Applies Neumann boundary condition at the left boundary (x = 0).
         */
        void applyNeumannBoundary(std::vector<std::vector<double>>& grid);

        /**
         * @brief Applies Dirichlet boundary condition at the right boundary (x = L).
         */
        void applyDirichletBoundary(std::vector<std::vector<double>>& grid);

        /**
         * @brief Solves a tridiagonal system of equations using the Thomas algorithm.
         */
        void solveTridiagonal(double* a, double* b, double* c, double* d, int size);

    public:
        /**
         * @brief Constructor to initialize the solver with parameters.
         */
        HeatEquationSolver2D(const Material& material, const Heatsource2D& source, double L, double tmax, double u0, int N, int M);

        /**
         * @brief Solve the 2D heat equation using finite difference methods.
         */
        void solve();

        /**
         * @brief Returns the entire temperature grid for visualization.
         */
        const std::vector<std::vector<std::vector<double>>>& getAllTemperatureGrids() const;
    };
}

#endif
