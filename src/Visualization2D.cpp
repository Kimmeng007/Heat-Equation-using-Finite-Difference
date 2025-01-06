#include "Visualization2D.h"
#include <iostream>
#include <algorithm>

namespace heat {

    Visualization2D::Visualization2D(int windowWidth, int windowHeight)
        : windowWidth_(windowWidth), windowHeight_(windowHeight), window_(nullptr), renderer_(nullptr) {
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            throw std::runtime_error("Failed to initialize SDL");
        }

        window_ = SDL_CreateWindow("2D Heat Equation Visualization2D", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth_, windowHeight_, SDL_WINDOW_SHOWN);
        if (!window_) {
            throw std::runtime_error("Failed to create SDL window");
        }

        renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);
        if (!renderer_) {
            throw std::runtime_error("Failed to create SDL renderer");
        }
    }


    Visualization2D::~Visualization2D() {
        SDL_DestroyRenderer(renderer_);
        SDL_DestroyWindow(window_);
        SDL_Quit();
    }

    void Visualization2D::computeTemperatureRange(const std::vector<std::vector<std::vector<double>>>& frames) {
        // Initialize minTemp_ and maxTemp_ with very large and very small values
        minTemp_ = 1e10;  // Arbitrarily large value for minTemp_
        maxTemp_ = -1e10; // Arbitrarily small value for maxTemp_

        for (const auto& frame : frames) {
            for (const auto& row : frame) {
                for (double temp : row) {
                    // Update minTemp_ and maxTemp_
                    if (temp < minTemp_) minTemp_ = temp;
                    if (temp > maxTemp_) maxTemp_ = temp;
                }
            }
        }
    }

    void Visualization2D::showFrame(const std::vector<std::vector<double>>& frame) {
        bool running = true;
        SDL_Event event;

        while (running) {
            // Poll SDL events
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) {
                    running = false;
                    break;
                }
            }

            // Render the frame
            SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
            SDL_RenderClear(renderer_);

            // Map temperatures to colors and render the frame
            for (size_t i = 0; i < frame.size(); ++i) {
                for (size_t j = 0; j < frame[i].size(); ++j) {
                    double normalizedTemp = (frame[i][j] - minTemp_) / (maxTemp_ - minTemp_);
                    uint8_t colorValue = static_cast<uint8_t>(normalizedTemp * 255);
                    SDL_SetRenderDrawColor(renderer_, colorValue, 0, 255 - colorValue, 255);

                    SDL_Rect pixel = {static_cast<int>(j), static_cast<int>(i), 1, 1};
                    SDL_RenderFillRect(renderer_, &pixel);
                }
            }

            SDL_RenderPresent(renderer_);

            // SDL_Delay(5); 
            running = false; 
        }
    }

    void Visualization2D::showAllFrames(const std::vector<std::vector<std::vector<double>>>& frames, int timestep) {
        computeTemperatureRange(frames); 

        for (int i = 0; i < timestep; i ++) {
            std::cout << "Timestep " << i + 1 << " of " << timestep << std::endl;
            showFrame(frames[i]);
        }
    }

}
