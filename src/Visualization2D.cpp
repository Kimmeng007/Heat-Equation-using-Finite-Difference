#include "Visualization2D.h"
#include <iostream>
#include <iomanip>

namespace heat {

    void Visualization2D::render(const std::vector<std::vector<double>>& grid) const {
        std::cout << "2D Heat Equation Solution Animation"<< "\n";

        // Determine the grid size
        size_t rows = grid.size();
        size_t cols = grid[0].size();

        // Render the grid as a simple ASCII visualization
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                // Scale temperature for visualization (e.g., normalize to [0, 9])
                int scaledTemp = static_cast<int>(9 * (grid[i][j] / 100)); // Adjust scale as needed
                std::cout << std::setw(2) << scaledTemp;
            }
            std::cout << "\n";
        }
    }

}
