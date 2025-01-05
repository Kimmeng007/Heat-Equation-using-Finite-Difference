#include "Visualization2D.h"

Visualization2D::Visualization2D(const char* title, int width, int height)
    : Visualization(title, width, height) {}

void Visualization2D::renderGrid2D(const std::vector<std::vector<double>>& temperatureGrid, int rows, int cols, double maxTemperature) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    int cellWidth = windowWidth / cols;
    int cellHeight = windowHeight / rows;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            double temp = temperatureGrid[i][j];
            SDL_Color color = getTemperatureColor(temp, maxTemperature);
            SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

            SDL_Rect cell = {j * cellWidth, i * cellHeight, cellWidth, cellHeight};
            SDL_RenderFillRect(renderer, &cell);
        }
    }

    SDL_RenderPresent(renderer);
}
