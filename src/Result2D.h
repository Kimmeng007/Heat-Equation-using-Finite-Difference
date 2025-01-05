#ifndef RESULT2D_H
#define RESULT2D_H

#include "HeatEquationSolver2D.h"
#include "Material.h"
#include "Visualization.h"
#include <vector>

namespace heat {

/**
 * @brief Handles the 2D visualization of heat equation results.
 */
class Result2D : public Visualization {
private:
    HeatEquationSolver2D& solver; /**< Reference to the heat equation solver */

public:
    /**
     * @brief Constructor for the Result2D class.
     * @param solver Reference to the HeatEquationSolver2D instance.
     * @param title Title of the visualization window.
     * @param width Width of the visualization window.
     * @param height Height of the visualization window.
     */
    Result2D(HeatEquationSolver2D& solver, const char* title, int width = 800, int height = 600);

    /**
     * @brief Visualizes the results of the heat equation simulation.
     */
    void visualize();
};

} // namespace heat

#endif // RESULT2D_H
