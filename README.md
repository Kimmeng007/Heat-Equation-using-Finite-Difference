# Heat Equation 

## Description
This project implements a **numerical simulation of the heat equation** in **1D (rod)** and **2D (plate)** using the **implicit finite difference method**.  
The goal is to model **heat propagation** in various materials and observe the **temperature evolution** under the influence of localized heat sources.

The code is developed in **C++**, with **graphical animations rendered using the SDL library** to visualize the results.

---

## Scientific Background
The heat equation is a partial differential equation defined as:

$$
\frac{\partial u}{\partial t} = \frac{\lambda}{\rho c} \nabla^2 u + \frac{F(x, y)}{\rho c}
$$

where:
- $$ u(x, t) $$: temperature field  
- $ \lambda $: thermal conductivity  
- $$ \rho \): density of the material  
- \( c \): specific heat capacity  
- \( F(x, y) \): heat source term  

---

## Numerical Methods
- **Spatial and temporal discretization** using uniform grids  
- **Implicit (Backward Euler) scheme** for time stepping — ensuring stability  
- **Thomas algorithm** for efficiently solving tridiagonal systems  
- **Dynamic memory management** with `std::vector` to prevent leaks  
- **Interactive visualization** with SDL  

---

## Case Studies
### 1. 1D Rod
- Mixed boundary conditions (Neumann + Dirichlet)  
- Variable heat sources depending on position  
- Tridiagonal system solved at each time step  

### 2. 2D Plate
- Symmetric boundary conditions on all edges  
- Four localized heat zones  
- Problem separated into 1D tridiagonal systems (x and y directions)  

---

## Results
The simulations show the heat diffusion process across different materials: **copper, iron, glass, and polystyrene**.  
The results indicate the following order of thermal conductivity:

> **Copper > Iron > Glass > Polystyrene**

Animations use a color scale from **green (low temperature)** to **red (high temperature)** to visualize temperature evolution over time.

---

## Tools and Technologies
- **Language:** C++  
- **Graphics Library:** SDL  
- **Compiler:** g++ / clang++  
- **Numerical Methods:** Finite differences, Backward Euler, Thomas algorithm  

---

## Run Instructions
To compile the code:
1. Navigate to src : cd src
2. This command :  g++ -g -Wall -Wextra -o prog *.cpp $(pkg-config --cflags --libs sdl2)
3. To display: ./prog.exe

## Authors
HONG Kimmeng, KOH Tito \\
Supervisor: Prof. Vincent Torri \\
École Nationale Supérieure d’Informatique pour l’Industrie et l’Entreprise (ENSIIE) \\
Academic Year: 2024–2025

