#include <iostream>
#include <vector>

auto bfact( double& x, double& dwc, double& beta_i ){
  double c0=3.75, c1=1., c2=3.5156229, c3=3.0899424, c4=1.2067492, 
    c5=0.2659732, c6=0.0360768, c7=0.0045813, c8=0.39894228, c9=0.01328592, 
    c10=0.00225319, c11=0.00157565, c12=0.00916281, c13=0.02057706, 
    c14=0.02635537, c15=0.01647633, c16=0.00392377, c17=0.5, c18=0.87890594, 
    c19=0.51498869, c20=0.15084934, c21=0.02658733, c22=0.00301532, 
    c23=0.00032411, c24=0.02282967, c25=0.02895312, c26=0.01787654, 
    c27=0.00420059, c28=0.39894228, c29=0.03988024, c30=0.00362018, 
    c31=0.00163801, c32=0.01031555;
    
    double bessi0;
   // compute bessi0
    double y = x / c0;
    if ( y < 1.0 ){
      double u = y * y;
      bessi0=c1+u*(c2+u*(c3+u*(c4+u*(c5+u*(c6+u*c7)))));
    } else {
      double v = 1/y;
      bessi0=(c8+v*(c9+v*(c10+v*(-c11+v*(c12+v*(-c13+v*(c14+v*(-c15+v*c16))))))))/sqrt(x);
    }
    std::cout << bessi0 << std::endl;

    // compute bessi1
    double bessi1;
    if ( y <= 1.0 ){
      double u = y * y;
      bessi1 = (c17+u*(c18+u*(c19+u*(c20+u*(c21+u*(c22+u*c23))))))*x;
    } else {
      double v=1/y;
      bessi1=c24+v*(-c25+v*(c26-v*c27));
      bessi1=c28+v*(-c29+v*(-c30+v*(c31+v*(-c32+v*bessi1))));
      bessi1=bessi1/sqrt(x);
    }
    std::cout << bessi1 << std::endl;


    /*

   if (y.le.one) then
      u=y*y
      bessi1=   else
   endif
*/

  std::cout << "Hello, world" << std::endl;

}
