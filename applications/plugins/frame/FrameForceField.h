/******************************************************************************
*       SOFA, Simulation Open-Framework Architecture, version 1.0 beta 4      *
*                (c) 2006-2009 MGH, INRIA, USTL, UJF, CNRS                    *
*                                                                             *
* This library is free software; you can redistribute it and/or modify it     *
* under the terms of the GNU Lesser General Public License as published by    *
* the Free Software Foundation; either version 2.1 of the License, or (at     *
* your option) any later version.                                             *
*                                                                             *
* This library is distributed in the hope that it will be useful, but WITHOUT *
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or       *
* FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License *
* for more details.                                                           *
*                                                                             *
* You should have received a copy of the GNU Lesser General Public License    *
* along with this library; if not, write to the Free Software Foundation,     *
* Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301 USA.          *
*******************************************************************************
*                              SOFA :: Framework                              *
*                                                                             *
* Authors: M. Adam, J. Allard, B. Andre, P-J. Bensoussan, S. Cotin, C. Duriez,*
* H. Delingette, F. Falipou, F. Faure, S. Fonteneau, L. Heigeas, C. Mendoza,  *
* M. Nesme, P. Neumann, J-P. de la Plata Alcade, F. Poyer and F. Roy          *
*                                                                             *
* Contact information: contact@sofa-framework.org                             *
******************************************************************************/
#ifndef FRAME_FRAMEFORCEFIELD_H
#define FRAME_FRAMEFORCEFIELD_H

#include <sofa/core/behavior/ForceField.h>
#include "AffineTypes.h"
#include "initFrame.h"
#include "GridMaterial.h"
#include "MappingTypes.h"

namespace sofa
{

namespace component
{

namespace forcefield
{

using helper::vector;

using namespace sofa::defaulttype;
/** Compute strain and apply material law
*/
template <class DataTypes>
class FrameForceField : public core::behavior::ForceField<DataTypes>
{
public:
    SOFA_CLASS(SOFA_TEMPLATE(FrameForceField,DataTypes),SOFA_TEMPLATE(core::behavior::ForceField, DataTypes));

    typedef typename DataTypes::Real Real;
    static const int material_dimensions = DataTypes::material_dimensions;
    typedef typename DataTypes::Coord Coord;
    typedef typename DataTypes::VecCoord VecCoord;
    typedef Data<typename DataTypes::VecCoord> DataVecCoord;
    typedef Data<typename DataTypes::VecDeriv> DataVecDeriv;
    typedef typename DataTypes::MaterialFrame Frame;
    typedef vector<Frame> VecFrame;

    typedef defaulttype::CStrain<DataTypes,false> StrainType;
    typedef typename StrainType::StrainVec StrainVec;
    typedef typename StrainType::StrStr StrStrMat;
    typedef typename StrainType::Strain Strain;
    typedef typename StrainType::Stress Stress;

    static const unsigned strainenergy_size = StrainType::strainenergy_size;
    typedef typename StrainType::StrainEnergyVec StrainEnergyVec;

//                typedef material::GridMaterial<material::MaterialTypes<material_dimensions,Real> > Material;
    typedef material::Material<material::MaterialTypes<material_dimensions,Real> > Material;
    typedef typename Material::StrStr StressStrainMatrix;
    typedef typename Material::VecMaterialCoord VecMaterialCoord;


public:
    FrameForceField(core::behavior::MechanicalState<DataTypes> *mm = NULL);
    virtual ~FrameForceField();


    // -- ForceField interface
    void init();
    void addForce(DataVecDeriv& f , const DataVecCoord& x , const DataVecDeriv& v , const core::MechanicalParams* /*mparams*/);
    void addDForce(DataVecDeriv&   df , const DataVecDeriv&   dx , const core::MechanicalParams* mparams );

    //        virtual void draw();

protected :

    // VecFrame rotation; ///< rotation matrices
    vector<Strain> strain, strainRate, stress, strainChange, stressChange;
    Material* material;
    typedef defaulttype::SampleData<DataTypes> SampleData;
    SampleData* sampleData;

    typedef typename StrainType::StrainEnergyVec  VecInteg; // vec or order VecIntegOrder
    vector< VecInteg > integFactors;
    vector< StressStrainMatrix > stressStrainMatrices;

};

#if defined(WIN32) && !defined(FRAME_FRAMEFORCEFIELD_CPP)
#ifndef SOFA_FLOAT
extern template class SOFA_FRAME_API FrameForceField<DeformationGradient331dTypes>;
extern template class SOFA_FRAME_API FrameForceField<DeformationGradient332dTypes>;
#endif
#ifndef SOFA_DOUBLE
extern template class SOFA_FRAME_API FrameForceField<DeformationGradient331fTypes>;
extern template class SOFA_FRAME_API FrameForceField<DeformationGradient332fTypes>;
#endif
#endif

} //

} //

} // namespace sofa

#endif
