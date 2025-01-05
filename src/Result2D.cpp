#include "Result2D.h"

namespace heat {

    void Result2D::runSimulation() {
        // Create the heat source and solver
        Heatsource2D heatSource(t_max_, L_, f_);
        HeatEquationSolver2D solver(material_, heatSource, L_, t_max_, u0_, N_, M_);

        // Solve the 2D heat equation
        solver.solve();

        // Retrieve the full temperature matrix from the solver
        std::vector<std::vector<std::vector<double>>> temperatureGrids = solver.getAllTemperatureGrids();

        // Initialize the Visualization2D object for rendering
        Visualization2D visualizer("2D Heat Equation Visualization");

        // Compute the maximum temperature for color scaling
        double maxTemperature = u0_;
        for (const auto& timeStep : temperatureGrids) {
            for (const auto& row : timeStep) {
                for (double temp : row) {
                    if (temp > maxTemperature) {
                        maxTemperature = temp;
                    }
                }
            }
        }

        // Render each grid in the temperature matrix
        for (const auto& grid : temperatureGrids) {
            visualizer.renderGrid2D(grid, N_, N_, maxTemperature);

            // Add delay for visualization
            SDL_Delay(100);
        }
    }
}
