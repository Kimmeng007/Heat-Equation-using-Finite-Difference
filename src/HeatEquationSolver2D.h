#ifndef HEAT_EQUATION_SOLVER_2D_H
#define HEAT_EQUATION_SOLVER_2D_H

#include <iostream>
#include "material.h"
#include "HeatSource2D.h"
#include <vector>

/**
 * @brief Solves the two-dimensional heat equation for a given material and heat source.
 */
namespace heat {
    class HeatEquationSolver2D {
    private:
        Material material;      /**< Material properties */
        Heatsource2D source;    /**< Heat source affecting the material */
        double L;               /**< Length of the domain */
        double tmax;            /**< Maximum simulation time */
        double u0;              /**< Initial temperature */
        int N;                  /**< Number of spatial divisions in each dimension */
        int M;                  /**< Number of time steps */
        double dx;              /**< Spatial step size (x or y-direction), Note that, in this case dx = dy */
        double dt;              /**< Time step size */

        double*** temperatureMatrix; /**< Dynamic 3D array for storing temperature values */

        /**
         * @brief Initializes the dynamic memory for the temperature matrix.
         */
        void initializeMatrix();

        /**
         * @brief Deallocates the dynamic memory for the temperature matrix.
         */
        void deallocateMatrix();

        /**
         * @brief Applies Neumann boundary conditions at the edges of the domain.
         */
        void applyNeumannBoundary(double** currentLayer);

        /**
         * @brief Applies Dirichlet boundary conditions at the edges of the domain.
         */
        void applyDirichletBoundary(double** currentLayer);

    public:
        /**
         * @brief Constructor to initialize the HeatEquationSolver2D object.
         *
         * @param material Material for which to solve the heat equation.
         * @param source Heat source affecting the material.
         * @param L Length of the domain.
         * @param tmax Maximum simulation time.
         * @param u0 Initial temperature.
         * @param N Number of spatial divisions in each dimension.
         * @param M Number of time steps.
         */
        HeatEquationSolver2D(const Material& material, const Heatsource2D& source, double L, double tmax, double u0, int N, int M)
            : material(material), source(source), L(L), tmax(tmax), u0(u0), N(N), M(M), dx(L / (N - 1)), dt(tmax / (M - 1)) {
                initializeMatrix();
        }

        /**
         * @brief Destructor to deallocate dynamic memory
         */
        ~HeatEquationSolver2D() {
            deallocateMatrix();
        }

        /**
         * @brief Solve the heat equation using finite difference methods
         */
        void solve();

        /**
         * @brief Print the temperature matrix at a specific time step
         *
         * @param timeStep The time step index (0 to M-1)
         * @param os Output stream (default: std::cout)
         */
        void printTemperatureMatrixAtTime(int timeStep, std::ostream& os = std::cout) const;

        std::vector<std::vector<std::vector<double>>> getAllTemperatureGrids() const;
    };

}

#endif // HEAT_EQUATION_SOLVER_2D_H
