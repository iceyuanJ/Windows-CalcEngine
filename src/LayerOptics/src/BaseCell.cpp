#include "BaseCell.hpp"
#include "BaseCellDescription.hpp"
#include "FenestrationCommon.hpp"
#include "MaterialDescription.hpp"

using namespace std;
using namespace FenestrationCommon;

namespace LayerOptics {

  CBaseCell::CBaseCell( shared_ptr< CMaterial > t_Material, 
    shared_ptr< CBaseCellDescription > t_CellDescription ) {
    m_Material = t_Material;
    m_CellDescription = t_CellDescription;
  };

  double CBaseCell::T_dir_dir( const Side t_Side, shared_ptr< const CBeamDirection > t_Direction ) {
    return m_CellDescription->T_dir_dir( t_Side, t_Direction );
  };

  double CBaseCell::R_dir_dir( const Side t_Side, shared_ptr< const CBeamDirection > t_Direction ) {
    return m_CellDescription->R_dir_dir( t_Side, t_Direction );
  };

  shared_ptr< vector< double > > CBaseCell::T_dir_dir_band( const Side t_Side, 
    shared_ptr< const CBeamDirection > t_Direction ) {
    double value = T_dir_dir( t_Side, t_Direction );
    shared_ptr< vector< double > > aResults = make_shared< vector< double > >();
    shared_ptr< vector< double > > aMaterials = m_Material->getBandProperties( Property::T, t_Side );
    size_t size = aMaterials->size();
    for( size_t i = 0; i < size; i++ ) {
      aResults->push_back( value );
    }
    return aResults;
  };

  shared_ptr< vector< double > > CBaseCell::R_dir_dir_band( const Side t_Side, 
    shared_ptr< const CBeamDirection > t_Direction ) {
    double value = R_dir_dir( t_Side, t_Direction );
    shared_ptr< vector< double > > aResults = make_shared< vector< double > >();
    shared_ptr< vector< double > > aMaterials = m_Material->getBandProperties( Property::R, t_Side );
    size_t size = aMaterials->size();
    for( size_t i = 0; i < size; i++ ) {
      aResults->push_back( value );
    }
    return aResults;
  };

  int CBaseCell::getBandIndex( const double t_Wavelength ) {
    return m_Material->getBandIndex( t_Wavelength );
  };

  size_t CBaseCell::getBandSize() const {
    return m_Material->getBandSize();
  };

}