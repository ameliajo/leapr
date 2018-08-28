#define CATCH_CONFIG_MAIN
#include "catch.hpp" 
#include "cdf/cdf.h"
#include <range/v3/all.hpp>


TEST_CASE("super simple cdf" ){
  GIVEN( "you call the functions separately" ){
    int a_size = 3, b_size = 4;
    Eigen::Tensor<double,3> ssm(a_size,b_size,1); 
    Eigen::Tensor<double,2> eq15(a_size,b_size), eq17(a_size,b_size), 
                            eq15Real(a_size,b_size), eq17Real(a_size,b_size);

    ssm(0,0,0) = 1; ssm(0,1,0) = 2;  ssm(0,2,0) = 3;  ssm(0,3,0) = 4; 
    ssm(1,0,0) = 5; ssm(1,1,0) = 6;  ssm(1,2,0) = 7;  ssm(1,3,0) = 8; 
    ssm(2,0,0) = 9; ssm(2,1,0) = 10; ssm(2,2,0) = 11; ssm(2,3,0) = 12;

    std::vector<double> 
      correctEq_14 { 0.1923076923, 0.2307692308, 0.2692307692, 0.3076923077 },
      correctEq_16 { 0.1923076923, 0.4230769231, 0.6923076923, 1.0000000000 };

    eq15Real(0,0) = 0.066666; eq15Real(1,0) = 0.333333; eq15Real(2,0) = 0.600000; 
    eq15Real(0,1) = 0.111111; eq15Real(1,1) = 0.333333; eq15Real(2,1) = 0.555555; 
    eq15Real(0,2) = 0.142857; eq15Real(1,2) = 0.333333; eq15Real(2,2) = 0.523809; 
    eq15Real(0,3) = 0.166666; eq15Real(1,3) = 0.333333; eq15Real(2,3) = 0.500000;

    eq17Real(0,0) = 0.066666; eq17Real(1,0) = 0.4;      eq17Real(2,0) = 1.0; 
    eq17Real(0,1) = 0.111111; eq17Real(1,1) = 0.444444; eq17Real(2,1) = 1.0; 
    eq17Real(0,2) = 0.142857; eq17Real(1,2) = 0.476190; eq17Real(2,2) = 1.0; 
    eq17Real(0,3) = 0.166666; eq17Real(1,3) = 0.5;      eq17Real(2,3) = 1.0;

    THEN( "Eq. 14-17 are correct" ){ 

      for ( int b = 0; b < b_size; ++b ){
        REQUIRE( correctEq_14[b] == Approx(calc_eq_14(b,ssm)).epsilon(1e-6) );
        REQUIRE( correctEq_16[b] == Approx(calc_eq_16(b,ssm)).epsilon(1e-6) );
      }

      for ( int b = 0; b < b_size; ++b ){
        for ( int a = 0; a < a_size; ++a ){
          eq15(a,b) = calc_eq_15(a,b,ssm);
          eq17(a,b) = calc_eq_17(a,b,ssm);
        }
      }
  
      for ( int b = 0; b < b_size; ++b ){
        for ( int a = 0; a < a_size; ++a ){
          REQUIRE( eq15(a,b) == Approx(eq15Real(a,b)).epsilon(1e-6) );
          REQUIRE( eq17(a,b) == Approx(eq17Real(a,b)).epsilon(1e-6) );
        } 
      }
    } // THEN
  } // GIVEN
  GIVEN( "you call the function as one big whole" ){
    int a_size = 3, b_size = 4;
    Eigen::Tensor<double,3> ssm(a_size,b_size,1); 
    Eigen::Tensor<double,2> 
                            eq15Real(a_size,b_size), eq17Real(a_size,b_size);



    ssm(0,0,0) = 1; ssm(0,1,0) = 2;  ssm(0,2,0) = 3;  ssm(0,3,0) = 4; 
    ssm(1,0,0) = 5; ssm(1,1,0) = 6;  ssm(1,2,0) = 7;  ssm(1,3,0) = 8; 
    ssm(2,0,0) = 9; ssm(2,1,0) = 10; ssm(2,2,0) = 11; ssm(2,3,0) = 12;

    auto out = cdf_no_leapr(ssm);
    auto eq14 = std::get<0>(out);
    auto eq15 = std::get<1>(out);
    auto eq16 = std::get<2>(out);
    auto eq17 = std::get<3>(out);

    std::vector<double> 
      correctEq_14 { 0.1923076923, 0.2307692308, 0.2692307692, 0.3076923077 },
      correctEq_16 { 0.1923076923, 0.4230769231, 0.6923076923, 1.0000000000 };

    eq15Real(0,0) = 0.066666; eq15Real(1,0) = 0.333333; eq15Real(2,0) = 0.600000; 
    eq15Real(0,1) = 0.111111; eq15Real(1,1) = 0.333333; eq15Real(2,1) = 0.555555; 
    eq15Real(0,2) = 0.142857; eq15Real(1,2) = 0.333333; eq15Real(2,2) = 0.523809; 
    eq15Real(0,3) = 0.166666; eq15Real(1,3) = 0.333333; eq15Real(2,3) = 0.500000;

    eq17Real(0,0) = 0.066666; eq17Real(1,0) = 0.4;      eq17Real(2,0) = 1.0; 
    eq17Real(0,1) = 0.111111; eq17Real(1,1) = 0.444444; eq17Real(2,1) = 1.0; 
    eq17Real(0,2) = 0.142857; eq17Real(1,2) = 0.476190; eq17Real(2,2) = 1.0; 
    eq17Real(0,3) = 0.166666; eq17Real(1,3) = 0.5;      eq17Real(2,3) = 1.0;

    THEN( "Eq. 14-17 are correct" ){ 

      for ( int b = 0; b < b_size; ++b ){
        REQUIRE( correctEq_14[b] == Approx(eq14[b]).epsilon(1e-6) );
        REQUIRE( correctEq_16[b] == Approx(eq16[b]).epsilon(1e-6) );
        for ( int a = 0; a < a_size; ++a ){
          REQUIRE( eq15(a,b,0) == Approx(eq15Real(a,b)).epsilon(1e-6) );
          REQUIRE( eq17(a,b,0) == Approx(eq17Real(a,b)).epsilon(1e-6) );
        } 
      }
    } // THEN
  } // GIVEN

} // TEST CASE


TEST_CASE( "cdf" ){
  GIVEN( "" ){
    WHEN( "" ){
      int ntempr, nphon, 
          lat;
      double delta, twt, c, tbeta;
      std::vector<double> alpha, beta, temp, rho;
      std::string title;
      title  = "H IN H2O, ENDF MODEL"; 
      ntempr = 1;     nphon = 100;    
      lat   = 1;  
      alpha = { 0.01008, 0.015, 0.0252, 0.033, 0.050406, 0.0756, 0.100812, 0.151218,
        0.201624, 0.25203, 0.302436, 0.352842, 0.403248, 0.453654, 0.50406, 
        0.554466, 0.609711, 0.670259, 0.736623, 0.809349, 0.889061, 0.976435, 
        1.07213, 1.17708, 1.29211, 1.41822, 1.55633, 1.70775, 1.87379, 2.05566, 
        2.25506, 2.47352, 2.71295, 2.97546, 3.26308, 3.57832, 3.92390, 4.30266, 
        4.71770, 5.17256, 5.67118, 6.21758, 6.81650, 7.47289, 8.19228, 8.98073, 
        9.84489, 10.7919, 11.8303, 12.9674, 14.2145, 15.5815, 17.0796, 18.7208, 
        20.5203, 22.4922, 24.6526, 27.0216, 29.6175, 32.4625, 35.5816, 38.9991, 
        42.7453, 46.8503, 50.0 }; 
    
      beta = { 0.000000, 0.006375, 0.012750, 0.025500, 0.038250, 0.0510, 0.06575, 
        0.0806495, 0.120974, 0.161299, 0.241949, 0.322598, 0.403248, 0.483897, 
        0.564547, 0.645197, 0.725846, 0.806496, 0.887145, 0.967795, 1.048440, 
        1.129090, 1.209740, 1.290390, 1.371040, 1.451690, 1.532340, 1.612990, 
        1.693640, 1.774290, 1.854940, 1.935590, 2.016240, 2.096890, 2.177540, 
        2.258190, 2.338840, 2.419490, 2.500140, 2.580790, 2.669500, 2.767090, 
        2.874450, 2.992500, 3.122350, 3.265300, 3.422470, 3.595360, 3.785490, 
        3.994670, 4.224730, 4.477870, 4.756310, 5.062580, 5.399390, 5.769970, 
        6.177660, 6.626070, 7.119240, 7.661810, 8.258620, 8.915110, 9.637220, 
        10.43200, 11.30510, 12.26680, 13.32430, 14.48670, 15.76600, 17.17330, 
        18.72180, 20.42450, 22.29760, 24.35720, 25.0 };
    
      beta = {-40.0, -39.39, -38.78, -38.18, -37.57, -36.96, -36.36, -35.75, 
        -35.15, -34.54, -33.93, -33.33, -32.72, -32.12, -31.51, -30.90, -30.30, 
        -29.69, -29.09, -28.48, -27.87, -27.27, -26.66, -26.06, -25.45, -24.84, 
        -24.24, -23.63, -23.03, -22.42, -21.81, -21.21, -20.60, -20.0, -19.39, 
        -18.78, -18.18, -17.57, -16.96, -16.36, -15.75, -15.15, -14.54, -13.93, 
        -13.33, -12.72, -12.12, -11.51, -10.90, -10.30, -9.69, -9.00, -8.48, 
        -7.87, -7.27, -6.66, -6.06, -5.45, -4.84, -4.24, -3.63, -3.03, -2.42, 
        -1.81, -1.21, -0.60, 0.0, 0.60, 1.21, 1.81, 2.42, 3.03, 3.63, 4.24, 4.84, 
        5.45, 6.06, 6.66, 7.27, 7.87, 8.48, 9.09, 9.69, 10.30, 10.90, 11.51, 
        12.12, 12.72, 13.33, 13.93, 14.54, 15.15, 15.75, 16.36, 16.96, 17.57, 
        18.18, 18.78, 19.39, 20.0};


      temp   = { 296.0 };        
      delta  = 0.00255;         
      rho = { 0.0000, 0.0005, 0.001, 0.002, 0.0035, 0.005, 0.0075, 0.01, 0.013, 
        0.0165, 0.02, 0.0245, 0.029, 0.034, 0.0395, 0.045, 0.0506, 0.0562,
        0.0622, 0.0686, 0.075, 0.083, 0.091, 0.099, 0.107, 0.115, 0.1197, 
        0.1214, 0.1218, 0.1195, 0.1125, 0.1065, 0.1005, 0.09542, 0.09126, 
        0.0871, 0.0839, 0.0807, 0.07798, 0.07574, 0.0735, 0.07162, 0.06974, 
        0.06804, 0.06652, 0.065, 0.0634, 0.0618, 0.06022, 0.05866, 0.0571, 
        0.05586, 0.05462, 0.0535, 0.0525, 0.0515, 0.05042, 0.04934, 0.04822, 
        0.04706, 0.0459, 0.04478, 0.04366, 0.04288, 0.04244, 0.042, 0.006, 
        0.006, 0.00639, 0.00678, 0.00756, 0.00873, 0.01029, 0.012255, 0.01695, 
        0.021645, 0.03573, 0.057255, 0.0909, 0.12495, 0.127695, 0.120645, 
        0.09795, 0.040035, 0.022425, 0.011085, 0.00756, 0.005205, 0.003645, 
        0.002865, 0.002085, 0.001695, 0.001695, 0.00129, 0.00129, 0.00129,
        0.00129, 0.00129, 0.00129, 0.00129, 0.00129, 0.001, 0.001, 0.001, 
        0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 
        0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 
        0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 
        0.00208695, 0.00208695, 0.00208695, 0.00208695, 0.00247815, 
        0.00208695, 0.00247815, 0.00247815, 0.0028695, 0.0032595, 0.0032595, 
        0.003651, 0.00443475, 0.00482595, 0.0056085, 0.00639, 0.009129, 
        0.0122595, 0.01539, 0.020478, 0.0263475, 0.03495, 0.049035, 0.05955, 
        0.074085, 0.08856, 0.09678, 0.104205, 0.111255, 0.119085, 0.121425, 
        0.11751, 0.11439, 0.09678, 0.0819, 0.06978, 0.061956, 0.052173, 
        0.045129, 0.038085, 0.0275205, 0.023985, 0.014217, 0.0083475, 
        0.0056085, 0.003651, 0.00247815, 0.00208695, 0.00208695, 0.00208695 };
      twt = 0.055556; c = 0.0; tbeta = 0.444444; 

      auto out = cdf(ntempr, nphon, lat, delta, twt, c, tbeta, alpha, beta, temp, rho );
      //std::cout << (out|ranges::view::all) << std::endl;
      std::vector<double> correctEq14 {0, 0, 0, 0, 0, 0, 2.55339e-28, 
        1.32196e-27, 1.44421e-26, 1.26322e-25, 9.60693e-25, 5.50626e-24, 
        2.72044e-23, 1.73094e-22, 1.04817e-21, 5.81133e-21, 2.96786e-20, 
        1.42772e-19, 4.41771e-19, 1.93574e-18, 7.9925e-18, 3.06323e-17, 
        1.10219e-16, 3.51148e-16, 1.12642e-15, 3.54553e-15, 9.70872e-15, 
        2.81366e-14, 7.33816e-14, 1.94435e-13, 4.85016e-13, 1.17518e-12, 
        2.75392e-12, 6.18715e-12, 1.29487e-11, 2.64319e-11, 5.30731e-11, 
        1.0978e-10, 2.2404e-10, 4.13043e-10, 6.90107e-10, 1.15385e-09, 
        2.09194e-09, 3.96493e-09, 7.57605e-09, 1.47891e-08, 2.87171e-08, 
        5.65094e-08, 1.11149e-07, 2.16323e-07, 4.29424e-07, 9.56754e-07, 
        1.78142e-06, 3.55199e-06, 6.43638e-06, 1.2572e-05, 2.58236e-05, 
        5.28249e-05, 0.000107009, 0.000216301, 0.000447591, 0.000897825, 
        0.00166255, 0.00275689, 0.00434298, 0.00700253, 0.632297, 0.0747294, 
        0.029146, 0.0213107, 0.019996, 0.0187571, 0.0166387, 0.0146049, 
        0.0130531, 0.0117798, 0.0105375, 0.00929878, 0.00871664, 0.00872165, 
        0.0080102, 0.00708272, 0.00641173, 0.00591499, 0.00551081, 0.00513091, 
        0.00477507, 0.00445901, 0.00418315, 0.00396967, 0.00383558, 0.00387435, 
        0.00420167, 0.00460538, 0.00452953, 0.00406457, 0.00359859, 0.0032497, 
        0.00291545, 0.00255115},
      correctEq16 {0, 0, 0, 0, 0, 0, 2.55339e-28, 1.5773e-27, 1.60194e-26, 
        1.42342e-25, 1.10303e-24, 6.60929e-24, 3.38137e-23, 2.06908e-22, 
        1.25508e-21, 7.06641e-21, 3.6745e-20, 1.79517e-19, 6.21289e-19, 
        2.55703e-18, 1.05495e-17, 4.11819e-17, 1.51401e-16, 5.02548e-16, 
        1.62897e-15, 5.17449e-15, 1.48832e-14, 4.30198e-14, 1.16401e-13, 
        3.10836e-13, 7.95852e-13, 1.97104e-12, 4.72496e-12, 1.09121e-11, 
        2.38608e-11, 5.02927e-11, 1.03366e-10, 2.13145e-10, 4.37185e-10, 
        8.50228e-10, 1.54033e-09, 2.69419e-09, 4.78613e-09, 8.75106e-09, 
        1.63271e-08, 3.11162e-08, 5.98334e-08, 1.16343e-07, 2.27492e-07, 
        4.43815e-07, 8.73239e-07, 1.82999e-06, 3.61142e-06, 7.16341e-06, 
        1.35998e-05, 2.61717e-05, 5.19953e-05, 1.0482e-4, 2.11829e-4, 
        4.2813e-4, 8.75721e-4, 0.00177355, 0.0034361, 0.00619299, 0.010536, 
        0.0175385, 0.649836, 0.724565, 0.753711, 0.775022, 0.795018, 0.813775, 
        0.830413, 0.845018, 0.858071, 0.869851, 0.880389, 0.889688, 0.898404, 
        0.907126, 0.915136, 0.922219, 0.92863, 0.934545, 0.940056, 0.945187, 
        0.949962, 0.954421, 0.958604, 0.962574, 0.96641, 0.970284, 0.974486, 
        0.979091, 0.983621, 0.987685, 0.991284, 0.994533, 0.997449, 1},
      correctEq15_diag { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3.16819e-09, 1.34959e-06, 6.88045e-05, 
        6.84092e-4, 0.00208706, 0.00343118, 0.00472821, 0.00733659, 0.0111333, 
        0.0133464, 0.0127017, 0.0105297, 0.00840076, 0.00767875, 0.00869503, 
        0.0110606, 0.0145791, 0.0190046, 0.0241772, 0.0300154, 0.036258, 
        0.0418962, 0.0451932, 0.0460467, 0.0465056, 0.0489754, 0.0459333, 
        0.0381916, 0.0300796, 0.0222248, 0.0150976, 0.00934232, 0.00547785, 
        0.00325159, 0.0020051, 0.00136336 },
      correctEq17_diag { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3.86167e-09, 2.53e-06, 0.00016968, 
        0.00272544, 0.012404, 0.0220965, 0.030445, 0.053606, 0.112612, 0.186073, 
        0.20931, 0.151338, 0.083666, 0.0565243, 0.055841, 0.0669216, 0.0884777, 
        0.12005, 0.161382, 0.211117, 0.270526, 0.346111, 0.448182, 0.544764, 
        0.628614, 0.682491, 0.757165, 0.8341, 0.89196, 0.933652, 0.962466, 
        0.980829, 0.99096, 0.995979, 0.998481, 1 };

      auto eq14 = std::get<0>(out); auto eq15 = std::get<1>(out); 
      auto eq16 = std::get<2>(out); auto eq17 = std::get<3>(out); 

      THEN( "Eq. 14 and Eq. 16 are calculated correctly" ){ 
        for ( size_t i = 0; i < eq14.size(); ++i ){
          REQUIRE( correctEq14[i] == Approx(eq14[i]).epsilon(1e-6) );
          REQUIRE( correctEq16[i] == Approx(eq16[i]).epsilon(1e-6) );
        }
      } // THEN 
      THEN( "Snippets of Eq. 15 appear to be correct" ){ 
        for ( size_t i = 0; i < alpha.size(); ++i ){
          REQUIRE( correctEq15_diag[i] == Approx(eq15(i,i,0)).epsilon(1e-6) );
          REQUIRE( correctEq17_diag[i] == Approx(eq17(i,i,0)).epsilon(1e-6) );
        }
      } // THEN 
    } // WHEN
  } // GIVEN
} // TEST CASE





/*
  int nout, ntempr, iprint, nphon, mat, npr, iel, ncold, nss, nalpha, nbeta, 
      lat, ni, nd, nka;
  double sps, b7, za, awr, spr, aws, delta, twt, c, tbeta, dka;
  std::vector<double> alpha, beta, temp, rho, oscE, oscW, 
    kappa;
  std::string title;
    nout   = 20;                                                      // Card 1
    title  = "H IN H2O, ENDF MODEL";                                  // Card 2
    ntempr = 1;       iprint = 1;     nphon = 100;                    // Card 3
    mat    = 1;       za     = 1001.0;                                // Card 4
    awr    = 0.99917; spr    = 20.478;  npr   = 2;  iel = 0;   ncold = 0;
    nss    = 1;       b7     = 1.0;   aws = 15.85316;   sps = 3.8883; // Card 6
    nalpha = 65;      nbeta  = 75;    lat   = 1;                      // Card 7
    alpha = { 0.01008, 0.015, 0.0252, 0.033, 0.050406, 0.0756, 0.100812, 0.151218,
      0.201624, 0.25203, 0.302436, 0.352842, 0.403248, 0.453654, 0.50406, 
      0.554466, 0.609711, 0.670259, 0.736623, 0.809349, 0.889061, 0.976435, 
      1.07213, 1.17708, 1.29211, 1.41822, 1.55633, 1.70775, 1.87379, 2.05566, 
      2.25506, 2.47352, 2.71295, 2.97546, 3.26308, 3.57832, 3.92390, 4.30266, 
      4.71770, 5.17256, 5.67118, 6.21758, 6.81650, 7.47289, 8.19228, 8.98073, 
      9.84489, 10.7919, 11.8303, 12.9674, 14.2145, 15.5815, 17.0796, 18.7208, 
      20.5203, 22.4922, 24.6526, 27.0216, 29.6175, 32.4625, 35.5816, 38.9991, 
      42.7453, 46.8503, 50.0 };  // Card 8

    beta = { 0.000000, 0.006375, 0.012750, 0.025500, 0.038250, 0.0510, 0.06575, 
      0.0806495, 0.120974, 0.161299, 0.241949, 0.322598, 0.403248, 0.483897, 
      0.564547, 0.645197, 0.725846, 0.806496, 0.887145, 0.967795, 1.048440, 
      1.129090, 1.209740, 1.290390, 1.371040, 1.451690, 1.532340, 1.612990, 
      1.693640, 1.774290, 1.854940, 1.935590, 2.016240, 2.096890, 2.177540, 
      2.258190, 2.338840, 2.419490, 2.500140, 2.580790, 2.669500, 2.767090, 
      2.874450, 2.992500, 3.122350, 3.265300, 3.422470, 3.595360, 3.785490, 
      3.994670, 4.224730, 4.477870, 4.756310, 5.062580, 5.399390, 5.769970, 
      6.177660, 6.626070, 7.119240, 7.661810, 8.258620, 8.915110, 9.637220, 
      10.43200, 11.30510, 12.26680, 13.32430, 14.48670, 15.76600, 17.17330, 
      18.72180, 20.42450, 22.29760, 24.35720, 25.0 };

    beta = {-40.0, -39.39, -38.78, -38.18, -37.57, -36.96, -36.36, -35.75, 
      -35.15, -34.54, -33.93, -33.33, -32.72, -32.12, -31.51, -30.90, -30.30, 
      -29.69, -29.09, -28.48, -27.87, -27.27, -26.66, -26.06, -25.45, -24.84, 
      -24.24, -23.63, -23.03, -22.42, -21.81, -21.21, -20.60, -20.0, -19.39, 
      -18.78, -18.18, -17.57, -16.96, -16.36, -15.75, -15.15, -14.54, -13.93, 
      -13.33, -12.72, -12.12, -11.51, -10.90, -10.30, -9.69, -9.00, -8.48, 
      -7.87, -7.27, -6.66, -6.06, -5.45, -4.84, -4.24, -3.63, -3.03, -2.42, 
      -1.81, -1.21, -0.60, 0.0, 0.60, 1.21, 1.81, 2.42, 3.03, 3.63, 4.24, 4.84, 
      5.45, 6.06, 6.66, 7.27, 7.87, 8.48, 9.09, 9.69, 10.30, 10.90, 11.51, 
      12.12, 12.72, 13.33, 13.93, 14.54, 15.15, 15.75, 16.36, 16.96, 17.57, 
      18.18, 18.78, 19.39, 20.0};

    nbeta = beta.size();

    temp   = { 296.0 };                                             // Card 10 
    delta  = 0.00255;    ni = 184;                                   // Card 11
    rho = { 0.0000, 0.0005, 0.001, 0.002, 0.0035, 0.005, 0.0075, 0.01, 0.013, 
      0.0165, 0.02, 0.0245, 0.029, 0.034, 0.0395, 0.045, 0.0506, 0.0562,
      0.0622, 0.0686, 0.075, 0.083, 0.091, 0.099, 0.107, 0.115, 0.1197, 
      0.1214, 0.1218, 0.1195, 0.1125, 0.1065, 0.1005, 0.09542, 0.09126, 
      0.0871, 0.0839, 0.0807, 0.07798, 0.07574, 0.0735, 0.07162, 0.06974, 
      0.06804, 0.06652, 0.065, 0.0634, 0.0618, 0.06022, 0.05866, 0.0571, 
      0.05586, 0.05462, 0.0535, 0.0525, 0.0515, 0.05042, 0.04934, 0.04822, 
      0.04706, 0.0459, 0.04478, 0.04366, 0.04288, 0.04244, 0.042, 0.006, 
      0.006, 0.00639, 0.00678, 0.00756, 0.00873, 0.01029, 0.012255, 0.01695, 
      0.021645, 0.03573, 0.057255, 0.0909, 0.12495, 0.127695, 0.120645, 
      0.09795, 0.040035, 0.022425, 0.011085, 0.00756, 0.005205, 0.003645, 
      0.002865, 0.002085, 0.001695, 0.001695, 0.00129, 0.00129, 0.00129,
      0.00129, 0.00129, 0.00129, 0.00129, 0.00129, 0.001, 0.001, 0.001, 
      0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 
      0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 
      0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 
      0.00208695, 0.00208695, 0.00208695, 0.00208695, 0.00247815, 
      0.00208695, 0.00247815, 0.00247815, 0.0028695, 0.0032595, 0.0032595, 
      0.003651, 0.00443475, 0.00482595, 0.0056085, 0.00639, 0.009129, 
      0.0122595, 0.01539, 0.020478, 0.0263475, 0.03495, 0.049035, 0.05955, 
      0.074085, 0.08856, 0.09678, 0.104205, 0.111255, 0.119085, 0.121425, 
      0.11751, 0.11439, 0.09678, 0.0819, 0.06978, 0.061956, 0.052173, 
      0.045129, 0.038085, 0.0275205, 0.023985, 0.014217, 0.0083475, 
      0.0056085, 0.003651, 0.00247815, 0.00208695, 0.00208695, 0.00208695 };
    twt = 0.055556; c = 0.0; tbeta = 0.444444;  // Card 13
    nd = 0;                                     // Card 14
    oscE = { };                                 // Card 15
    oscW = { };                                 // Card 16
    nka = 0; dka = 0.0;                         // Card 17
    kappa    = { };                             // Card 18
*/

