#ifndef MULTILAYER_H
#define MULTILAYER_H

#include <memory>
#include <vector>

#include "WCECommon.hpp"
#include "WCESingleLayerOptics.hpp"

namespace SingleLayerOptics {

	class CLayerSingleComponent;
	class CScatteringLayer;

}

namespace MultiLayerOptics {

	class CInterRef;
	class CEquivalentScatteringLayer;

	// Handles equivalent layer properties of multilayer IGU that is made of
	// any type of layer (specular or diffuse)
	class CMultiLayerScattered : public SingleLayerOptics::IScatteringLayer {
	public:
		CMultiLayerScattered(
			const double t_Tf_dir_dir = 0, const double t_Rf_dir_dir = 0,
			const double t_Tb_dir_dir = 0, const double t_Rb_dir_dir = 0,
			const double t_Tf_dir_dif = 0, const double t_Rf_dir_dif = 0,
			const double t_Tb_dir_dif = 0, const double t_Rb_dir_dif = 0,
			const double t_Tf_dif_dif = 0, const double t_Rf_dif_dif = 0,
			const double t_Tb_dif_dif = 0, const double t_Rb_dif_dif = 0 );

		explicit CMultiLayerScattered( const SingleLayerOptics::CScatteringLayer & t_Layer );

		void addLayer(
			const double t_Tf_dir_dir, const double t_Rf_dir_dir,
			const double t_Tb_dir_dir, const double t_Rb_dir_dir,
			const double t_Tf_dir_dif, const double t_Rf_dir_dif,
			const double t_Tb_dir_dif, const double t_Rb_dir_dif,
			const double t_Tf_dif_dif, const double t_Rf_dif_dif,
			const double t_Tb_dif_dif, const double t_Rb_dif_dif,
			const FenestrationCommon::Side t_Side = FenestrationCommon::Side::Back );

		void addLayer( const SingleLayerOptics::CScatteringLayer & t_Layer,
		               const FenestrationCommon::Side t_Side = FenestrationCommon::Side::Back );

		void setSourceData( std::shared_ptr< FenestrationCommon::CSeries > t_SourceData );

		size_t getNumOfLayers() const;

		double getPropertySimple(
			const FenestrationCommon::PropertySimple t_Property,
			const FenestrationCommon::Side t_Side,
			const FenestrationCommon::Scattering t_Scattering,
			const double t_Theta = 0,
			const double t_Phi = 0 ) override;

		double getAbsorptanceLayer(
			const size_t Index, FenestrationCommon::Side t_Side,
			FenestrationCommon::ScatteringSimple t_Scattering,
			const double t_Theta = 0,
			const double t_Phi = 0 );

		double getAbsorptance(
			FenestrationCommon::Side t_Side,
			FenestrationCommon::ScatteringSimple t_Scattering,
			const double t_Theta = 0,
			const double t_Phi = 0 );

		std::vector< double > getWavelengths() const override;

		double getMinLambda() const override;
		double getMaxLambda() const override;

	private:
		void initialize( const SingleLayerOptics::CScatteringLayer & t_Layer );

		void calculateState( const double t_Theta, const double t_Phi );

		std::shared_ptr< CInterRef > m_InterRef;
		std::shared_ptr< CEquivalentScatteringLayer > m_Layer;
		std::vector< SingleLayerOptics::CScatteringLayer > m_Layers;

		bool m_Calculated;
		double m_Theta;
		double m_Phi;
	};
}

#endif
