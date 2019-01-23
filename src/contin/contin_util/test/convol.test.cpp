#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "contin/contin_util/convol.h"

TEST_CASE( "convol" ){
  GIVEN( "two vectors" ){
    std::vector<double> 
      t1 {0.2, 0.6, 0.8, 2.0, 6.0, 8.0},
      t2 {0.2, 0.6, 0.8, 2.0, 6.0, 8.0,
          0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
          0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
      output(18), correct(18); 
    double delta = 0.03;

    int nn = 18; 
    THEN( "the vectors are correctly convolved and result is returned" ){

      output = convol( t1, t2, delta, nn ),
      correct = {3.8459762, 2.6993367, 1.0195307, 0.53364442, 0.37281623, 
        0.384, 0.624, 1.008, 1.8, 2.16, 0.96, 0, 0, 0, 0, 0, 0, 0};

      REQUIRE( output.size() == correct.size() );
      for ( size_t i = 0; i < output.size(); ++i ){
        REQUIRE( output[i] == Approx( correct[i] ).epsilon(1e-6 ) );  
      }
           
      t1 = {0.01, 0.04, 0.09, 0.11, 0.16, 0.21};
      t2 = {0.01, 0.04, 0.09, 0.11, 0.16, 0.21, 0.0,  0.0,  0.0,  0.0,  0.0,  
            0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0};

      delta = 0.5;
      output = convol( t1, t2, delta, nn );
      correct = {1.1974704E-2, 1.3563056E-2, 1.3531928E-2, 1.379648E-2, 
        1.387114E-2, 1.7875E-2, 2.675E-2, 3.1775E-2, 3.0125E-2, 
        2.52E-2, 1.1025E-2, 0., 0., 0., 0., 0., 0., 0.};

      REQUIRE( output.size() == correct.size() );
      for ( size_t i = 0; i < output.size(); ++i ){
        REQUIRE( output[i] == Approx( correct[i] ).epsilon(1e-6 ) );  
      }
 
      t1 = {0.41483349, 0.49122347, 0.28793794, 0.19807373, 0.16013178, 
        0.35027406, 0.54943040};
      t2 = {0.41483349, 0.49122347, 0.28793794, 0.19807373, 0.16013178, 
        0.35027406, 0.5494304, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 
        0.0, 0.0, 0.0, 0.0, 0.0};
      delta = 0.3481334;

      nn = 21; 
      output = convol( t1, t2, delta, nn );
      correct = {0.24934471, 0.26630576, 0.25941571, 0.24935982, 0.26861886, 
        0.29515324, 0.28458452, 0.23324588, 0.1398470, 9.5883480E-2, 8.8657E-2,
        0.1004980, 5.2546179E-2, 0., 0., 0., 0., 0., 0., 0., 0.};

      REQUIRE( output.size() == correct.size() );
      for ( size_t i = 0; i < output.size(); ++i ){
        REQUIRE( output[i] == Approx( correct[i] ).epsilon(1e-6 ) );  
      }
 
    } // THEN
  } // GIVEN
  GIVEN( "two vectors" ){
    std::vector<double> 
      t1 { 1.6145575501853762, 1.6966062728611888, 0.89067060932967568, 
         0.83055749019345759, 0.85698915228609684, 0.82062267112315690 },
      t2 { 1.6145575501853762, 1.6966062728611888, 0.89067060932967568, 
        0.83055749019345759, 0.85698915228609684, 0.82062267112315690, 0.0, 
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 
        0.0, 0.0, 0.0, 0.0, 0.0 },
      output(18), correct(18); 
    double delta = 9.9970755221739149e-2;
    int nn = 180; 

    THEN( "the vectors are correctly convolved and result is returned" ){

      output = convol( t1, t2, delta, nn ),
      correct = { 1.1527134042223905, 1.1183255882541923, 1.0309064787704803, 
        0.92304692942652411, 0.82661778092122651, 0.63730021135541937, 
        0.43035672657696150, 0.25191773173321347, 0.17562780964360827, 
        0.10545885885937635, 3.3661231385843850e-2, 0.0, 0.0, 0.0, 0.0, 0.0, 
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };

      REQUIRE( output.size() == correct.size() );
      for ( size_t i = 0; i < output.size(); ++i ){
        REQUIRE( output[i] == Approx( correct[i] ).epsilon(1e-6) );  
      }
    } // THEN
  } // GIVEN
  GIVEN( "two vectors" ){
    std::vector<double> 
      t1 { 1.0418438033539950, 1.0947883102147700, 0.57473309331903810, 0.53594322134131989, 0.55299907875587984, 0.52953246832440359, 0.57723202177222455, 0.59124757089132085, 0.61482233802934072, 0.64365863700344150 },
      t2 { 0.46605790270614433, 0.48369462583326667, 0.49053805926769661, 0.49284479926352820, 0.49318727629580128, 0.49151079679922405, 0.48633038484117996, 0.47412346689783713, 0.45129413672489449, 0.41694489255239259, 0.37542661919527825, 0.33571622720856448, 0.30002930126056598, 0.26779332215105167, 0.23538708400120983, 0.20191251353636147, 0.16743052453832799, 0.13237116089256559, 0.10063991111922464, 7.5587684090634877e-2, 5.7733849286578605e-2, 4.4514893439515729e-2, 3.3007290358418942e-2, 2.3071030937270805e-2, 1.4663913522565131e-2, 7.9234037229468837e-3, 3.1821218053670755e-3, 6.6627383467767159e-4, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
    double delta = 9.9970755221739149e-2;
    int nn = 37;

    THEN( "the vectors are correctly convolved and result is returned" ){
      std::vector<double> output = convol( t1, t2, delta, nn );
      std::vector<double> correct { 0.39224501722727217, 0.40960178676949988, 0.42255003425485449, 0.43153187761238176, 0.43704885123708986, 0.43907120749421147, 0.43705456121640257, 0.43022150595476960, 0.41789284686880929, 0.40020969471288048, 0.37843625636309181, 0.35424301610040770, 0.32888659314600360, 0.30260234307757328, 0.27528493514977970, 0.24687900823124878, 0.21771543415858433, 0.18866864342894657, 0.16097088689495295, 0.13579859746325229, 0.11355526276868566, 9.3902446405644380E-002, 7.6356722300506261E-002, 6.0667545635435104E-002, 4.6906821488091027E-002, 3.5221354410008378E-002, 2.5768550452603574E-002, 1.8546549710897874E-002, 1.3228666701889807E-002, 9.2989831200484367E-003, 6.3019048429087694E-003, 4.0092701722733255E-003, 2.3308146786282270E-003, 1.1853311789167681E-003, 4.8989228767026783E-004, 1.4333208346935429E-004, 2.1436374560879447E-005, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
      REQUIRE( output.size() == correct.size() );
      for ( size_t i = 0; i < output.size(); ++i ){
        REQUIRE( output[i] == Approx( correct[i] ).epsilon(1e-6) );  
      }
    } // THEN
  } // GIVEN
  GIVEN( "super simple case" ){
    std::vector<double> 
      t1 {0.1, 0.6, 0.4},
      t2 {0.1, 0.6, 0.4, 
          0.0, 0.0  };
    double delta = 1.00;

    int nn = 5; 
    THEN( "the vectors are correctly convolved and result is returned" ){

      auto output = convol( t1, t2, delta, nn );
      std::cout << (output|ranges::view::all) << std::endl;

 
    } // THEN
  } // GIVEN

} // TEST CASE


