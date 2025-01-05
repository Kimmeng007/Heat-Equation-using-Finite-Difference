#include "Result2D.h"
#include "SDL.h"

namespace heat {

/**
 * @brief Constructor for the Result2D class.
 * @param solver Reference to the HeatEquationSolver2D instance.
 * @param title Title of the visualization window.
 * @param width Width of the visualization window.
 * @param height Height of the visualization window.
 */
Result2D::Result2D(HeatEquationSolver2D& solver, const char* title, int width, int height)
    : Visualization(title, width, height), solver(solver) {}

/**
 * @brief Visualizes the results of the heat equation simulation.
 */
void Result2D::visualize() {
    const auto& grids = solver.getAllTemperatureGrids();
    int numTimeSteps = grids.size();
    int spatialDivisions = grids[0].size();

    for (int t = 0; t < numTimeSteps; ++t) {
        // Extract the 2D grid for the current timestep.
        const auto& grid = grids[t];
        std::vector<double> flattenedGrid;
        double maxTemperature = 0.0;

        for (const auto& row : grid) {
            for (double temp : row) {
                flattenedGrid.push_back(temp);
                if (temp > maxTemperature) {
                    maxTemperature = temp;
                }
            }
        }

        render2DTemperatureProfile(flattenedGrid.data(), spatialDivisions * spatialDivisions, maxTemperature);
        SDL_Delay(100); // Delay for smooth visualization
    }
}

} // namespace heat
