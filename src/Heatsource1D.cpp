#include "Heatsource1D.h"

namespace heat{
    
    double Heatsource1D::F(double x, double t) const{
        if(t >= 0 && t<= t_max_){
            /** Region 1 */
            if(x >= L_ / 10 && x <= 2*L_/10){
                return t_max_ * f_ * f_;
            }
            
            /** Region 2 */
            else if(x >= 5*L_/10 && x <= 6*L_/10){
                return 0.75*t_max_ * f_ * f_;
            }
        }

        /** Outside the defined regions */
        return 0.0;
    }
}