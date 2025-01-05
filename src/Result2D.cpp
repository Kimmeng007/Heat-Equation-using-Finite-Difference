#include "Result2D.h"

namespace heat {

    void Result2D::runSimulation() {
        // Create the heat source and solver
        Heatsource2D heatSource(t_max_, L_, f_);
        HeatEquationSolver2D solver(material_, heatSource, L_, t_max_, u0_, N_, M_);

        // Solve the 2D heat equation
        solver.solve();

        // Retrieve the full temperature grids
        auto temperatureGrids = solver.getAllTemperatureGrids();

        // Initialize the Visualization2D object
        Visualization2D visualizer("2D Heat Equation Simulation");

        // Loop through time steps and visualize
        for (size_t t = 0; t < temperatureGrids.size(); ++t) {
            std::cout << "Visualizing time step " << t << "...\n";
            visualizer.render(temperatureGrids[t]);
        }
    }

}
