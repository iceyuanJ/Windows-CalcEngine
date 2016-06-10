#ifndef EQUIVALENTLAYER_H
#define EQUIVALENTLAYER_H

#include <memory>
#include <map>

#include "FenestrationCommon.hpp"

namespace LayerOptics {

  class CLayer;
  class CScatteringSurface;
  enum class Scattering;

}

namespace MultiPane {

  struct SimpleResults {
    SimpleResults() : T( 0 ), R( 0 ) { };
    double T;
    double R;
  };
  
  // Calculates Transmittance and reflectance of multi layer IGU with direct and diffuse properties
  class CEquivalentLayer {
  public:
    CEquivalentLayer( const double Tf_dir_dir, const double Rf_dir_dir, const double Tb_dir_dir, const double Rb_dir_dir, 
      const double Tf_dir_dif, const double Rf_dir_dif, const double Tb_dir_dif, const double Rb_dir_dif, 
      const double Tf_dif_dif, const double Rf_dif_dif, const double Tb_dif_dif, const double Rb_dif_dif );

    CEquivalentLayer( std::shared_ptr< LayerOptics::CLayer > t_Layer );

    void addLayer( const double Tf_dir_dir, const double Rf_dir_dir, const double Tb_dir_dir, const double Rb_dir_dir, 
      const double Tf_dir_dif, const double Rf_dir_dif, const double Tb_dir_dif, const double Rb_dir_dif, 
      const double Tf_dif_dif, const double Rf_dif_dif, const double Tb_dif_dif, const double Rb_dif_dif,
      const FenestrationCommon::Side t_Side = FenestrationCommon::Side::Back );

    void addLayer( std::shared_ptr< LayerOptics::CLayer > t_Layer, const FenestrationCommon::Side t_Side );

    double getPropertySimple( const FenestrationCommon::PropertySimple t_Property, const FenestrationCommon::Side t_Side,
      const LayerOptics::Scattering t_Scattering ) const;

  private:
    void calcEquivalentProperties( std::shared_ptr< LayerOptics::CLayer > t_First, std::shared_ptr< LayerOptics::CLayer > t_Second );

    // Find interreflectance value for given scattering
    double getInterreflectance( 
      std::shared_ptr< const LayerOptics::CScatteringSurface > t_First, 
      std::shared_ptr< const LayerOptics::CScatteringSurface > t_Second, 
      const LayerOptics::Scattering t_Scattering );

    std::shared_ptr< SimpleResults > calcDirectDiffuseTransAndRefl( 
      std::shared_ptr< const LayerOptics::CScatteringSurface > f1, 
      std::shared_ptr< const LayerOptics::CScatteringSurface > b1, 
      std::shared_ptr< const LayerOptics::CScatteringSurface > f2, 
      std::shared_ptr< const LayerOptics::CScatteringSurface > b2 );

    std::shared_ptr< LayerOptics::CLayer > m_Layer;

  };

}

#endif