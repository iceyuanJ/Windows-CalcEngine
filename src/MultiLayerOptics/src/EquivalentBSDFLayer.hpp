#ifndef EQUIVALENTBSDFLAYERMULTIWL_H
#define EQUIVALENTBSDFLAYERMULTIWL_H

#include <memory>
#include <vector>
#include <map>

#include "AbsorptancesMultiPaneBSDF.hpp"

namespace FenestrationCommon
{
    class SquareMatrix;
    class CMatrixSeries;
    class CSeries;
    enum class Side;
    enum class PropertySimple;

}   // namespace FenestrationCommon

namespace SingleLayerOptics
{
    class CBSDFLayer;
    class CBSDFIntegrator;
    enum class BSDFDirection;
    class CBSDFDirections;

}   // namespace SingleLayerOptics

namespace MultiLayerOptics
{
    class CEquivalentBSDFLayerSingleBand;

    // Calculates equivalent BSDF matrices for transmittances and reflectances
    class CEquivalentBSDFLayer
    {
    public:
        CEquivalentBSDFLayer(std::vector<double> const & t_CommonWavelengths,
                             std::shared_ptr<SingleLayerOptics::CBSDFLayer> & t_Layer);

        void addLayer( std::shared_ptr<SingleLayerOptics::CBSDFLayer> & t_Layer );
        const SingleLayerOptics::CBSDFDirections & getDirections( const SingleLayerOptics::BSDFDirection t_Side ) const;
        std::vector<double> getCommonWavelengths() const;

        // Absorptance wavelength by wavelength matrices
        std::shared_ptr<FenestrationCommon::CMatrixSeries> getTotalA(const FenestrationCommon::Side t_Side);

        // Transmittance and reflectance wavelength by wavelength matrices
        std::shared_ptr<FenestrationCommon::CMatrixSeries> getTotal(const FenestrationCommon::Side t_Side,
                                                                    const FenestrationCommon::PropertySimple t_Property);

        void setSolarRadiation(const std::shared_ptr<FenestrationCommon::CSeries> & t_SolarRadiation);

    private:
        void calculate();

        // Wavelength layer per layer calculations
        void calculateWavelengthProperties(size_t const t_NumOfLayers, size_t const t_Start, size_t const t_End);

        void updateWavelengthLayers(SingleLayerOptics::CBSDFLayer & t_Layer);

        // std::vector of layer results over each wavelength
        std::vector<CEquivalentBSDFLayerSingleBand> m_LayersWL;

        // Layers that are added to the equivalent layer
        std::vector<std::shared_ptr<SingleLayerOptics::CBSDFLayer>> m_Layer;

        // Total absoprtance coefficients for every wavelength (does not include source data)
        std::map<FenestrationCommon::Side, std::shared_ptr<FenestrationCommon::CMatrixSeries>> m_TotA;

        // Total Transmittance and Reflectance values for every wavelength (does not include source data)
        std::map<std::pair<FenestrationCommon::Side, FenestrationCommon::PropertySimple>, std::shared_ptr<FenestrationCommon::CMatrixSeries>> m_Tot;

        const FenestrationCommon::SquareMatrix m_Lambda;

        std::vector<double> m_CombinedLayerWavelengths;
        bool m_Calculated;
    };

}   // namespace MultiLayerOptics

#endif
