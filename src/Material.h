#ifndef MATERIAL_H
#define MATERIAL_H

/**
 * @brief class representing material properties
 * There are lambda_ (thermal conductivuty), rho_ (density) and c_ (heat capacity)
 */
class Material{
    public:
    double lambda_; /** W/m.K */
    double rho_; /** kg/m^3 */
    double c_; /** J/kg.K */

    /**
     * @brief initialize material properties
     * @param lambda : Thermal conductivity
     * @param rho : Density
     * @param c : Heat capacity
     */
    Material(double lambda, double rho, double c): lambda_(lambda), rho_(rho), c_(c){}
};


#endif