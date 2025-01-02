#include "Result1D.h"

namespace heat {

    void Result1D::runSimulation() {
        // Create the heat source object
        Heatsource1D heatSource(t_max_, L_, f_);  /**< Initialize the heat source with the appropriate parameters */

        // Initialize the HeatEquationSolver1D with the provided parameters
        HeatEquationSolver1D solver(material_, heatSource, L_, t_max_, u0_, N_s_, N_t_);

        // Solve the heat equation using the finite difference method
        solver.solve();

        // Initialize the Visualization object for rendering the results
        Visualization visualizer("1D Heat Equation Visualization");

        // Create a static array to hold the temperature profiles for each time step
        const double* temperatureProfiles[N_t_];  /**< Holds temperature profiles at different time steps */

        // Extract the temperature profile at each time step from the solver
        for (int t = 0; t < N_t_; ++t) {
            temperatureProfiles[t] = solver.getTemperatureAtTime(t);  /**< Access the temperature profile at time step t */
        }

        // Compute the maximum temperature for color scaling (using initial temperature as a placeholder)
        double maxTemperature = u0_;  /**< Maximum temperature for color scaling in visualization */

        // Render the temperature profiles at all time steps
        visualizer.renderMultiple2DTemperatureProfiles(temperatureProfiles, N_t_, N_s_, maxTemperature);
    }

}
