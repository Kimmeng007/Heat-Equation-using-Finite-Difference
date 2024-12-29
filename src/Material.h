#ifndef MATERIAL_H
#define MATERIAL_H

#include <iostream>

/**
 * @brief Represents the physical properties of a material related to heat transfer
 *
 * This struct models the thermal properties of a material, including its name, thermal conductivity,
 * density, and specific heat capacity. These properties are crucial in solving heat transfer problems.
 */
namespace heat{
    struct Material{
        const char* name; /** The name of the material */
        double conductivity; /** Thermal conductivity of the material (lambda) */
        double density; /** Density of the material (rho)*/
        double specificHeat; /** Heat capacity of the material (c) */

        /**
         * @brief New Material object
         * 
         * @param name : The name of the material
         * @param conductivity : The thermal conductivity of the material (lambda)
         * @param density : The density of the material (rho)
         * @param specificHeat : The specific heat capacity of the material (c)
         */
        Material(const char* name, double conductivity, double density, double specificHeat): name(name), conductivity(conductivity), density(density), specificHeat(specificHeat){}

        /**
         * @brief Calculate and return the thermal diffusivity of the material
         * @return double The thermal diffusivity of the material
         */
        double getThermalDiffusivity() const;

        /**
         * @brief Overload the stream insertion operator to output the details of the material
         * 
         * @param st :  Reference to the output stream object
         * @param mat : Reference to the Material object
         * @return std::ostream& Reference to the output stream object
         */
        friend std::ostream& operator<<(std::ostream& st, const Material& mat);
    };
    // Predefined materials
    extern const Material copper; /** Represents the material Copper with predefined properties */
    extern const Material iron; /** Represents the material Iron with predefined properties */
    extern const Material glass; /** Represents the material Glass with predefined properties */
    extern const Material polystyrene; /** Represents the material Polystyrene with predefined properties */
}

#endif