#include <iostream>
#include <vector>

auto bt ( int j, double& pj, const double& x ){
  /* This calculates the statistical weight factor Pj for cold hydrogen or 
   * deuterium calculation. This goes in Eq. 567 - 568, and is called by the
   * betaLoop function.
   * 
   *                  ( 2j + 1 ) * exp( - j*(j+1)*x ) 
   * Pj = -----------------------------------------------------------------
   *      (2*1+1)e^(-1*2*x) + (2*3+1)e^(-3*4*x) + (2*5+1)e^(-5*6*x) +...
   *
   * if j is odd ( ortho hydrogen or para deuterium )
   *
   *                  ( 2j + 1 ) * exp( - j*(j+1)*x ) 
   * Pj = -----------------------------------------------------------------
   *      (2*2+1)e^(-2*3*x) + (2*4+1)e^(-4*5*x) + (2*6+1)e^(-6*7*x) +...
   * if j is even ( para hydrogen or ortho deuterium )
   *
   */

  double b = 0;
  // Loop either 0 --> 18 or 1 --> 19
  for ( auto k = j%2; k < 20; k += 2 ){
    b += (2*k+1) * exp( -k * (k+1) * x / 2 );
  }
  pj  =  (2*j+1) * exp( -j * (j+1) * x / 2 ) / ( 2 * b );
}

