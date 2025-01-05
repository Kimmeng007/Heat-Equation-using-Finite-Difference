#ifndef VISUALIZATION2D_H
#define VISUALIZATION2D_H

#include "Visualization.h"
#include <vector>

/**
 * @brief A class to handle the visualization of 2D temperature grids using SDL
 */
class Visualization2D : public Visualization {
public:
    /**
     * @brief Construct a new Visualization2D object
     * 
     * @param title The title of the window
     * @param width The width of the window (default 800)
     * @param height The height of the window (default 600)
     */
    Visualization2D(const char* title, int width = 800, int height = 600);

    /**
     * @brief Renders a 2D grid temperature profile
     * 
     * @param temperatureGrid 2D array representing the temperature grid
     * @param rows Number of rows in the grid
     * @param cols Number of columns in the grid
     * @param maxTemperature Maximum temperature for color scaling
     */
    void renderGrid2D(const std::vector<std::vector<double>>& temperatureGrid, int rows, int cols, double maxTemperature);
};

#endif
