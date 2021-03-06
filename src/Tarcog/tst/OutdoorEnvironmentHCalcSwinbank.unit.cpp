#include <memory>
#include <stdexcept>
#include <gtest/gtest.h>

#include "WCETarcog.hpp"

using namespace Tarcog;


class TestOutdoorEnvironmentHCalcSwingbank : public testing::Test {

private:
	std::shared_ptr< CEnvironment > Outdoor;
	std::shared_ptr< CSingleSystem > m_TarcogSystem;

protected:
	void SetUp() override {
		/////////////////////////////////////////////////////////
		// Outdoor
		/////////////////////////////////////////////////////////
		auto airTemperature = 300.0; // Kelvins
		auto pressure = 101325.0; // Pascals
		auto airSpeed = 5.5; // meters per second
		auto airDirection = AirHorizontalDirection::Windward;
		auto tSky = 270.0; // Kelvins
		auto solarRadiation = 0.0;

		Outdoor = std::make_shared< COutdoorEnvironment >( airTemperature, pressure, airSpeed, solarRadiation,
		                                              airDirection, tSky, SkyModel::Swinbank );
		ASSERT_TRUE( Outdoor != nullptr );
		Outdoor->setHCoeffModel( BoundaryConditionsCoeffModel::CalculateH );

		/////////////////////////////////////////////////////////
		// Indoor
		/////////////////////////////////////////////////////////

		auto roomTemperature = 294.15;

		std::shared_ptr< CEnvironment > Indoor = std::make_shared< CIndoorEnvironment >( roomTemperature, pressure );
		ASSERT_TRUE( Indoor != nullptr );

		/////////////////////////////////////////////////////////
		// IGU
		/////////////////////////////////////////////////////////
		auto solidLayerThickness = 0.003048; // [m]
		auto solidLayerConductance = 100.0;

		auto aSolidLayer = std::make_shared< CIGUSolidLayer >( solidLayerThickness, solidLayerConductance );
		ASSERT_TRUE( aSolidLayer != nullptr );

		auto windowWidth = 1.0;
		auto windowHeight = 1.0;
		CIGU aIGU( windowWidth, windowHeight );
		aIGU.addLayer( aSolidLayer );

		/////////////////////////////////////////////////////////
		// System
		/////////////////////////////////////////////////////////
		m_TarcogSystem = std::make_shared< CSingleSystem >( aIGU, Indoor, Outdoor );
		m_TarcogSystem->solve();
		ASSERT_TRUE( m_TarcogSystem != nullptr );
	}

public:
	std::shared_ptr< CEnvironment > GetOutdoors() const {
		return Outdoor;
	};

};

TEST_F( TestOutdoorEnvironmentHCalcSwingbank, CalculateH_Swinbank ) {
	SCOPED_TRACE( "Begin Test: Outdoors -> H model = Calculate; Sky Model = Swinbank" );

	auto aOutdoor = GetOutdoors();
	ASSERT_TRUE( aOutdoor != nullptr );

	auto radiosity = aOutdoor->getEnvironmentIR();
	EXPECT_NEAR( 423.17235, radiosity, 1e-6 );

	auto hc = aOutdoor->getHc();
	EXPECT_NEAR( 26, hc, 1e-6 );

	auto outIR = aOutdoor->getRadiationFlow();
	EXPECT_NEAR( 20.7751423, outIR, 1e-6 );

	auto outConvection = aOutdoor->getConvectionConductionFlow();
	EXPECT_NEAR( -48.607583, outConvection, 1e-6 );

	auto totalHeatFlow = aOutdoor->getHeatFlow();
	EXPECT_NEAR( -27.83244071, totalHeatFlow, 1e-6 );
}
