#include <iostream>
#include <vector>
#include "Material.h"
#include "Result1D.h"
#include "Result2D.h"

int SDL_main(int argc, char* argv[]){
    (void)argc; 
    (void)argv; 
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
        int N_1D = 1001;        // Number of spatial points 
        int N_2D = 501;     // Number of spatial points (501 for x and 501 for y) 
                            // It does not fit the window height if we use 1001 for x and y, so we use 501 each
        int M = 100;        // Number of time steps
        double f = 1353.15;     // Heat source intensity factor in Kelvin

        // (1D) Iterate through each material and solve the heat equation 
        for (const auto& material : materials) {
            std::cout << "Simulating for material: " << material.name << "\n";

            // Set up the simulation for the current material
            heat::Result1D simulation1D(f, t_max, L, u0, N_1D, M, material);

            // Run the simulation
            simulation1D.runSimulation();
        }

        // (2D) Iterate through each material and solve the heat equation 
        for (const auto& material : materials) {
            std::cout << "Simulating for material: " << material.name << "\n";

            // Set up the simulation for the current material
            heat::Result2D simulation2D(f, t_max, L, u0, N_2D, M, material);

            // Run the simulation
            simulation2D.runSimulation();
        }

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;

}
