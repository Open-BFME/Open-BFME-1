// stlport
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas
// The three Clear bodies are 5-byte thunks: retail's ICF folded them onto one
// ILT thunk at 0x0000B9CE, which jumps to 0x006731A0 -- ?reset@NetCommandList@@QAEXXZ,
// already matched in targets/game/reverse/functions.csv. The callee is named by
// the real header, so the object references the defining name and links.
#include "GameNetwork/NetCommandList.h"

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath/vehiclecurve.h
class VehicleCurveClass
{
public:
    // upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath/vehiclecurve.h
    struct _ArcInfoStruct
    {
    };
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath/hermitespline.h
class HermiteSpline1DClass
{
public:
    // upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath/hermitespline.h
    struct TangentsClass
    {
    };
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath/hermitespline.h
class HermiteSpline3DClass
{
public:
    // upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath/hermitespline.h
    struct TangentsClass
    {
    };
};

template<class Type>
class VectorClass
{
public:
    virtual void Clear();
};

template<class Type>
void VectorClass<Type>::Clear()
{
    reinterpret_cast<NetCommandList *>(this)->reset();
}

template void VectorClass<VehicleCurveClass::_ArcInfoStruct>::Clear();
template void VectorClass<HermiteSpline1DClass::TangentsClass>::Clear();
template void VectorClass<HermiteSpline3DClass::TangentsClass>::Clear();
