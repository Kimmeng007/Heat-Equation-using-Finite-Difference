#ifndef RESULT2D_H
#define RESULT2D_H

#include <iostream>
#include "HeatEquationSolver2D.h"
#include "Material.h"
#include "Visualization2D.h"

/**
 * @brief A class to solve and visualize the 2D heat equation for a material
 */
namespace heat {
    class Result2D {
    private:
        double f_;
        double t_max_;
        double L_;
        double u0_;
        int N_;
        int M_;
        Material material_;

    public:
        /**
         * @brief Constructs a Result2D object with simulation parameters.
         * 
         * @param f Frequency of the heat source
         * @param tmax Maximum simulation time
         * @param L Length of the simulation domain
         * @param u0 Initial temperature
         * @param N Number of spatial divisions
         * @param M Number of time steps
         * @param material Material properties
         */
        Result2D(double f, double tmax, double L, double u0, int N, int M, const Material& material)
            : f_(f), t_max_(tmax), L_(L), u0_(u0), N_(N), M_(M), material_(material) {}

        /**
         * @brief Runs the 2D heat equation simulation and visualizes results.
         */
        void runSimulation();
    };
}

#endif
