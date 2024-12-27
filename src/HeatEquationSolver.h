#ifndef HEAT_EQUATION_SOLVER_H
#define HEAT_EQUATION_SOLVER_H

#include "Grid.h"
#include "Material.h"
#include "Heatsource.h"

class HeatEquationSolver{
    private: 
    double* u_; /** current temperature array */
    double* u_prev_; /** previous temperature array */

    public: 
    Grid grid_;
    Material material_;
    Heatsource heatsource_;

     /**
     * @brief initialize the solver
     * @param grid : Grid object
     * @param material : Material properties
     * @param heatsource : Heat source object
     */
    HeatEquationSolver(Grid grid, Material material, Heatsource heatsource): grid_(grid), material_(material), heatsource_(heatsource){
        u_ = new double[grid_.Nx_](); // Initialize arrays to zero
        u_prev_ = new double[grid_.Nx_]();
    }

    /**
     * @brief release allocated memory
     */
    ~HeatEquationSolver();

    /**
     * @brief initialize the temperature field with initial conditions
     * @param T0 initial temperature in Kelvin
     */

    void initialize(double T0);

    /**
     * @brief apply boundary conditions (Neumann and Dirichlet)
     */
    void applyBoundaryConditions();

    /**
     * @brief solve one time step using the implicit method
     */
    void step();
};


#endif