#define CATCH_CONFIG_MAIN
#include <iostream>
#include <vector>
#include "trans/trans.h"
#include "catch.hpp"
#include "generalTools/testing.h"
#include <range/v3/all.hpp>


TEST_CASE( "trans" ){

  std::vector<double> alpha {0.10, 0.20, 0.40, 0.50}, beta {0.15, 0.18, 0.22}, correct;

  double transWgt = 0.05, delta = 9e-2, c, temp = 296, 
    sc = 1.0, scaling = 1.0, lambda_s = 0.23, tbeta = 0.95, 
    effectiveTemp = 570;
  transWgt = 0.5;
  tbeta = 0.5;

  std::vector<double> sab = ranges::view::iota(1,int(alpha.size()*beta.size()+1))
                          | ranges::view::transform([](auto x){return 1e-3*x;});

  GIVEN( "no diffusion" ){
    c = 0.0;

    WHEN( "translational weight is small" ){
      transWgt = 0.05; 
      tbeta = 0.95;
      trans( alpha, beta, transWgt, delta, c, sc, scaling, lambda_s, tbeta, 
             effectiveTemp, temp,  sab );
      correct = { 1.359940, 8.42100E-1, 3.86253E-1, 1.648607, 1.310258, 
      8.96480E-1, 1.473408, 1.321628, 1.104853, 1.362848, 1.253072, 1.091452 };
      THEN( "S(a,b) and effective temperature outputs are correct" ){
        REQUIRE(ranges::equal(sab,correct,equal));
        REQUIRE( 556.3 == Approx(effectiveTemp).epsilon(1e-6) );
      } // THEN
    } // WHEN
    WHEN( "translational weight is large" ){
      transWgt = 0.5; 
      tbeta = 0.5;
      trans( alpha, beta, transWgt, delta, c, sc, scaling, lambda_s, tbeta, 
             effectiveTemp, temp,  sab );
      correct = {1.170449, 1.132933, 1.066604, 8.459466E-1, 8.383600E-1, 
      8.20872E-1, 5.737014E-1, 5.764080E-1, 5.751139E-1, 4.984466E-1, 
      5.01821E-1, 5.038771E-1 };
      THEN( "S(a,b) and effective temperature outputs are correct" ){
        REQUIRE(ranges::equal(sab,correct,equal));
        REQUIRE( 433 == Approx(effectiveTemp).epsilon(1e-6) );
      } // THEN
    } // WHEN
    WHEN( "alpha and beta values are very small" ){
      alpha = {0.001, 0.002, 0.004, 0.005};
      beta  = {0.0015,0.0018,0.0022};
      transWgt = 0.05; 
      tbeta = 0.95;
      trans( alpha, beta, transWgt, delta, c, sc, scaling, lambda_s, tbeta, 
             effectiveTemp, temp,  sab );
      correct = { 39.43256, 39.27908, 38.93495, 28.02756, 27.99394, 27.84877, 
                  19.83799, 19.81991, 19.79582, 17.74976, 17.73555, 17.71663 }; 
      THEN( "S(a,b) and effective temperature outputs are correct" ){
        REQUIRE(ranges::equal(sab,correct,equal));
        REQUIRE( 556.3 == Approx(effectiveTemp).epsilon(1e-6) );
      } // THEN
    } // WHEN

    WHEN( "translational weight is small" ){
      alpha = {0.001,0.002,0.004,0.005};
      beta = {0.0015,0.0018,0.0022};
      std::vector<double> sab = ranges::view::iota(1,int(alpha.size()*beta.size()+1))
                              | ranges::view::transform([](auto x){return 1e-3*x;});


      transWgt = 0.05; 
      tbeta = 0.95;
      trans( alpha, beta, transWgt, delta, c, sc, scaling, lambda_s, tbeta, 
             effectiveTemp, temp,  sab );
      correct = { 39.43256, 39.27908, 38.93495, 28.02756, 27.99394,  27.84877, 
                  19.83799, 19.81991, 19.79582, 17.74976,  17.73555, 17.71663};
      THEN( "S(a,b) and effective temperature outputs are correct" ){
        REQUIRE(ranges::equal(sab,correct,equal));
        REQUIRE( 556.3 == Approx(effectiveTemp).epsilon(1e-6) );
      } // THEN
    } // WHEN

    WHEN( "translational weight is larger and more alpha,beta values" ){
      alpha =      {1e-5,1e-4,1e-3,1e-2,1e-1,1.0,10,20,50};
      beta  = {0.00,1e-5,1e-4,1e-3,1e-2,1e-1,1.0,10,20,50};
      std::vector<double> sab = ranges::view::iota(1,int(alpha.size()*beta.size()+1))
                              | ranges::view::transform([](auto x){return 1e-3*x;});
 
      transWgt = 0.2; 
      tbeta = 0.8;
      
      temp = 596.0;
      AND_WHEN( "alpha and beta value are not scaled (lat=0)" ){

        trans( alpha, beta, transWgt, delta, c, sc, scaling, lambda_s, tbeta, 
               effectiveTemp, temp,  sab );
        correct = {  1.994744E2, 1.994727E2, 1.992349E2, 1.761239E2, 5.65913E-3, 
        5.99113E-3, 6.99912E-3, 7.99998E-3, 8.99994E-3, 5.99283E-3, 6.309085E1, 
        6.309046E1, 6.308549E1, 6.233784E1, 1.817689E1, 1.59737E-2, 1.69973E-2, 
        1.79999E-2, 1.89998E-2, 1.06677E-2, 1.996615E1, 1.996604E1, 1.996493E1, 
        1.994924E1, 1.770957E1, 2.59956E-2, 2.69917E-2, 2.79998E-2, 2.89994E-2, 
        1.52989E-2, 6.32454940, 6.32454830, 6.32423750, 6.32079240, 6.27130850, 
        1.92746280, 3.69731E-2, 3.79994E-2, 3.89981E-2, 2.12555E-2, 1.98168440, 
        1.98172490, 1.98178970, 1.98210100, 1.98488020, 1.83899950, 4.69186E-2, 
        4.79968E-2, 4.89932E-2, 2.79239E-2, 5.18916E-1, 5.18954E-1, 5.19008E-1, 
        5.19229E-1, 5.21116E-1, 5.38813E-1, 2.80139E-1, 5.79755E-2, 5.89686E-2, 
        3.85062E-2, 3.31777E-2, 3.32007E-2, 3.32249E-2, 3.32616E-2, 3.34242E-2, 
        3.49013E-2, 5.02640E-2, 6.77807E-2, 6.87878E-2, 5.96199E-2, 1.25262E-2, 
        1.25401E-2, 1.25545E-2, 1.25735E-2, 1.26395E-2, 1.32000E-2, 1.98954E-2, 
        7.70064E-2, 7.85919E-2, 7.41241E-2, 2.18543E-3, 2.18853E-3, 2.19170E-3, 
        2.19566E-3, 2.20750E-3, 2.30258E-3, 3.53872E-3, 5.08625E-2, 8.72796E-2, 
        8.86631E-2 };
        THEN( "S(a,b) and effective temperature outputs are correct" ){
          REQUIRE(ranges::equal(sab,correct,equal));
          REQUIRE( 575.2 == Approx(effectiveTemp).epsilon(1e-6) );
        } // THEN
      } // AND WHEN
      AND_WHEN( "alpha and beta value are not scaled (lat=1)" ){
        sc = 0.492608069; scaling = 0.492608069;
        trans( alpha, beta, transWgt, delta, c, sc, scaling, lambda_s, tbeta, 
               effectiveTemp, temp,  sab );
        correct = { 2.842070E2, 2.842058E2, 2.840389E2, 2.673005E2, 6.08110E-1, 
        5.98738E-3, 6.99875E-3, 7.99997E-3, 8.99991E-3, 5.70052E-3, 8.988626E1, 
        8.988598E1, 8.988249E1, 8.935613E1, 4.868566E1, 1.59626E-2, 1.69962E-2, 
        1.79999E-2, 1.89997E-2, 1.04688E-2, 2.844125E1, 2.844117E1, 2.844039E1, 
        2.842937E1, 2.680892E1, 8.75471E-2, 2.69882E-2, 2.79998E-2, 2.89992E-2, 
        1.52096E-2, 9.00973040, 9.00972940, 9.00950810, 9.00705570, 8.97237470, 
        5.00259950, 3.69622E-2, 3.79992E-2, 3.89974E-2, 2.08840E-2, 2.84636880, 
        2.84640640, 2.846444E0, 2.84648650, 2.84657030, 2.73906810, 5.44531E-2, 
        4.79963E-2, 4.89909E-2, 2.73327E-2, 8.29348E-1, 8.29386E-1, 8.29436E-1, 
        8.29600E-1, 8.30920E-1, 8.43850E-1, 5.94946E-1, 5.79742E-2, 5.89616E-2, 
        3.63545E-2, 1.03685E-1, 1.03715E-1, 1.03746E-1, 1.03797E-1, 1.04036E-1, 
        1.06200E-1, 1.26094E-1, 6.94957E-2, 6.87718E-2, 5.40516E-2, 3.73175E-2, 
        3.73406E-2, 3.73644E-2, 3.73950E-2, 3.74953E-2, 3.83063E-2, 4.68172E-2, 
        8.18560E-2, 7.85819E-2, 6.79374E-2, 1.02228E-2, 1.02338E-2, 1.02449E-2, 
        1.02580E-2, 1.02897E-2, 1.05130E-2, 1.31090E-2, 5.45032E-2, 8.50659E-2, 
        8.49093E-2 };
     
        THEN( "S(a,b) and effective temperature outputs are correct" ){
          REQUIRE(ranges::equal(sab,correct,equal));
          REQUIRE( 575.2 == Approx(effectiveTemp).epsilon(1e-6) );
        } // THEN
      } // AND WHEN

    } // WHEN

  } // GIVEN
} // TEST CASE





/*
TEST_CASE( "trans (old tests)" ){

  std::vector<double> alpha {0.10, 0.20, 0.40, 0.50}, 
    beta {0.15, 0.18, 0.22}, correct;

  double transWgt = 0.03, delta = 220.0, diffusion_const = 1.5, temp = 200, 
    sc = 1.0, scaling = 1.0, lambda_s = 0.002, tbeta = 2.1, 
    effectiveTemp = 13.5; ;

  std::vector<double> sab {0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1,1.1,1.2};


  GIVEN( "that the translational motion is diffusive" ){
    WHEN( "temperature is relatively low" ){
      trans( alpha, beta, transWgt, delta, diffusion_const, sc, scaling, 
        lambda_s, tbeta, effectiveTemp, temp,  sab );
      correct = { 0.23049978, 0.25982880, 0.19141505, 0.62197701, 0.58781315, 
        0.39163902, 1.08210491, 0.92354902, 0.64343974, 1.41011128, 1.18123544, 
        0.84745080};
      
      THEN( "S(a,b) and effective temperature outputs are correct" ){
        REQUIRE(ranges::equal(sab,correct,equal));
	REQUIRE( 16.12676056 == Approx(effectiveTemp).epsilon(1e-6) );
      } // THEN
    } // WHEN
  }}

    WHEN( "temperature is relatively high" ){

      alpha = {0.8, 1.0, 1.4, 1.5};
      beta = {0.15, 0.19, 0.24, 0.30, 0.31 };
      temp = 800.0;
      effectiveTemp = 117.2;
      std::vector<double> sab { 0.001, 0.002, 0.003, 0.004, 0.006, 0.01, 0.02, 0.03, 0.04, 0.06, 
            0.1, 0.2, 0.3, 0.4, 0.6, 1.1, 1.2, 1.3, 1.4, 1.6 };
      lambda_s = 2.5236078E-3;
      tbeta = 5.1;

      trans( alpha, beta, transWgt, delta, diffusion_const, sc, scaling, 
        lambda_s, tbeta, effectiveTemp, temp, sab );
      correct = { 0.92601235894, 0.61808459249, 0.4026621598, 0.2607989292, 
        0.2444620547, 1.0791262271, 0.7478653475, 0.5053651418, 0.3344515293, 
        0.3160592329, 1.3359968514, 1.0435211230, 0.7531824364, 0.5472561336, 
        0.5385673429, 2.0990244422, 1.7440234835, 1.4013032062, 1.0787827232, 
        1.0696952350 };
      
      THEN( "S(a,b) and effective temperature outputs are correct" ){
        REQUIRE(ranges::equal(sab,correct,equal));
	REQUIRE( 121.1929824 == Approx(effectiveTemp).epsilon(1e-4) );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "that the translational motion is a free gas" ){
    diffusion_const = 0;

    WHEN( "temperature is relatively low" ){

      trans( alpha, beta, transWgt, delta, diffusion_const, sc, scaling, 
        lambda_s, tbeta, effectiveTemp, temp,  sab );
      correct = { 0.92779395, 0.462578, 0.18376845, 1.771662, 1.2519220,
        0.74812670, 2.146880, 1.78983859, 1.384712, 2.2401082, 1.99146590, 
        1.630380 };
      

      THEN( "S(a,b) and effective temperature outputs are correct" ){
        REQUIRE(ranges::equal(sab,correct,equal));
	REQUIRE( 16.12676056 == Approx(effectiveTemp).epsilon(1e-4) );
      } // THEN
    } // WHEN

    WHEN( "temperature is relatively high" ){

      alpha = {0.8, 1.0, 1.4, 1.5};
      beta = {0.15, 0.19, 0.24, 0.30, 0.31 };
      temp = 800.0;
      effectiveTemp = 117.2;
      std::vector<double> sab { 0.001, 0.002, 0.003, 0.004, 0.006, 0.01, 0.02, 
        0.03, 0.04, 0.06, 0.1, 0.2, 0.3, 0.4, 0.6, 1.1, 1.2, 1.3, 1.4, 1.6 };

      lambda_s = 2.5236078E-3;
      tbeta = 5.1;

      trans( alpha, beta, transWgt, delta, diffusion_const, sc, scaling, 
        lambda_s, tbeta, effectiveTemp, temp, sab );
      correct = { 1.539329, 1.363224, 1.116673, 0.8210472, 0.7761662, 
        1.446650, 1.318804, 1.1343993, 0.8915002, 0.8546271, 1.362848, 
        1.276393, 1.168248, 0.9998096, 0.9865463, 1.9122958, 1.806748, 
        1.693513, 1.505287, 1.4913750 };
      
      THEN( "S(a,b) and effective temperature outputs are correct" ){
        REQUIRE(ranges::equal(sab,correct,equal));
	REQUIRE( 121.192979 == Approx(effectiveTemp).epsilon(1e-4) );
      } // THEN
    } // WHEN
  } // GIVEN
} // TEST CASE
*/

