#ifndef BSDFLAYER_H
#define BSDFLAYER_H

#include <memory>
#include <vector>
#include <map>

namespace FenestrationCommon {

  class CSquareMatrix;
  enum class Side;

}

namespace LayerOptics {

  class CBSDFDirections;

  // Layer results from BSDF directions.
  class CBSDFResults {
  public:
    explicit CBSDFResults( const std::shared_ptr< const CBSDFDirections >& t_Directions );

    // Transmittance matrices for front and back sides
    std::shared_ptr< FenestrationCommon::CSquareMatrix > Tau( const FenestrationCommon::Side t_Side ) const;
    // Reflectance matrices for front and back sides
    std::shared_ptr< FenestrationCommon::CSquareMatrix > Rho( const FenestrationCommon::Side t_Side ) const;

    void setResultMatrices( const std::shared_ptr< FenestrationCommon::CSquareMatrix >& t_Tau,
      const std::shared_ptr< FenestrationCommon::CSquareMatrix >& t_Rho, FenestrationCommon::Side t_Side );

    // Direct-direct components
    double TauDirDir( const FenestrationCommon::Side t_Side, const double t_Theta, const double t_Phi );
    double RhoDirDir( const FenestrationCommon::Side t_Side, const double t_Theta, const double t_Phi );

    // Directional hemispherical results for every direction in BSDF definition
    std::shared_ptr< std::vector< double > > TauDirHem( const FenestrationCommon::Side t_Side );
    std::shared_ptr< std::vector< double > > RhoDirHem( const FenestrationCommon::Side t_Side );
    std::shared_ptr< std::vector< double > > Abs( const FenestrationCommon::Side t_Side );

    // Directional hemispherical results for given Theta and Phi direction
    double TauDirHem( const FenestrationCommon::Side t_Side, const double t_Theta, const double t_Phi );
    double RhoDirHem( const FenestrationCommon::Side t_Side, const double t_Theta, const double t_Phi );
    double Abs( const FenestrationCommon::Side t_Side, const double t_Theta, const double t_Phi );

    std::shared_ptr< const CBSDFDirections > getDirections() const;

    // Diffuse transmittance for front and back sides
    double TauDiffDiff( const FenestrationCommon::Side t_Side ) const;

    // Diffuse reflectance for front and back sides
    double RhoDiffDiff( const FenestrationCommon::Side t_Side ) const;

    // Lambda values for the layer.
    std::shared_ptr< const std::vector< double > > lambdaVector() const;
    std::shared_ptr< const FenestrationCommon::CSquareMatrix > lambdaMatrix() const;

  protected:
    std::shared_ptr< const CBSDFDirections > m_Directions;
    size_t m_DimMatrices;

  private:
    // Hemispherical integration over m_Directions
    double integrate( FenestrationCommon::CSquareMatrix& t_Matrix ) const;

    std::map< FenestrationCommon::Side, std::shared_ptr< FenestrationCommon::CSquareMatrix > > m_Tau;
    std::map< FenestrationCommon::Side, std::shared_ptr< FenestrationCommon::CSquareMatrix > > m_Rho;

    std::map< FenestrationCommon::Side, std::shared_ptr< std::vector< double > > > m_VTauHem;
    std::map< FenestrationCommon::Side, std::shared_ptr< std::vector< double > > > m_VRhoHem;

    std::map< FenestrationCommon::Side, std::shared_ptr< std::vector< double > > > m_Abs;

    void calcHemispherical();
    bool m_HemisphericalCalculated;
  };

}

#endif