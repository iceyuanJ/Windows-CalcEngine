#ifndef BSDFLAYERMAKER_H
#define BSDFLAYERMAKER_H

#include <memory>

namespace SingleLayerOptics
{
    enum class DistributionMethod
    {
        UniformDiffuse,
        DirectionalDiffuse
    };

    class ICellDescription;
    class CMaterial;
    class CBSDFHemisphere;
    class CBSDFLayer;
    class CBaseCell;

    // Class to simplify interface for BSDF layer creation
    class CBSDFLayerMaker
    {
    public:

        std::shared_ptr<CBaseCell> getCell() const;

        static std::shared_ptr<CBSDFLayer>
          getSpecularLayer(const std::shared_ptr<CMaterial> & t_Material,
                           const std::shared_ptr<const CBSDFHemisphere> & t_BSDF);

        static std::shared_ptr<CBSDFLayer>
          getCircularPerforatedLayer(const std::shared_ptr<CMaterial> & t_Material,
                                     const std::shared_ptr<const CBSDFHemisphere> & t_BSDF,
                                     double x,
                                     double y,
                                     double thickness,
                                     double radius);

        static std::shared_ptr<CBSDFLayer>
          getRectangularPerforatedLayer(const std::shared_ptr<CMaterial> & t_Material,
                                        const std::shared_ptr<const CBSDFHemisphere> & t_BSDF,
                                        double x,
                                        double y,
                                        double thickness,
                                        double xHole,
                                        double yHole);

        static std::shared_ptr<CBSDFLayer> getVenetianLayer(
          const std::shared_ptr<CMaterial> & t_Material,
          const std::shared_ptr<const CBSDFHemisphere> & t_BSDF,
          double slatWidth,
          double slatSpacing,
          double slatTiltAngle,
          double curvatureRadius,
          size_t numOfSlatSegments,
          DistributionMethod method = DistributionMethod::DirectionalDiffuse);

        static std::shared_ptr<CBSDFLayer>
          getPerfectlyDiffuseLayer(const std::shared_ptr<CMaterial> & t_Material,
                                   const std::shared_ptr<const CBSDFHemisphere> & t_BSDF);

	    static std::shared_ptr<CBSDFLayer>
	    getWovenLayer(const std::shared_ptr<CMaterial> & t_Material,
	                                  const std::shared_ptr<const CBSDFHemisphere> & t_BSDF,
	                                  double diameter,
	                                  double spacing);

    private:
        std::shared_ptr<CBSDFLayer> m_Layer;
        std::shared_ptr<CBaseCell> m_Cell;
    };

}   // namespace SingleLayerOptics

#endif
