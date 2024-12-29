#ifndef HEAT_EQUATION_SOLVER_1D_H
#define HEAT_EQUATION_SOLVER_1D_H

#include <iostream>
#include "material.h"
#include "Heatsource1D.h"

/**
 * @brief Solves the one-dimensional heat equation for a given material and heat source
 */
namespace heat{
    class HeatEquationSolver1D {
    private:
        Material material;    /** Material properties */
        Heatsource1D source;  /** Heat source affecting the material */
        double L;             /** Length of the domain */
        double tmax;          /** Maximum simulation time */
        double u0;            /** Initial temperature */
        int N_s;              /** Number of spatial divisions */
        int N_t;              /** Number of time steps */
        double dx;            /** Spatial step size */
        double dt;            /** Time step size */

        double** temperatureMatrix; /** Dynamic 2D array for storing temperature values */

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
        : material(material), source(source), L(L), tmax(tmax), u0(u0), N_s(N_s), N_t(N_t), dx(L / N_s), dt(tmax / N_t){}

        /**
         * @brief Destructor to deallocate dynamic memory.
         */
        ~HeatEquationSolver1D();

        /**
         * @brief Solve the heat equation using finite difference methods.
         */
        void solve();

        /**
         * @brief Print the temperature matrix to the console.
         */
        void printTemperatureMatrix() const;

        /**
         * @brief Overload the stream insertion operator to display solver details.
         * 
         * @param os Output stream object.
         * @param solver HeatEquationSolver1D instance.
         * @return std::ostream& Updated output stream object.
         */
        friend std::ostream& operator<<(std::ostream& os, const HeatEquationSolver1D& solver);
    };
}

#endif
