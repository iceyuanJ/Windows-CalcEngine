#ifndef WINDOWS_CALCENGINE_COLORPROPERTIES_HPP
#define WINDOWS_CALCENGINE_COLORPROPERTIES_HPP

#include <memory>
#include <vector>

#include "WCECommon.hpp"
#include "ScatteringLayer.hpp"

namespace SingleLayerOptics {

	struct Trichromatic {
		Trichromatic( double X, double Y, double Z );

		double X;
		double Y;
		double Z;
	};

	struct RGB {
		RGB( int R, int G, int B );

		int R;
		int G;
		int B;
	};

	struct CIE_LAB {
		CIE_LAB( double L, double A, double B );

		double L;
		double a;
		double b;
	};

	class ColorProperties {

	public:
		/// For BSDF layers make additional constructor
		ColorProperties( const CScatteringLayer & layerX, const CScatteringLayer & layerY,
		                 const CScatteringLayer & layerZ, const FenestrationCommon::CSeries & t_Source,
		                 const FenestrationCommon::CSeries & t_DetectorX,
		                 const FenestrationCommon::CSeries & t_DetectorY,
		                 const FenestrationCommon::CSeries & t_DetectorZ,
		                 const std::shared_ptr< std::vector< double > > & t_wavelengths = nullptr );

		Trichromatic getTrichromatic(
				const FenestrationCommon::PropertySimple t_Property,
				const FenestrationCommon::Side t_Side,
				const FenestrationCommon::Scattering t_Scattering,
				const double t_Theta = 0,
				const double t_Phi = 0
		);

		RGB getRGB(
				const FenestrationCommon::PropertySimple t_Property,
				const FenestrationCommon::Side t_Side,
				const FenestrationCommon::Scattering t_Scattering,
				const double t_Theta = 0,
				const double t_Phi = 0 );

		CIE_LAB getCIE_Lab( const FenestrationCommon::PropertySimple t_Property,
		                    const FenestrationCommon::Side t_Side,
		                    const FenestrationCommon::Scattering t_Scattering, const double t_Theta = 0,
		                    const double t_Phi = 0 );

	private:
		CScatteringLayer m_LayerX;
		CScatteringLayer m_LayerY;
		CScatteringLayer m_LayerZ;
		double m_SDx;
		double m_SDy;
		double m_SDz;

	};

}


#endif //WINDOWS_CALCENGINE_COLORPROPERTIES_HPP
