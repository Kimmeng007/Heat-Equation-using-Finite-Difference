#ifndef RESULT2D_H
#define RESULT2D_H

#include <vector>
#include <iostream>
#include "HeatEquationSolver2D.h"
#include "Material.h"
#include "Visualization2D.h"

/**
 * @brief A class to manage the simulation and visualization of the 2D heat equation.
 */
namespace heat {

    class Result2D {
    private:
        double f_;              /**< Frequency of the heat source */
        double t_max_;          /**< Maximum simulation time */
        double L_;              /**< Length of the simulation domain */
        double u0_;             /**< Initial temperature */
        int N_;                 /**< Number of spatial divisions in each direction */
        int M_;                 /**< Number of time steps */
        Material material_;     /**< Material properties */

    public:
        /**
         * @brief Constructs a Result2D object with the given simulation parameters.
         *
         * @param f Frequency of the heat source.
         * @param tmax Maximum simulation time.
         * @param L Length of the simulation domain.
         * @param u0 Initial temperature.
         * @param N Number of spatial divisions.
         * @param M Number of time steps.
         * @param material Material properties.
         */
        Result2D(double f, double tmax, double L, double u0, int N, int M, const Material& material)
            : f_(f), t_max_(tmax), L_(L), u0_(u0), N_(N), M_(M), material_(material) {}

        /**
         * @brief Runs the 2D heat equation simulation and visualizes the results.
         */
        void runSimulation();
    };

}

#endif
