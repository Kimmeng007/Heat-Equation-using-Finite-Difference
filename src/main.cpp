#include <iostream>
#include <vector>
#include "Material.h"
#include "Result1D.h"
#include "Visualization.h"

int main(){
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
        heat::Result1D simulation(f, t_max, L, u0, N, M, material);

        // Run the simulation
        simulation.runSimulation();
    }

    return 0;
}
