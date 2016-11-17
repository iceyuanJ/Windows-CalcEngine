#ifndef THERMOCHROMICSURFACE_H
#define THERMOCHROMICSURFACE_H

#include <memory>
#include <vector>

#include "Surface.hpp"

namespace FenestrationCommon {

  class IInterpolation2D;

}

namespace Chromogenics {

  class CThermochromicSurface : public Tarcog::ISurface {
  public:
    CThermochromicSurface( std::vector< std::pair< double, double > > const& t_Emissivity, 
      std::vector< std::pair< double, double > > const& t_Transmittance );
    CThermochromicSurface( double const& t_Emissivity,
      std::vector< std::pair< double, double > > const& t_Transmittance );
    CThermochromicSurface( std::vector< std::pair< double, double > > const& t_Emissivity,
      double const& t_Transmittance );
    
    CThermochromicSurface( CThermochromicSurface const& t_Surface );

    virtual std::shared_ptr< Tarcog::ISurface > clone() const;

    void setTemperature( double const t_Temperature );

  private:
    std::shared_ptr< FenestrationCommon::IInterpolation2D > m_EmissivityInterpolator;
    std::shared_ptr< FenestrationCommon::IInterpolation2D > m_TransmittanceInterpolator;
  };

}

#endif