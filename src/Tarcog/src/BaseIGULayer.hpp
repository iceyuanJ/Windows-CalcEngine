#ifndef BASEIGUTARCOGLAYER_H
#define BASEIGUTARCOGLAYER_H

#include <memory>
#include "BaseLayer.hpp"

namespace FenestrationCommon
{
    enum class Side;

}

namespace Tarcog
{
    class CBaseIGULayer : public CBaseLayer
    {
    public:
        explicit CBaseIGULayer(double t_Thickness);

        double getThickness() const;
        double getTemperature(FenestrationCommon::Side t_Position) const;
        double J(FenestrationCommon::Side t_Position) const;
        double getMaxDeflection() const;
        double getMeanDeflection() const;

        double getConductivity();

    protected:
        virtual double layerTemperature();

        double m_Thickness;
    };

}   // namespace Tarcog
#endif
