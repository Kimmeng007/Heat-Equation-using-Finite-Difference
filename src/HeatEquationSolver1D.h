#ifndef HEAT_EQUATION_SOLVER_1D_H
#define HEAT_EQUATION_SOLVER_1D_H

#include <iostream>
#include "material.h"
#include "Heatsource1D.h"

/**
 * @brief Solves the one-dimensional heat equation for a given material and heat source.
 */
namespace heat {
    class HeatEquationSolver1D {
    private:
        Material material;    /**< Material properties */
        Heatsource1D source;  /**< Heat source affecting the material */
        double L;             /**< Length of the domain */
        double tmax;          /**< Maximum simulation time */
        double u0;            /**< Initial temperature */
        int N_s;              /**< Number of spatial divisions */
        int N_t;              /**< Number of time steps */
        double dx;            /**< Spatial step size */
        double dt;            /**< Time step size */

        double** temperatureMatrix; /**< Dynamic 2D array for storing temperature values */

        /**
         * @brief Initializes the dynamic memory for the temperature matrix.
         */
        void initializeMatrix();

        /**
         * @brief Deallocates the dynamic memory for the temperature matrix.
         */
        void deallocateMatrix();

        /**
         * @brief Applies Neumann boundary condition at x = 0.
         *
         * @param currentRow The current time step row in the temperature matrix.
         */
        void applyNeumannBoundary(double* currentRow);

        /**
         * @brief Applies Dirichlet boundary condition at x = L.
         *
         * @param currentRow The current time step row in the temperature matrix.
         */
        void applyDirichletBoundary(double* currentRow);

        /**
         * @brief Solves a tridiagonal system of equations using the Thomas algorithm.
         *
         * @param a Sub-diagonal coefficients (size N-1).
         * @param b Main diagonal coefficients (size N).
         * @param c Super-diagonal coefficients (size N-1).
         * @param d Right-hand side vector (size N).
         * @param N Size of the tridiagonal system.
         */
        void solveTridiagonal(double* a, double* b, double* c, double* d, int N);

    public:
        /**
         * @brief Constructor to initialize the HeatEquationSolver1D object.
         *
         * @param material Material for which to solve the heat equation.
         * @param source Heat source affecting the material.
         * @param L Length of the domain.
         * @param tmax Maximum simulation time.
         * @param u0 Initial temperature.
         * @param N_s Number of spatial divisions.
         * @param N_t Number of time steps.
         */
        HeatEquationSolver1D(const Material& material, const Heatsource1D& source, double L, double tmax, double u0, int N_s, int N_t)
            : material(material), source(source), L(L), tmax(tmax), u0(u0), N_s(N_s), N_t(N_t), dx(L / N_s), dt(tmax / N_t) {
                initializeMatrix();
        }

        /**
         * @brief Destructor to deallocate dynamic memory
         */
        ~HeatEquationSolver1D() {
            deallocateMatrix();
        }

        /**
         * @brief Solve the heat equation using finite difference methods
         */
        void solve();

        /**
         * @brief Print the temperature matrix to the specified output stream
         * 
         * @param os Output stream (default: std::cout)
         */
        void printTemperatureMatrix(std::ostream& os = std::cout) const;

        /**
         * @brief Gets the temperature profile at a specific time step
         * 
         * @param timeStep The time step index (0 to N_t-1)
         * @return A pointer to the temperature profile at the specified time step
         */
        const double* getTemperatureAtTime(int timeStep) const;

    };
}

#endif
