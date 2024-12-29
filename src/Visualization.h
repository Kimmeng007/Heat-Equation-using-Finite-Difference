#ifndef VISUALIZATION_H
#define VISUALIZATION_H


#include <SDL2/SDL.h>
#include <iostream>

/**
 * @brief A class to handle the visualization of temperature profiles using SDL
 */
class Visualization{

private:
    const char* windowTitle; /** Title of the SDL window */
    SDL_Window* window; /** Pointer to the SDL window */
    SDL_Renderer* renderer; /** Pointer to the SDL renderer */
    int windowWidth; /** Width of the SDL window */
    int windowHeight; /** Height of the SDL window */

    /**
     * @brief Initializes SDL and creates the window and renderer
     */
    void initializeSDL();

    /**
     * @brief Cleans up SDL resources
     */
    void cleanUp();
    
public:
    /**
     * @brief a new Visualization object
     * 
     * @param title The title of the window 
     * @param width The width of the window (default 800)
     * @param height The height of the window (default 600)
     */
    Visualization(const char* title, int width = 800, int height = 600);

    /**
     * @brief cleans up SDL resources
     */
    ~Visualization();

    /**
     * @brief Starts the SDL event loop for handling rendering and events
     */
    void startEventLoop();

    /**
     * @brief Renders a 2D temperature profile for a single time step
     * 
     * @param temperature : Array of temperature values
     * @param size : The number of spatial divisions (length of the array)
     * @param maxTemperature : The maximum temperature value for color scaling
     */
    void render2DTemperatureProfile(const double* temperature, int size, double maxTemperature);

    /**
     * @brief Renders multiple 2D temperature profiles over time
     * 
     * @param temperatureProfiles : Array of temperature arrays for different time steps
     * @param numTimeSteps : The number of time steps
     * @param spatialDivisions : The number of spatial divisions in each temperature profile
     * @param maxTemperature : The maximum temperature value for color scaling
     */
    void renderMultiple2DTemperatureProfiles(const double** temperatureProfiles, int numTimeSteps, int spatialDivisions, double maxTemperature);

    /**
     * @brief Calculates a color representation for a given temperature
     * 
     * @param temperature : The temperature value
     * @param maxTemperature : The maximum temperature value for scaling
     * @return SDL_Color The color representing the temperature
     */
    SDL_Color getTemperatureColor(double temperature, double maxTemperature);
};

#endif
