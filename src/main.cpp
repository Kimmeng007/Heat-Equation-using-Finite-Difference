#include <iostream>
#include <vector>
#include "Material.h"
#include "Result1D.h"
// #include "Visualization.h"
// #include <SDL2/SDL.h>
#include "Result2D.h"
#include "Visualization2D.h"

int SDL_main(int argc, char* argv[]){
    try{
        // Materials from Table 2
        std::vector<heat::Material> materials = {
            heat::copper, 
            heat::iron, 
            heat::glass, 
            heat::polystyrene
        };

        // Simulation parameters
        double t_max = 16.0;  // Maximum simulation time in seconds
        double L = 1.0;       // Length of the domain in meters
        double u0 = 286.15;    // Initial temperature in Kelvin
        int N = 1001;        // Number of spatial points
        int M = 100;        // Number of time steps
        double f = 1353.15;     // Heat source intensity factor in Kelvin

        // Iterate through each material and solve the heat equation
        for (const auto& material : materials) {
            std::cout << "Simulating for material: " << material.name << "\n";

            // Set up the simulation for the current material
            heat::Result2D simulation(f, t_max, L, u0, N, M, material);
            // heat::Result2D simulation(f, t_max, L, u0, N, M, material);

            // Run the simulation
            simulation.runSimulation();
        }

        // // Create a static array to hold the temperature profiles for each time step
        // const double* temperatureProfiles[M];  /**< Holds temperature profiles at different time steps */

        // // Extract the temperature profile at each time step from the solver
        // for (int t = 0; t < M; ++t) {
        //     temperatureProfiles[t] = solver.getTemperatureAtTime(t);  /**< Access the temperature profile at time step t */
        //     std::cout << "Timestep =  " << t << std::endl;
        //     std::cout << *temperatureProfiles[t] << std::endl;
        // }

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;

}
