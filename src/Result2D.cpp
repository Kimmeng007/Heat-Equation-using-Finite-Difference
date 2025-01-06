#include "Result2D.h"
#include <iostream>
#include <vector>

namespace heat {

    void Result2D::runSimulation() {

        Heatsource2D heatSource(t_max_, L_, f_);  /**< Initialize the heat source with the appropriate parameters */

        HeatEquationSolver2D solver_(material_, heatSource, L_, t_max_, u0_, N_, M_); /**< Initialize the HeatEquationSolver1D with the provided parameters */

        solver_.solve(); /**< Solve the heat equation using the finite difference method */

        Visualization2D visualizer; /**< Initialize the Visualization object for rendering the results */

        const auto& results = solver_.getAllTemperatureGrids(); /**< Store all Temperatuer Grid */

        visualizer.showAllFrames(results, M_); /**< Visualize all frames */
        
    }


}
