// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad/pointerremap.h
class PointerRemapClass
{
public:
    // upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad/pointerremap.h
    struct PtrPairStruct
    {
    };
};

template<class Type>
class DynamicVectorClass
{
public:
    bool Add(const Type &);
};

class DynamicVectorAddPtrPairShim
{
public:
    bool add(const PointerRemapClass::PtrPairStruct &item);
};

template<class Type>
bool DynamicVectorClass<Type>::Add(const Type &item)
{
    return ((DynamicVectorAddPtrPairShim *)this)->add(
        *(const PointerRemapClass::PtrPairStruct *)&item);
}

template bool DynamicVectorClass<PointerRemapClass::PtrPairStruct>::Add(
    const PointerRemapClass::PtrPairStruct &);
