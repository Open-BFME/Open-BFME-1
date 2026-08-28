// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath/vehiclecurve.h
class VehicleCurveClass
{
public:
    // upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath/vehiclecurve.h
    struct _ArcInfoStruct
    {
    };
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath/hermitespline.h
class HermiteSpline1DClass
{
public:
    // upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath/hermitespline.h
    struct TangentsClass
    {
    };
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath/hermitespline.h
class HermiteSpline3DClass
{
public:
    // upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath/hermitespline.h
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

class VectorClassClearSplineShim
{
public:
    void run();
};

template<class Type>
void VectorClass<Type>::Clear()
{
    ((VectorClassClearSplineShim *)this)->run();
}

template void VectorClass<VehicleCurveClass::_ArcInfoStruct>::Clear();
template void VectorClass<HermiteSpline1DClass::TangentsClass>::Clear();
template void VectorClass<HermiteSpline3DClass::TangentsClass>::Clear();
