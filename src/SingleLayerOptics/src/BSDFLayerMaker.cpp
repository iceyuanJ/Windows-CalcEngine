#include <stdexcept>

#include "BSDFLayerMaker.hpp"
#include "UniformDiffuseCell.hpp"
#include "DirectionalDiffuseCell.hpp"
#include "UniformDiffuseBSDFLayer.hpp"
#include "DirectionalDiffuseBSDFLayer.hpp"
#include "CellDescription.hpp"
#include "SpecularCellDescription.hpp"
#include "BaseCell.hpp"
#include "SpecularCell.hpp"
#include "SpecularBSDFLayer.hpp"
#include "VenetianCellDescription.hpp"
#include "VenetianCell.hpp"
#include "PerforatedCellDescription.hpp"
#include "PerforatedCell.hpp"
#include "WovenCellDescription.hpp"
#include "WovenCell.hpp"
#include "PerfectDiffuseCellDescription.hpp"
#include <WCECommon.hpp>

namespace SingleLayerOptics
{
    std::shared_ptr<CBaseCell> CBSDFLayerMaker::getCell() const
    {
        return m_Cell;
    }

    std::shared_ptr<CBSDFLayer>
      CBSDFLayerMaker::getSpecularLayer(const std::shared_ptr<CMaterial> & t_Material,
                                        const std::shared_ptr<const CBSDFHemisphere> & t_BSDF)
    {
        auto aDescription = std::make_shared<CSpecularCellDescription>();
        auto aCell = std::make_shared<CSpecularCell>(t_Material, aDescription);
        return std::make_shared<CSpecularBSDFLayer>(aCell, t_BSDF);
    }

    std::shared_ptr<CBSDFLayer> CBSDFLayerMaker::getCircularPerforatedLayer(
      const std::shared_ptr<CMaterial> & t_Material,
      const std::shared_ptr<const CBSDFHemisphere> & t_BSDF,
      double x,
      double y,
      double thickness,
      double radius)
    {
        std::shared_ptr<ICellDescription> aCellDescription =
          std::make_shared<CCircularCellDescription>(x, y, thickness, radius);
        std::shared_ptr<CUniformDiffuseCell> aCell =
          std::make_shared<CPerforatedCell>(t_Material, aCellDescription);
        return std::make_shared<CUniformDiffuseBSDFLayer>(aCell, t_BSDF);
    }

    std::shared_ptr<CBSDFLayer> CBSDFLayerMaker::getRectangularPerforatedLayer(
      const std::shared_ptr<CMaterial> & t_Material,
      const std::shared_ptr<const CBSDFHemisphere> & t_BSDF,
      const double x,
      const double y,
      const double thickness,
      const double xHole,
      const double yHole)
    {
        std::shared_ptr<ICellDescription> aCellDescription =
          std::make_shared<CRectangularCellDescription>(x, y, thickness, xHole, yHole);
        std::shared_ptr<CUniformDiffuseCell> aCell =
          std::make_shared<CPerforatedCell>(t_Material, aCellDescription);
        return std::make_shared<CUniformDiffuseBSDFLayer>(aCell, t_BSDF);
    }

    std::shared_ptr<CBSDFLayer>
      CBSDFLayerMaker::getVenetianLayer(const std::shared_ptr<CMaterial> & t_Material,
                                        const std::shared_ptr<const CBSDFHemisphere> & t_BSDF,
                                        const double slatWidth,
                                        const double slatSpacing,
                                        const double slatTiltAngle,
                                        const double curvatureRadius,
                                        const size_t numOfSlatSegments,
                                        const DistributionMethod method)
    {
        std::shared_ptr<ICellDescription> aCellDescription =
          std::make_shared<CVenetianCellDescription>(
            slatWidth, slatSpacing, slatTiltAngle, curvatureRadius, numOfSlatSegments);
        if(method == DistributionMethod::UniformDiffuse)
        {
            std::shared_ptr<CUniformDiffuseCell> aCell =
              std::make_shared<CVenetianCell>(t_Material, aCellDescription);
            return std::make_shared<CUniformDiffuseBSDFLayer>(aCell, t_BSDF);
        }
        else
        {
            std::shared_ptr<CDirectionalDiffuseCell> aCell =
              std::make_shared<CVenetianCell>(t_Material, aCellDescription);
            return std::make_shared<CDirectionalDiffuseBSDFLayer>(aCell, t_BSDF);
        }
    }

    std::shared_ptr<CBSDFLayer> CBSDFLayerMaker::getPerfectlyDiffuseLayer(
      const std::shared_ptr<CMaterial> & t_Material,
      const std::shared_ptr<const CBSDFHemisphere> & t_BSDF)
    {
        auto aDescription = std::make_shared<CPerfectDiffuseCellDescription>();
        auto aCell = std::make_shared<CUniformDiffuseCell>(t_Material, aDescription);
        return std::make_shared<CUniformDiffuseBSDFLayer>(aCell, t_BSDF);
    }

    std::shared_ptr<CBSDFLayer>
      CBSDFLayerMaker::getWovenLayer(const std::shared_ptr<CMaterial> & t_Material,
                                     const std::shared_ptr<const CBSDFHemisphere> & t_BSDF,
                                     double diameter,
                                     double spacing)
    {
        auto aDescription = std::make_shared<CWovenCellDescription>(diameter, spacing);
        auto aCell = std::make_shared<CUniformDiffuseCell>(t_Material, aDescription);
        return std::make_shared<CUniformDiffuseBSDFLayer>(aCell, t_BSDF);
    }

}   // namespace SingleLayerOptics
