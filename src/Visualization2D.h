#ifndef VISUALIZATION2D_H
#define VISUALIZATION2D_H

#include "Visualization.h"
#include <vector>
#include <string>

/**
 * @brief A class for visualizing 2D heat equation results.
 */
namespace heat {

    class Visualization2D : public Visualization {
    public:
        /**
         * @brief Constructs a Visualization2D object with a title for the visualizations.
         *
         * @param title Title for the visualization.
         */
        Visualization2D(const char* title) : Visualization(title) {}

        /**
         * @brief Renders a 2D temperature grid.
         *
         * @param grid The 2D temperature grid to render.
         */
        void render(const std::vector<std::vector<double>>& grid) const;
    };

}

#endif
