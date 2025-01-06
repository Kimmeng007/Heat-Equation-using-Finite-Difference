#ifndef HEAT_SOURCE_H
#define HEAT_SOURCE_H

/**
 * @brief class representing the heat source F(x,t)
 */
namespace heat{
    
    class Heatsource1D{
        
    private:
        double t_max_; /** Maximum time for simulation */
        double L_; /** Length of the bar */
        double f_; /** Scaling factor for heat source */

    public:   
        /**
         * @brief initialize the the heat source parameters
         * @param t_max : Maximum simulation time
         * @param L : Length of the bar
         * @param f : Scaling factor for heat source
         */
        Heatsource1D(double t_max, double L, double f): t_max_(t_max), L_(L), f_(f){}

        /**
         * @brief compute the heat source value at position x and time t
         * @param x : Position along the bar
         * @param t : Current time
         * @return Heat source value F(x)
         */
        double F(double x) const;
    };

}

#endif