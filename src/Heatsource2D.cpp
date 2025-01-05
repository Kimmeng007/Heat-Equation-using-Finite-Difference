#include "Heatsource2D.h"

namespace heat {

    double Heatsource2D::F(double x, double y) const {
        if (x >= L_ / 6.0 && x <= 2 * L_ / 6.0 && y >= L_ / 6.0 && y <= 2 * L_ / 6.0) {
            return t_max_ * f_ * f_;
        } else if (x >= 4 * L_ / 6.0 && x <= 5 * L_ / 6.0 && y >= L_ / 6.0 && y <= 2 * L_ / 6.0) {
            return t_max_ * f_ * f_;
        } else if (x >= L_ / 6.0 && x <= 2 * L_ / 6.0 && y >= 4 * L_ / 6.0 && y <= 5 * L_ / 6.0) {
            return t_max_ * f_ * f_;
        } else if (x >= 4 * L_ / 6.0 && x <= 5 * L_ / 6.0 && y >= 4 * L_ / 6.0 && y <= 5 * L_ / 6.0) {
            return t_max_ * f_ * f_;
        } else {
            return 0.0; 
        }
    }

}
