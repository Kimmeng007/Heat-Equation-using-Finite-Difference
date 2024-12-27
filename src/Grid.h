#ifndef GRID_H
#define GRID_H

/**
 * @brief class for spatial and temporal grid discretization
 */
class Grid{
    public: 
    int Nx_; /** Number of spatial points */
    int Nt_; /** Number of time steps */
    double dx_; /** Spatial step size */
    double dt_; /** Time step size */
    double L_; /** Length of the bar */
    double t_max_; /** Maximum simulation time */

    /**
     * @brief initialization
     * @param Nx : Number of spatial points
     * @param Nt : Number of time steps
     * @param L : Length of the bar
     * @param t_max : maximum simulation time
     */
    Grid(int Nx, int Nt, double L, double t_max): Nx_(Nx), Nt_(Nt), L_(L), t_max_(t_max){
        dx_ = L_ / (Nx_ - 1);
        dt_ = t_max_ / Nt_;
    }
};

#endif