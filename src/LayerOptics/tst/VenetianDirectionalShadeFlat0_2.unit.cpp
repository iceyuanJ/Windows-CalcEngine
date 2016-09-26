#include <memory>
#include <gtest/gtest.h>

#include "VenetianCellDescription.hpp"
#include "MaterialDescription.hpp"
#include "FenestrationCommon.hpp"
#include "BSDFDirections.hpp"
#include "BSDFResults.hpp"
#include "SquareMatrix.hpp"
#include "BSDFLayer.hpp"
#include "BSDFLayerMaker.hpp"

using namespace std;
using namespace LayerOptics;
using namespace FenestrationCommon;

class TestVenetianDirectionalShadeFlat0_2 : public testing::Test {

private:
  shared_ptr< CBSDFLayer > m_Shade;

protected:
  virtual void SetUp() {
    // create material
    double Tmat = 0.1;
    double Rfmat = 0.7;
    double Rbmat = 0.7;
    double minLambda = 0.3;
    double maxLambda = 2.5;
    shared_ptr< CMaterialBand > aMaterial = 
      make_shared< CMaterialSingleBand >( Tmat, Tmat, Rfmat, Rbmat, minLambda, maxLambda );
    
    // make cell geometry
    double slatWidth = 0.010; // m
    double slatSpacing = 0.010; // m
    double slatTiltAngle = 45;
    double curvatureRadius = 0;
    size_t numOfSlatSegments = 1;

    shared_ptr< CCellDescription > aCellDescription = 
      make_shared< CVenetianCellDescription >( slatWidth, slatSpacing, slatTiltAngle, 
      curvatureRadius, numOfSlatSegments );

    // Method
    DistributionMethod aDistribution = DistributionMethod::DirectionalDiffuse;

    // create BSDF
    shared_ptr< CBSDFHemisphere > aBSDF = make_shared< CBSDFHemisphere >( BSDFBasis::Full );

    // make layer
    CBSDFLayerMaker aMaker = CBSDFLayerMaker( aMaterial, aBSDF, aCellDescription, aDistribution );
    m_Shade = aMaker.getLayer();

  }

public:
  shared_ptr< CBSDFLayer > GetShade() { return m_Shade; };

};

TEST_F( TestVenetianDirectionalShadeFlat0_2, TestVenetian1 ) {
  SCOPED_TRACE( "Begin Test: Venetian cell (Flat, 45 degrees slats) - solar properties." );
  
  shared_ptr< CBSDFLayer > aShade = GetShade();

  shared_ptr< CBSDFResults > aResults = aShade->getResults();

  double tauDiff = aResults->TauDiffDiff( Side::Front );
  EXPECT_NEAR( 0.45408806110142574, tauDiff, 1e-6 );

  double RfDiff = aResults->RhoDiffDiff( Side::Front );
  EXPECT_NEAR( 0.27657763790935469, RfDiff, 1e-6 );

}