#include <memory>
#include <gtest/gtest.h>

#include "WCESpectralAveraging.hpp"
#include "WCEMultiLayerOptics.hpp"
#include "WCESingleLayerOptics.hpp"
#include "WCECommon.hpp"


using namespace SingleLayerOptics;
using namespace FenestrationCommon;
using namespace SpectralAveraging;
using namespace MultiLayerOptics;

// Example on how to create scattered multilayer.

class MultiPaneScattered_102_PerforatedRectangular : public testing::Test {

private:
	std::shared_ptr< CMultiLayerScattered > m_Layer;

	std::shared_ptr< CSeries > loadSolarRadiationFile() const {

		auto aSolarRadiation = std::make_shared< CSeries >();

		// Full ASTM E891-87 Table 1 (Solar radiation)
		aSolarRadiation->addProperty( 0.3000, 0.0 );
		aSolarRadiation->addProperty( 0.3050, 3.4 );
		aSolarRadiation->addProperty( 0.3100, 15.6 );
		aSolarRadiation->addProperty( 0.3150, 41.1 );
		aSolarRadiation->addProperty( 0.3200, 71.2 );
		aSolarRadiation->addProperty( 0.3250, 100.2 );
		aSolarRadiation->addProperty( 0.3300, 152.4 );
		aSolarRadiation->addProperty( 0.3350, 155.6 );
		aSolarRadiation->addProperty( 0.3400, 179.4 );
		aSolarRadiation->addProperty( 0.3450, 186.7 );
		aSolarRadiation->addProperty( 0.3500, 212.0 );
		aSolarRadiation->addProperty( 0.3600, 240.5 );
		aSolarRadiation->addProperty( 0.3700, 324.0 );
		aSolarRadiation->addProperty( 0.3800, 362.4 );
		aSolarRadiation->addProperty( 0.3900, 381.7 );
		aSolarRadiation->addProperty( 0.4000, 556.0 );
		aSolarRadiation->addProperty( 0.4100, 656.3 );
		aSolarRadiation->addProperty( 0.4200, 690.8 );
		aSolarRadiation->addProperty( 0.4300, 641.9 );
		aSolarRadiation->addProperty( 0.4400, 798.5 );
		aSolarRadiation->addProperty( 0.4500, 956.6 );
		aSolarRadiation->addProperty( 0.4600, 990.0 );
		aSolarRadiation->addProperty( 0.4700, 998.0 );
		aSolarRadiation->addProperty( 0.4800, 1046.1 );
		aSolarRadiation->addProperty( 0.4900, 1005.1 );
		aSolarRadiation->addProperty( 0.5000, 1026.7 );
		aSolarRadiation->addProperty( 0.5100, 1066.7 );
		aSolarRadiation->addProperty( 0.5200, 1011.5 );
		aSolarRadiation->addProperty( 0.5300, 1084.9 );
		aSolarRadiation->addProperty( 0.5400, 1082.4 );
		aSolarRadiation->addProperty( 0.5500, 1102.2 );
		aSolarRadiation->addProperty( 0.5700, 1087.4 );
		aSolarRadiation->addProperty( 0.5900, 1024.3 );
		aSolarRadiation->addProperty( 0.6100, 1088.8 );
		aSolarRadiation->addProperty( 0.6300, 1062.1 );
		aSolarRadiation->addProperty( 0.6500, 1061.7 );
		aSolarRadiation->addProperty( 0.6700, 1046.2 );
		aSolarRadiation->addProperty( 0.6900, 859.2 );
		aSolarRadiation->addProperty( 0.7100, 1002.4 );
		aSolarRadiation->addProperty( 0.7180, 816.9 );
		aSolarRadiation->addProperty( 0.7244, 842.8 );
		aSolarRadiation->addProperty( 0.7400, 971.0 );
		aSolarRadiation->addProperty( 0.7525, 956.3 );
		aSolarRadiation->addProperty( 0.7575, 942.2 );
		aSolarRadiation->addProperty( 0.7625, 524.8 );
		aSolarRadiation->addProperty( 0.7675, 830.7 );
		aSolarRadiation->addProperty( 0.7800, 908.9 );
		aSolarRadiation->addProperty( 0.8000, 873.4 );
		aSolarRadiation->addProperty( 0.8160, 712.0 );
		aSolarRadiation->addProperty( 0.8237, 660.2 );
		aSolarRadiation->addProperty( 0.8315, 765.5 );
		aSolarRadiation->addProperty( 0.8400, 799.8 );
		aSolarRadiation->addProperty( 0.8600, 815.2 );
		aSolarRadiation->addProperty( 0.8800, 778.3 );
		aSolarRadiation->addProperty( 0.9050, 630.4 );
		aSolarRadiation->addProperty( 0.9150, 565.2 );
		aSolarRadiation->addProperty( 0.9250, 586.4 );
		aSolarRadiation->addProperty( 0.9300, 348.1 );
		aSolarRadiation->addProperty( 0.9370, 224.2 );
		aSolarRadiation->addProperty( 0.9480, 271.4 );
		aSolarRadiation->addProperty( 0.9650, 451.2 );
		aSolarRadiation->addProperty( 0.9800, 549.7 );
		aSolarRadiation->addProperty( 0.9935, 630.1 );
		aSolarRadiation->addProperty( 1.0400, 582.9 );
		aSolarRadiation->addProperty( 1.0700, 539.7 );
		aSolarRadiation->addProperty( 1.1000, 366.2 );
		aSolarRadiation->addProperty( 1.1200, 98.1 );
		aSolarRadiation->addProperty( 1.1300, 169.5 );
		aSolarRadiation->addProperty( 1.1370, 118.7 );
		aSolarRadiation->addProperty( 1.1610, 301.9 );
		aSolarRadiation->addProperty( 1.1800, 406.8 );
		aSolarRadiation->addProperty( 1.2000, 375.2 );
		aSolarRadiation->addProperty( 1.2350, 423.6 );
		aSolarRadiation->addProperty( 1.2900, 365.7 );
		aSolarRadiation->addProperty( 1.3200, 223.4 );
		aSolarRadiation->addProperty( 1.3500, 30.1 );
		aSolarRadiation->addProperty( 1.3950, 1.4 );
		aSolarRadiation->addProperty( 1.4425, 51.6 );
		aSolarRadiation->addProperty( 1.4625, 97.0 );
		aSolarRadiation->addProperty( 1.4770, 97.3 );
		aSolarRadiation->addProperty( 1.4970, 167.1 );
		aSolarRadiation->addProperty( 1.5200, 239.3 );
		aSolarRadiation->addProperty( 1.5390, 248.8 );
		aSolarRadiation->addProperty( 1.5580, 249.3 );
		aSolarRadiation->addProperty( 1.5780, 222.3 );
		aSolarRadiation->addProperty( 1.5920, 227.3 );
		aSolarRadiation->addProperty( 1.6100, 210.5 );
		aSolarRadiation->addProperty( 1.6300, 224.7 );
		aSolarRadiation->addProperty( 1.6460, 215.9 );
		aSolarRadiation->addProperty( 1.6780, 202.8 );
		aSolarRadiation->addProperty( 1.7400, 158.2 );
		aSolarRadiation->addProperty( 1.8000, 28.6 );
		aSolarRadiation->addProperty( 1.8600, 1.8 );
		aSolarRadiation->addProperty( 1.9200, 1.1 );
		aSolarRadiation->addProperty( 1.9600, 19.7 );
		aSolarRadiation->addProperty( 1.9850, 84.9 );
		aSolarRadiation->addProperty( 2.0050, 25.0 );
		aSolarRadiation->addProperty( 2.0350, 92.5 );
		aSolarRadiation->addProperty( 2.0650, 56.3 );
		aSolarRadiation->addProperty( 2.1000, 82.7 );
		aSolarRadiation->addProperty( 2.1480, 76.2 );
		aSolarRadiation->addProperty( 2.1980, 66.4 );
		aSolarRadiation->addProperty( 2.2700, 65.0 );
		aSolarRadiation->addProperty( 2.3600, 57.6 );
		aSolarRadiation->addProperty( 2.4500, 19.8 );
		aSolarRadiation->addProperty( 2.4940, 17.0 );
		aSolarRadiation->addProperty( 2.5370, 3.0 );
		aSolarRadiation->addProperty( 2.9410, 4.0 );
		aSolarRadiation->addProperty( 2.9730, 7.0 );
		aSolarRadiation->addProperty( 3.0050, 6.0 );
		aSolarRadiation->addProperty( 3.0560, 3.0 );
		aSolarRadiation->addProperty( 3.1320, 5.0 );
		aSolarRadiation->addProperty( 3.1560, 18.0 );
		aSolarRadiation->addProperty( 3.2040, 1.2 );
		aSolarRadiation->addProperty( 3.2450, 3.0 );
		aSolarRadiation->addProperty( 3.3170, 12.0 );
		aSolarRadiation->addProperty( 3.3440, 3.0 );
		aSolarRadiation->addProperty( 3.4500, 12.2 );
		aSolarRadiation->addProperty( 3.5730, 11.0 );
		aSolarRadiation->addProperty( 3.7650, 9.0 );
		aSolarRadiation->addProperty( 4.0450, 6.9 );

		return aSolarRadiation;
	}

	std::shared_ptr< CSpectralSampleData > loadSampleData_NFRC_102() const {
		auto aMeasurements_102 = std::make_shared< CSpectralSampleData >();

		aMeasurements_102->addRecord( 0.300, 0.0020, 0.0470, 0.0480 );
		aMeasurements_102->addRecord( 0.305, 0.0030, 0.0470, 0.0480 );
		aMeasurements_102->addRecord( 0.310, 0.0090, 0.0470, 0.0480 );
		aMeasurements_102->addRecord( 0.315, 0.0350, 0.0470, 0.0480 );
		aMeasurements_102->addRecord( 0.320, 0.1000, 0.0470, 0.0480 );
		aMeasurements_102->addRecord( 0.325, 0.2180, 0.0490, 0.0500 );
		aMeasurements_102->addRecord( 0.330, 0.3560, 0.0530, 0.0540 );
		aMeasurements_102->addRecord( 0.335, 0.4980, 0.0600, 0.0610 );
		aMeasurements_102->addRecord( 0.340, 0.6160, 0.0670, 0.0670 );
		aMeasurements_102->addRecord( 0.345, 0.7090, 0.0730, 0.0740 );
		aMeasurements_102->addRecord( 0.350, 0.7740, 0.0780, 0.0790 );
		aMeasurements_102->addRecord( 0.355, 0.8180, 0.0820, 0.0820 );
		aMeasurements_102->addRecord( 0.360, 0.8470, 0.0840, 0.0840 );
		aMeasurements_102->addRecord( 0.365, 0.8630, 0.0850, 0.0850 );
		aMeasurements_102->addRecord( 0.370, 0.8690, 0.0850, 0.0860 );
		aMeasurements_102->addRecord( 0.375, 0.8610, 0.0850, 0.0850 );
		aMeasurements_102->addRecord( 0.380, 0.8560, 0.0840, 0.0840 );
		aMeasurements_102->addRecord( 0.385, 0.8660, 0.0850, 0.0850 );
		aMeasurements_102->addRecord( 0.390, 0.8810, 0.0860, 0.0860 );
		aMeasurements_102->addRecord( 0.395, 0.8890, 0.0860, 0.0860 );
		aMeasurements_102->addRecord( 0.400, 0.8930, 0.0860, 0.0860 );
		aMeasurements_102->addRecord( 0.410, 0.8930, 0.0860, 0.0860 );
		aMeasurements_102->addRecord( 0.420, 0.8920, 0.0860, 0.0860 );
		aMeasurements_102->addRecord( 0.430, 0.8920, 0.0850, 0.0850 );
		aMeasurements_102->addRecord( 0.440, 0.8920, 0.0850, 0.0850 );
		aMeasurements_102->addRecord( 0.450, 0.8960, 0.0850, 0.0850 );
		aMeasurements_102->addRecord( 0.460, 0.9000, 0.0850, 0.0850 );
		aMeasurements_102->addRecord( 0.470, 0.9020, 0.0840, 0.0840 );
		aMeasurements_102->addRecord( 0.480, 0.9030, 0.0840, 0.0840 );
		aMeasurements_102->addRecord( 0.490, 0.9040, 0.0850, 0.0850 );
		aMeasurements_102->addRecord( 0.500, 0.9050, 0.0840, 0.0840 );
		aMeasurements_102->addRecord( 0.510, 0.9050, 0.0840, 0.0840 );
		aMeasurements_102->addRecord( 0.520, 0.9050, 0.0840, 0.0840 );
		aMeasurements_102->addRecord( 0.530, 0.9040, 0.0840, 0.0840 );
		aMeasurements_102->addRecord( 0.540, 0.9040, 0.0830, 0.0830 );
		aMeasurements_102->addRecord( 0.550, 0.9030, 0.0830, 0.0830 );
		aMeasurements_102->addRecord( 0.560, 0.9020, 0.0830, 0.0830 );
		aMeasurements_102->addRecord( 0.570, 0.9000, 0.0820, 0.0820 );
		aMeasurements_102->addRecord( 0.580, 0.8980, 0.0820, 0.0820 );
		aMeasurements_102->addRecord( 0.590, 0.8960, 0.0810, 0.0810 );
		aMeasurements_102->addRecord( 0.600, 0.8930, 0.0810, 0.0810 );
		aMeasurements_102->addRecord( 0.610, 0.8900, 0.0810, 0.0810 );
		aMeasurements_102->addRecord( 0.620, 0.8860, 0.0800, 0.0800 );
		aMeasurements_102->addRecord( 0.630, 0.8830, 0.0800, 0.0800 );
		aMeasurements_102->addRecord( 0.640, 0.8790, 0.0790, 0.0790 );
		aMeasurements_102->addRecord( 0.650, 0.8750, 0.0790, 0.0790 );
		aMeasurements_102->addRecord( 0.660, 0.8720, 0.0790, 0.0790 );
		aMeasurements_102->addRecord( 0.670, 0.8680, 0.0780, 0.0780 );
		aMeasurements_102->addRecord( 0.680, 0.8630, 0.0780, 0.0780 );
		aMeasurements_102->addRecord( 0.690, 0.8590, 0.0770, 0.0770 );
		aMeasurements_102->addRecord( 0.700, 0.8540, 0.0760, 0.0770 );
		aMeasurements_102->addRecord( 0.710, 0.8500, 0.0760, 0.0760 );
		aMeasurements_102->addRecord( 0.720, 0.8450, 0.0750, 0.0760 );
		aMeasurements_102->addRecord( 0.730, 0.8400, 0.0750, 0.0750 );
		aMeasurements_102->addRecord( 0.740, 0.8350, 0.0750, 0.0750 );
		aMeasurements_102->addRecord( 0.750, 0.8310, 0.0740, 0.0740 );
		aMeasurements_102->addRecord( 0.760, 0.8260, 0.0740, 0.0740 );
		aMeasurements_102->addRecord( 0.770, 0.8210, 0.0740, 0.0740 );
		aMeasurements_102->addRecord( 0.780, 0.8160, 0.0730, 0.0730 );
		aMeasurements_102->addRecord( 0.790, 0.8120, 0.0730, 0.0730 );
		aMeasurements_102->addRecord( 0.800, 0.8080, 0.0720, 0.0720 );
		aMeasurements_102->addRecord( 0.810, 0.8030, 0.0720, 0.0720 );
		aMeasurements_102->addRecord( 0.820, 0.8000, 0.0720, 0.0720 );
		aMeasurements_102->addRecord( 0.830, 0.7960, 0.0710, 0.0710 );
		aMeasurements_102->addRecord( 0.840, 0.7930, 0.0700, 0.0710 );
		aMeasurements_102->addRecord( 0.850, 0.7880, 0.0700, 0.0710 );
		aMeasurements_102->addRecord( 0.860, 0.7860, 0.0700, 0.0700 );
		aMeasurements_102->addRecord( 0.870, 0.7820, 0.0740, 0.0740 );
		aMeasurements_102->addRecord( 0.880, 0.7800, 0.0720, 0.0720 );
		aMeasurements_102->addRecord( 0.890, 0.7770, 0.0730, 0.0740 );
		aMeasurements_102->addRecord( 0.900, 0.7760, 0.0720, 0.0720 );
		aMeasurements_102->addRecord( 0.910, 0.7730, 0.0720, 0.0720 );
		aMeasurements_102->addRecord( 0.920, 0.7710, 0.0710, 0.0710 );
		aMeasurements_102->addRecord( 0.930, 0.7700, 0.0700, 0.0700 );
		aMeasurements_102->addRecord( 0.940, 0.7680, 0.0690, 0.0690 );
		aMeasurements_102->addRecord( 0.950, 0.7660, 0.0680, 0.0680 );
		aMeasurements_102->addRecord( 0.960, 0.7660, 0.0670, 0.0680 );
		aMeasurements_102->addRecord( 0.970, 0.7640, 0.0680, 0.0680 );
		aMeasurements_102->addRecord( 0.980, 0.7630, 0.0680, 0.0680 );
		aMeasurements_102->addRecord( 0.990, 0.7620, 0.0670, 0.0670 );
		aMeasurements_102->addRecord( 1.000, 0.7620, 0.0660, 0.0670 );
		aMeasurements_102->addRecord( 1.050, 0.7600, 0.0660, 0.0660 );
		aMeasurements_102->addRecord( 1.100, 0.7590, 0.0660, 0.0660 );
		aMeasurements_102->addRecord( 1.150, 0.7610, 0.0660, 0.0660 );
		aMeasurements_102->addRecord( 1.200, 0.7650, 0.0660, 0.0660 );
		aMeasurements_102->addRecord( 1.250, 0.7700, 0.0650, 0.0650 );
		aMeasurements_102->addRecord( 1.300, 0.7770, 0.0670, 0.0670 );
		aMeasurements_102->addRecord( 1.350, 0.7860, 0.0660, 0.0670 );
		aMeasurements_102->addRecord( 1.400, 0.7950, 0.0670, 0.0680 );
		aMeasurements_102->addRecord( 1.450, 0.8080, 0.0670, 0.0670 );
		aMeasurements_102->addRecord( 1.500, 0.8190, 0.0690, 0.0690 );
		aMeasurements_102->addRecord( 1.550, 0.8290, 0.0690, 0.0690 );
		aMeasurements_102->addRecord( 1.600, 0.8360, 0.0700, 0.0700 );
		aMeasurements_102->addRecord( 1.650, 0.8400, 0.0700, 0.0700 );
		aMeasurements_102->addRecord( 1.700, 0.8420, 0.0690, 0.0700 );
		aMeasurements_102->addRecord( 1.750, 0.8420, 0.0690, 0.0700 );
		aMeasurements_102->addRecord( 1.800, 0.8410, 0.0700, 0.0700 );
		aMeasurements_102->addRecord( 1.850, 0.8400, 0.0690, 0.0690 );
		aMeasurements_102->addRecord( 1.900, 0.8390, 0.0680, 0.0680 );
		aMeasurements_102->addRecord( 1.950, 0.8390, 0.0710, 0.0710 );
		aMeasurements_102->addRecord( 2.000, 0.8390, 0.0690, 0.0690 );
		aMeasurements_102->addRecord( 2.050, 0.8400, 0.0680, 0.0680 );
		aMeasurements_102->addRecord( 2.100, 0.8410, 0.0680, 0.0680 );
		aMeasurements_102->addRecord( 2.150, 0.8390, 0.0690, 0.0690 );
		aMeasurements_102->addRecord( 2.200, 0.8300, 0.0700, 0.0700 );
		aMeasurements_102->addRecord( 2.250, 0.8300, 0.0700, 0.0700 );
		aMeasurements_102->addRecord( 2.300, 0.8320, 0.0690, 0.0690 );
		aMeasurements_102->addRecord( 2.350, 0.8320, 0.0690, 0.0700 );
		aMeasurements_102->addRecord( 2.400, 0.8320, 0.0700, 0.0700 );
		aMeasurements_102->addRecord( 2.450, 0.8260, 0.0690, 0.0690 );
		aMeasurements_102->addRecord( 2.500, 0.8220, 0.0680, 0.0680 );

		return aMeasurements_102;

	}

protected:
	void SetUp() override {

		auto aMeasurements_102 = loadSampleData_NFRC_102();

		// Create samples from measurements and solar radiation
		auto aSample_102 = std::make_shared< CSpectralSample >( aMeasurements_102 );

		// Create material from samples
		auto thickness = 3.048e-3; // [m]
		std::shared_ptr< CMaterial > aMaterial_102 = std::make_shared< CMaterialSample >( aSample_102,
		                                                                        thickness, MaterialType::Monolithic, WavelengthRange::Solar );

		// Setting rectangular perforated shade with double range material
		double Tmat = 0.1;
		double Rfmat = 0.7;
		double Rbmat = 0.7;
		std::shared_ptr<CMaterial> aSolarRangeMaterial =
			std::make_shared<CMaterialSingleBand>(Tmat, Tmat, Rfmat, Rbmat, WavelengthRange::Solar);

		// Visible range
		Tmat = 0.2;
		Rfmat = 0.6;
		Rbmat = 0.6;
		std::shared_ptr<CMaterial> aVisibleRangeMaterial =
			std::make_shared<CMaterialSingleBand>(Tmat, Tmat, Rfmat, Rbmat, WavelengthRange::Visible);

		std::shared_ptr<CMaterial> aMaterialPerforated =
			std::make_shared<CMaterialDualBand>(aVisibleRangeMaterial, aSolarRangeMaterial);

		// make cell geometry
		const double x = 19.05;        // mm
		const double y = 19.05;        // mm
		thickness = 5;           // mm
		const double xHole = 5;        // mm
		const double yHole = 5;        // mm

		CScatteringLayer Layer102 = CScatteringLayer::createSpecularLayer( aMaterial_102 );
		CScatteringLayer LayerPerforated = CScatteringLayer::createPerforatedRectangularLayer(
			aMaterialPerforated, x, y, thickness, xHole, yHole );

		// Equivalent BSDF layer
		m_Layer = std::make_shared< CMultiLayerScattered >( Layer102 );
		m_Layer->addLayer( LayerPerforated );

		auto aSolarRadiation = loadSolarRadiationFile();
		m_Layer->setSourceData( aSolarRadiation );

	}

public:
	std::shared_ptr< CMultiLayerScattered > getLayer() const {
		return m_Layer;
	};

};

TEST_F( MultiPaneScattered_102_PerforatedRectangular, TestPerforatedRectangularDirectBeam ) {
	SCOPED_TRACE( "Begin Test: Perforated rectangular layer - Scattering model front side (normal incidence)." );

	auto& aLayer = *getLayer();

	auto aSide = Side::Front;
	double theta = 0;
	double phi = 0;

	auto T_dir_dir = aLayer.getPropertySimple( PropertySimple::T, aSide, Scattering::DirectDirect, theta, phi );
	EXPECT_NEAR( 0.057440, T_dir_dir, 1e-6 );

	auto T_dir_dif = aLayer.getPropertySimple( PropertySimple::T, aSide, Scattering::DirectDiffuse, theta, phi );
	EXPECT_NEAR( 0.087586, T_dir_dif, 1e-6 );

	auto T_dif_dif = aLayer.getPropertySimple( PropertySimple::T, aSide, Scattering::DiffuseDiffuse, theta, phi );
	EXPECT_NEAR( 0.094272, T_dif_dif, 1e-6 );

	auto R_dir_dir = aLayer.getPropertySimple( PropertySimple::R, aSide, Scattering::DirectDirect, theta, phi );
	EXPECT_NEAR( 0.074817, R_dir_dir, 1e-6 );

	auto R_dir_dif = aLayer.getPropertySimple( PropertySimple::R, aSide, Scattering::DirectDiffuse, theta, phi );
	EXPECT_NEAR( 0.454929, R_dir_dif, 1e-6 );

	auto R_dif_dif = aLayer.getPropertySimple( PropertySimple::R, aSide, Scattering::DiffuseDiffuse, theta, phi );
	EXPECT_NEAR( 0.580893, R_dif_dif, 1e-6 );

	auto A_dir1 = aLayer.getAbsorptanceLayer( 1, aSide, ScatteringSimple::Direct, theta, phi );
	EXPECT_NEAR( 0.152533, A_dir1, 1e-6 );

	auto A_dir2 = aLayer.getAbsorptanceLayer( 2, aSide, ScatteringSimple::Direct, theta, phi );
	EXPECT_NEAR( 0.172695, A_dir2, 1e-6 );

	auto A_dif1 = aLayer.getAbsorptanceLayer( 1, aSide, ScatteringSimple::Diffuse, theta, phi );
	EXPECT_NEAR( 0.159761, A_dif1, 1e-6 );

	auto A_dif2 = aLayer.getAbsorptanceLayer( 2, aSide, ScatteringSimple::Diffuse, theta, phi );
	EXPECT_NEAR( 0.165073, A_dif2, 1e-6 );

}

TEST_F( MultiPaneScattered_102_PerforatedRectangular, TestPerforatedRectangularAngledBeam25 ) {
	SCOPED_TRACE( "Begin Test: Perforated rectangular layer - Scattering model back side (normal incidence)." );

	auto& aLayer = *getLayer();

	auto aSide = Side::Front;
	double theta = 25;
	double phi = 0;

	auto T_dir_dir = aLayer.getPropertySimple( PropertySimple::T, aSide, Scattering::DirectDirect, theta, phi );
	EXPECT_NEAR( 0.030501, T_dir_dir, 1e-6 );

	auto T_dir_dif = aLayer.getPropertySimple( PropertySimple::T, aSide, Scattering::DirectDiffuse, theta, phi );
	EXPECT_NEAR( 0.095823, T_dir_dif, 1e-6 );

	auto T_dif_dif = aLayer.getPropertySimple( PropertySimple::T, aSide, Scattering::DiffuseDiffuse, theta, phi );
	EXPECT_NEAR( 0.094272, T_dif_dif, 1e-6 );

	auto R_dir_dir = aLayer.getPropertySimple( PropertySimple::R, aSide, Scattering::DirectDirect, theta, phi );
	EXPECT_NEAR( 0.075583, R_dir_dir, 1e-6 );

	auto R_dir_dif = aLayer.getPropertySimple( PropertySimple::R, aSide, Scattering::DirectDiffuse, theta, phi );
	EXPECT_NEAR( 0.467180, R_dir_dif, 1e-6 );

	auto R_dif_dif = aLayer.getPropertySimple( PropertySimple::R, aSide, Scattering::DiffuseDiffuse, theta, phi );
	EXPECT_NEAR( 0.580893, R_dif_dif, 1e-6 );

	auto A_dir1 = aLayer.getAbsorptanceLayer( 1, aSide, ScatteringSimple::Direct, theta, phi );
	EXPECT_NEAR( 0.155684, A_dir1, 1e-6 );

	auto A_dir2 = aLayer.getAbsorptanceLayer( 2, aSide, ScatteringSimple::Direct, theta, phi );
	EXPECT_NEAR( 0.176836, A_dir2, 1e-6 );

	auto A_dif1 = aLayer.getAbsorptanceLayer( 1, aSide, ScatteringSimple::Diffuse, theta, phi );
	EXPECT_NEAR( 0.159761, A_dif1, 1e-6 );

	auto A_dif2 = aLayer.getAbsorptanceLayer( 2, aSide, ScatteringSimple::Diffuse, theta, phi );
	EXPECT_NEAR( 0.165073, A_dif2, 1e-6 );

}

TEST_F( MultiPaneScattered_102_PerforatedRectangular, TestPerforatedRectangularAngleBeam50 ) {
	SCOPED_TRACE( "Begin Test: Perforated rectangular layer - Scattering model front side (Theta = 50 deg)." );

	auto& aLayer = *getLayer();

	auto aSide = Side::Front;
	double theta = 50;
	double phi = 0;

	auto T_dir_dir = aLayer.getPropertySimple( PropertySimple::T, aSide, Scattering::DirectDirect, theta, phi );
	EXPECT_NEAR( 0.0, T_dir_dir, 1e-6 );

	auto T_dir_dif = aLayer.getPropertySimple( PropertySimple::T, aSide, Scattering::DirectDiffuse, theta, phi );
	EXPECT_NEAR( 0.094066, T_dir_dif, 1e-6 );

	auto T_dif_dif = aLayer.getPropertySimple( PropertySimple::T, aSide, Scattering::DiffuseDiffuse, theta, phi );
	EXPECT_NEAR( 0.094272, T_dif_dif, 1e-6 );

	auto R_dir_dir = aLayer.getPropertySimple( PropertySimple::R, aSide, Scattering::DirectDirect, theta, phi );
	EXPECT_NEAR( 0.099211, R_dir_dir, 1e-6 );

	auto R_dir_dif = aLayer.getPropertySimple( PropertySimple::R, aSide, Scattering::DirectDiffuse, theta, phi );
	EXPECT_NEAR( 0.488588, R_dir_dif, 1e-6 );

	auto R_dif_dif = aLayer.getPropertySimple( PropertySimple::R, aSide, Scattering::DiffuseDiffuse, theta, phi );
	EXPECT_NEAR( 0.580893, R_dif_dif, 1e-6 );

	auto A_dir1 = aLayer.getAbsorptanceLayer( 1, aSide, ScatteringSimple::Direct, theta, phi );
	EXPECT_NEAR( 0.166924, A_dir1, 1e-6 );

	auto A_dir2 = aLayer.getAbsorptanceLayer( 2, aSide, ScatteringSimple::Direct, theta, phi );
	EXPECT_NEAR( 0.177199, A_dir2, 1e-6 );

	auto A_dif1 = aLayer.getAbsorptanceLayer( 1, aSide, ScatteringSimple::Diffuse, theta, phi );
	EXPECT_NEAR( 0.159761, A_dif1, 1e-6 );

	auto A_dif2 = aLayer.getAbsorptanceLayer( 2, aSide, ScatteringSimple::Diffuse, theta, phi );
	EXPECT_NEAR( 0.165073, A_dif2, 1e-6 );

}
