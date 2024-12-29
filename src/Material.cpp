#include "material.h"
namespace heat{
    double Material::getThermalDiffusivity() const {
        return conductivity / (density * specificHeat);
    }

    std::ostream& operator<<(std::ostream& st, const Material& mat) {
        st << "Material: " << mat.name << "\n"
        << "  Thermal Conductivity (lambda): " << mat.conductivity << " W/(m.K)\n"
        << "  Density (rho): " << mat.density << " kg/m^3\n"
        << "  Specific Heat (c): " << mat.specificHeat << " J/(kg.K)\n"
        << "  Thermal Diffusivity (alpha): " << mat.getThermalDiffusivity() << " m^2/s\n";
        return st;
    }

    const Material copper("Copper", 389, 8940, 380);       /** Copper properties */
    const Material iron("Iron", 80.2, 7874, 440);          /** Iron properties */
    const Material glass("Glass", 1.2, 2530, 840);         /** Glass properties */
    const Material polystyrene("Polystyrene", 0.1, 1040, 1200); /** Polystyrene properties */
}
