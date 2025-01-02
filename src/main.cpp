#include <iostream>
#include <vector>
#include "Material.h"
#include "Result1D.h"
#include "Visualization.h"

int main(int argc, char* argv[]){
    // Materials from Table 2
    std::vector<heat::Material> materials = {
        heat::copper, 
        heat::iron, 
        heat::glass, 
        heat::polystyrene
    };

    // Simulation parameters
    double t_max = 10.0;  // Maximum simulation time in seconds
    double L = 1.0;       // Length of the domain in meters
    double u0 = 300.0;    // Initial temperature in Kelvin
    int N_s = 100;        // Number of spatial points
    int N_t = 100;        // Number of time steps
    double f = 100.0;     // Heat source intensity factor

    // Iterate through each material and solve the heat equation
    for (const auto& material : materials) {
        std::cout << "Simulating for material: " << material.name << "\n";

        // Set up the simulation for the current material
        heat::Result1D simulation(f, t_max, L, u0, N_s, N_t, material);

        // Run the simulation
        simulation.runSimulation();
    }

    return 0;
}
