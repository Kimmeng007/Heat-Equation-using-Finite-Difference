#include "Heatsource1D.h"

namespace heat{

    double Heatsource1D::F(double x) const{
        /** Region 1 */
        if(x >= L_ / 10 && x <= 2*L_/10){
            return t_max_ * f_ * f_;
        }
        
        /** Region 2 */
        else if(x >= 5*L_/10 && x <= 6*L_/10){
            return 0.75*t_max_ * f_ * f_;
        }

        else{
            return 0.0;
        }
    }
}