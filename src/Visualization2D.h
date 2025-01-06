#ifndef Visualization2D_H
#define Visualization2D_H

#include <vector>
#include <SDL2/SDL.h>

namespace heat {

    /**
     * @brief Handles the Visualization2D of 2D temperature grids using SDL.
     */
    class Visualization2D {
    private:
        int windowWidth_;        /**< Width of the SDL window */
        int windowHeight_;       /**< Height of the SDL window */
        SDL_Window* window_;     /**< SDL window pointer */
        SDL_Renderer* renderer_; /**< SDL renderer pointer */
        double minTemp_;
        double maxTemp_;

    public:
        /**
         * @brief Constructor to initialize the Visualization2D system.
         * 
         * @param windowWidth Width of the SDL window
         * @param windowHeight Height of the SDL window
         */
        Visualization2D(int windowWidth = 503, int windowHeight = 503);

        /**
         * @brief Destructor to deallocate resources used by SDL.
         */
        ~Visualization2D();

        /**
         * @brief Compute minimum and maximum temperature for normalization color of temperature step
         * 
         * @param frames A 3D vector containing multiple 2D grids representing temperature values at different timesteps. 
         *               Each grid corresponds to a frame.
         */
        void computeTemperatureRange(const std::vector<std::vector<std::vector<double>>>& frames);

        /**
         * @brief Displays a single temperature frame.
         * 
         * @param frame A 2D vector representing the temperature grid at a specific timestep. 
         *              Each element corresponds to a temperature value at a specific (x, y) position in the grid.
         */
        void showFrame(const std::vector<std::vector<double>>& frame);

        /**
         * @brief Displays a sequence of temperature frames over time.
         * 
         * @param frames A 3D vector containing multiple 2D grids representing temperature values at different timesteps. 
         *               Each grid corresponds to a frame.
         * @param timestep The total number of timesteps in the simulation (M).
         */
        void showAllFrames(const std::vector<std::vector<std::vector<double>>>& frames, int timestep);

        /**
         * @brief Clears the window and renderer.
         */
        void clear() const;

        /**
         * @brief Displays the rendered content on the screen.
         */
        void display() const;

        /**
         * @brief Delay to control frame rate.
         * 
         * @param milliseconds Duration of the delay in milliseconds
         */
        void delay(int milliseconds) const;

    };

}

#endif
