#ifndef HEAT_SOURCE_2D_H
#define HEAT_SOURCE_2D_H

/**
 * @brief Class representing the heat source F(x, y, t)
 */
namespace heat {

    class Heatsource2D {

    private:
        double t_max_; /**< Maximum time for simulation */
        double L_;     /**< Length of the domain */
        double f_;     /**< Scaling factor for heat source */

    public:
        /**
         * @brief Initialize the heat source parameters
         * @param t_max Maximum simulation time
         * @param L Length of the domain
         * @param f Scaling factor for heat source
         */
        Heatsource2D(double t_max, double L, double f) : t_max_(t_max), L_(L), f_(f) {}

        /**
         * @brief Compute the heat source value at position (x, y) and time t
         * @param x Position along the x-axis
         * @param y Position along the y-axis
         * @param t Current time
         * @return Heat source value F(x, y)
         */
        double F(double x, double y) const;
    };

}

#endif // HEAT_SOURCE_2D_H
