#ifndef RESULT1D_H
#define RESULT1D_H

#include <iostream>
#include "HeatEquationSolver1D.h"
#include "Material.h"
#include "Visualization.h"

/**
 * @brief A class to solve and visualize the 1D heat equation for a material
 * 
 */
namespace heat{

    class Result1D {
    private:
        double f_; /** Factor representing the intensity of the heat source */
        double t_max_; /** The maximum simulation time*/
        double L_; /** Length of the domain */
        double u0_; /** Initial temperature */
        int N_; /** Number of spatial divisions */
        int M_; /** Number of time steps */
        Material material_; /** The material for the simulation */

    public:
        /**
         * @brief Construct a new Final1D object
         * 
         * @param f : The intensity factor of the heat source
         * @param tmax : The maximum simulation time
         * @param L : The length of the domain
         * @param u0 : The initial temperature of the domain
         * @param N : Number of spatial divisions
         * @param M : Number of time steps
         * @param material : Material properties for the simulation
         */
        Result1D(double f, double tmax, double L, double u0, int N, int M, const Material& material)
        : f_(f), t_max_(tmax), L_(L), u0_(u0), N_(N), M_(M), material_(material) {}

        /**
         * @brief Run the heat equation solver and visualize results
         */
        void runSimulation();
    };
}

#endif
