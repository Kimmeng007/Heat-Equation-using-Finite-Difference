#include "Visualization.h"
#include <vector>

namespace heat{
    // Initializes SDL and sets up the window and renderer
    void Visualization::initializeSDL() {
        if (SDL_Init(SDL_INIT_VIDEO) != 0) {
            std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
            exit(1);
        }
        window = SDL_CreateWindow(windowTitle, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_SHOWN);
        if (!window) {
            std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
            SDL_Quit();
            exit(1);
        }
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if (!renderer) {
            std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
            SDL_DestroyWindow(window);
            SDL_Quit();
            exit(1);
        }
    }

    // Cleans up SDL resources
    void Visualization::cleanUp() {
        if (renderer) SDL_DestroyRenderer(renderer);
        if (window) SDL_DestroyWindow(window);
        SDL_Quit();
    }

    // Constructor
    Visualization::Visualization(const char* title, int width, int height)
        : windowTitle(title), window(nullptr), renderer(nullptr), windowWidth(width), windowHeight(height) {
        initializeSDL();
    }

    // Destructor
    Visualization::~Visualization() {
        cleanUp();
    }

    // Starts the SDL event loop
    void Visualization::startEventLoop() {
        bool quit = false;
        SDL_Event e;
        while (!quit) {
            while (SDL_PollEvent(&e)) {
                if (e.type == SDL_QUIT) quit = true;
            }
        }
    }

    // Renders a 2D temperature profile for a single time step
    void Visualization::render2DTemperatureProfile(const double* temperature, int size, double maxTemperature) {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Draw temperature profile lines
        for (int i = 0; i < size - 1; ++i) {
            SDL_Color color = getTemperatureColor(temperature[i], maxTemperature);
            SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

            int x1 = (i * windowWidth) / size;
            int x2 = ((i + 1) * windowWidth) / size;
            int y1 = windowHeight - (int)((temperature[i] / maxTemperature) * windowHeight);
            int y2 = windowHeight - (int)((temperature[i + 1] / maxTemperature) * windowHeight);

            SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
        }
        SDL_RenderPresent(renderer);
    }

    // Renders multiple 2D temperature profiles over time
    void Visualization::renderMultiple2DTemperatureProfiles(const double** temperatureProfiles, int numTimeSteps, int spatialDivisions, double maxTemperature) {
        for (int t = 0; t < numTimeSteps; ++t) {
            render2DTemperatureProfile(temperatureProfiles[t], spatialDivisions, maxTemperature);
            SDL_Delay(100); // Delay for smooth visualization
        }
    }

    void Visualization::render2DTemperatureProfile(const double* temperature, int rows, int cols, double maxTemperature) {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        int cellWidth = windowWidth / cols;
        int cellHeight = windowHeight / rows;

        for (int row = 0; row < rows; ++row) {
            for (int col = 0; col < cols; ++col) {
                double temp = temperature[row * cols + col];
                SDL_Color color = getTemperatureColor(temp, maxTemperature);
                SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

                SDL_Rect cellRect = { col * cellWidth, row * cellHeight, cellWidth, cellHeight };
                SDL_RenderFillRect(renderer, &cellRect);
            }
        }

        SDL_RenderPresent(renderer);
    }

    // Calculates a color representation for a given temperature
    SDL_Color Visualization::getTemperatureColor(double temperature, double maxTemperature) {
        // Normalize the temperature to [0, 1]
        double normalizedTemp = temperature / maxTemperature;
        if (normalizedTemp < 0.0) normalizedTemp = 0.0;
        if (normalizedTemp > 1.0) normalizedTemp = 1.0;

        SDL_Color color;
        color.r = (Uint8)(normalizedTemp * 255);
        color.g = (Uint8)((1.0 - normalizedTemp) * 255);
        color.b = 0;
        color.a = 255;

        return color;
    }

}
